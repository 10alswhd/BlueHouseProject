#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define RWRR S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define MAP_RW              PROT_READ | PROT_WRITE

#ifdef __APPLE__
    #define MAP_PRIV_ANON       MAP_PRIVATE | MAP_ANON
#else
    #define MAP_PRIV_ANON       MAP_PRIVATE | MAP_ANONYMOUS
#endif

struct index_s {
    int key;
    unsigned long children[2];
};

struct tree_s {
    int pagesize;
    unsigned long mapsize;
    unsigned char *pmap;
    unsigned long cur;
    struct index_s *root;
};

static void insert(struct tree_s *t, int key) {
    unsigned long off;
    struct index_s *x, *y, *new_node;

    y = NULL;
    x = t->root;
    while (x) {
        y = x;
        if (key < x->key)
            off = x->children[0];
        else
            off = x->children[1];

        if (off > 0)
            x = (struct index_s *)&t->pmap[off];
        else
            x = NULL;
    }

    new_node = (struct index_s *)&t->pmap[t->cur];
    new_node->key = key;
    unsigned long my_off = t->cur;
    t->cur += sizeof(struct index_s);

    if (!y)
        t->root = new_node;
    else if (new_node->key < y->key)
        y->children[0] = my_off;
    else
        y->children[1] = my_off;
}

static void print_inorder(struct tree_s *t, struct index_s *p) {
    /*
     * Check child nodes for 0 offset because that indicates a node
     * has no children.
     */
    if (p) {
        if (p->children[0] > 0)
            print_inorder(t, (struct index_s *)&t->pmap[p->children[0]]);
        printf("%d\n", p->key);
        if (p->children[1] > 0)
            print_inorder(t, (struct index_s *)&t->pmap[p->children[1]]);
    }
}

static int read_snapshot(const char *filename) {
    int fd;
    struct tree_s *t;

    fd = open(filename, O_RDONLY, RWRR);
    if (fd == -1) {
        fprintf(stderr, "can't read %s\n", filename);
        return -1;
    }

    t = malloc(sizeof(struct tree_s));
    t->pagesize = getpagesize();
    t->mapsize = (1<<20);
    t->pmap = mmap(0, t->mapsize, PROT_READ, MAP_SHARED, fd, 0);
    t->root = (struct index_s *)t->pmap;

    print_inorder(t, t->root);

    munmap(t->pmap, t->mapsize);
    close(fd);
    free(t);
    return 0;
}

static void take_snapshot(struct tree_s *t, const char *filename) {
    /*
     * Creates a file-backed memory map and copies a snapshot of the
     * tree to disk. It's called from a forked process to make use of
     * copy-on-write.
     */
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, RWRR);
    if (fd == -1)
        return;

    lseek(fd, t->mapsize-1, SEEK_SET);
    write(fd, "", 1);

    char *map = mmap(0, t->mapsize, PROT_WRITE, MAP_SHARED, fd, 0);
    memcpy(map, &t->pmap[0], t->mapsize);
    fsync(fd);

    print_inorder(t, t->root);

    printf("tree stored in snapshot file:\n");
    read_snapshot(filename);

    munmap(map, t->mapsize);
    munmap(t->pmap, t->mapsize);
    close(fd);
}

int main(int argc, char **argv) {
    pid_t pid, wpid;
    int status;
    struct tree_s *T = malloc(sizeof(struct tree_s));

    T->pagesize = getpagesize();
    T->mapsize = (1<<20);
    T->pmap = mmap(0, T->mapsize, MAP_RW, MAP_PRIV_ANON, -1, 0);
    T->root = NULL;

    insert(T, 4);
    insert(T, 3);
    insert(T, 2);
    insert(T, 8);
    insert(T, 7);
    insert(T, 10);

    pid = fork();
    if (pid == 0) {
        printf("taking a snapshot of following tree:\n");
        take_snapshot(T, "snapshot.dat");
        /* free this process's tree */
        free(T);
        exit(EXIT_SUCCESS);
    } else {
        printf("inserting 6 into tree from parent process:\n");
        insert(T, 6);
        print_inorder(T, T->root);
        wpid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
        if (wpid == -1) {
            perror("waitpid");
            goto err;
        }

        do {
            if (WIFEXITED(status))
                printf("(%d) child exited: %d\n", pid, WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                printf("(%d) child killed by signal: %d\n", pid, WTERMSIG(status));
            else if (WIFSTOPPED(status))
                printf("(%d) child stopped by signal: %d\n", pid, WSTOPSIG(status));
            else if (WIFCONTINUED(status))
                printf("(%d) continued\n", pid);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    munmap(T->pmap, T->mapsize);
    free(T);
    return 0;

err:
    munmap(T->pmap, T->mapsize);
    free(T);
    return -1;
}
