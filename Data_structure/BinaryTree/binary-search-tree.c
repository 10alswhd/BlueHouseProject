#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

typedef struct bst *bst_t;
struct bst {
    char name;
    int index;
    bst_t parent;
    union {
        struct { bst_t lchild, rchild; };
        bst_t childs[2];
    };
    int isleaf;
    int height, size, leafcount;
};

bst_t bst_newnode() {
    static int lastindex=0;
    bst_t b = malloc(sizeof(*b));
    b->name = 0;
    b->index = ++lastindex;
    b->lchild = NULL;
    b->rchild = NULL;
    b->parent = NULL;
    b->height = 0;
    b->size = 1;
    b->leafcount = 0;
    return b;
}

bst_t bst_merge(bst_t lchild, bst_t rchild) {
    bst_t r = bst_newnode();
    r->lchild = lchild;
    r->rchild = rchild;
    for(int i=0; i<2; i++) {
        bst_t c = r->childs[i];
        if(c) {
            c->parent = r;
            if(r->height < c->height+1)
                r->height = c->height+1;
            r->size += c->size;
            r->leafcount += c->leafcount;
        }
    }
    return r;
}

int bst_isleaf(bst_t bst) {
    return bst->isleaf;
    //return bst->lchild==NULL && bst->rchild==NULL;
}

void bst_print_glist(bst_t bst) {
    if(bst == NULL)
        printf("()");
    else if(bst_isleaf(bst)) {
        putchar(bst->name);
    }
    else {
        bst_t r;
        putchar('(');
        for(r=bst; r; r=r->rchild) {
            bst_print_glist(r->lchild);
        }
        putchar(')');
    }
}

void bst_update_info(bst_t bst) { // using lchild rchild and name only
    if(!bst)
        return;
    bst->height = 0;
    bst->size = 1;
    //if(bst_isleaf(bst)) {
    if(bst->lchild == NULL && bst->rchild==NULL) {
        bst->leafcount = 1;
        return;
    }
    bst->leafcount = 0;
    for(int i=0; i<2; i++) {
        bst_t c = bst->childs[i];
        if(c) {
            bst_update_info(c);
            c->parent = bst;
            if(bst->height < c->height+1)
                bst->height = c->height+1;
            bst->size += c->size;
            bst->leafcount += c->leafcount;
        }
    }
}

static char *glist_getnext(char *s) {
    while(*s && !isalpha(*s) && *s!='(' && *s!=')') s++;
    return s;
}

bst_t bst_from_glist_in(char **ps) {
    bst_t r, *p;
    char *s = *ps;
    s = glist_getnext(s);
    if(*s == '(') {
        r = NULL;
        p = &r;
        s = glist_getnext(s+1);
        *ps = s;
        while(*s != ')') {
            *p = bst_newnode();
            (*p)->lchild = bst_from_glist_in(ps);
            s = *ps;
            p = &(*p)->rchild;
        }
        *ps = glist_getnext(s+1);
        return r;
    } else {
        bst_t r;
        r = bst_newnode();
        r->name = *s;
        r->isleaf = 1;
        r->leafcount = 1;
        *ps = glist_getnext(s+1);
        return r;
    }
}

bst_t bst_from_glist(char *s) {
    bst_t bst;
    bst = bst_from_glist_in(&s);
    bst_update_info(bst);
    return bst;
}

void bst_print_node(bst_t bst) {
    printf("%3d", bst->index);
    if(bst->name)
        printf("(%c)", bst->name);
    else
        printf("   ");
}

void bst_preorder_tr(bst_t bst) {
    if(!bst)
        return;
    bst_print_node(bst);
    bst_preorder_tr(bst->lchild);
    bst_preorder_tr(bst->rchild);
}

void bst_inorder_tr(bst_t bst) {
    if(!bst)
        return;
    bst_inorder_tr(bst->lchild);
    bst_print_node(bst);
    bst_inorder_tr(bst->rchild);
}

void bst_postorder_tr(bst_t bst) {
    if(!bst)
        return;
    bst_postorder_tr(bst->lchild);
    bst_postorder_tr(bst->rchild);
    bst_print_node(bst);
}

void bst_levelorder_tr_in(bst_t bst, int level) {
    if(!bst)
        return;
    if(!level)
        bst_print_node(bst);
    else {
        bst_levelorder_tr_in(bst->lchild, level-1);
        bst_levelorder_tr_in(bst->rchild, level-1);
    }
}
void bst_levelorder_tr(bst_t bst) {
    for(int i=0; i<=bst->height; i++) {
        //putchar('|');
        bst_levelorder_tr_in(bst, i);
    }
}

void commander() {
    char *cmds[]={
        "rgl",                  /* 0 */
        "pgl",
        "ppre",
        "pin",
        "ppost",
        "plv",                  /* 5 */

        "gh",                   /* 6 */
        "gl",
        "gs",
        "quit",
        "help",                 /* 10 */
        NULL,
    };
    char buffer[1024], *bp;
    bst_t bst = NULL;
        
    while(1) {
        int index, len;
        printf("bst> ");
        fgets(buffer, sizeof(buffer), stdin);
        for(index=0; cmds[index]; index++) {
            len = strlen(cmds[index]);
            if(!isalnum(buffer[len])
               && !strncmp(buffer, cmds[index], len))
                break;
        }
        bp = buffer + len + 1;
        switch(index) {
        case 0:                 /* rgl */
            bst = bst_from_glist(bp);
            break;
        case 1:                 /* pgl */
            bst_print_glist(bst);
            putchar('\n');
            break;
        case 2:                 /* ppre */
            bst_preorder_tr(bst);
            putchar('\n');
            break;
        case 3:                 /* pin */
            bst_inorder_tr(bst);
            putchar('\n');
            break;
        case 4:                 /* ppost */
            bst_postorder_tr(bst);
            putchar('\n');
            break;
        case 5:                 /* plv */
            bst_levelorder_tr(bst);
            putchar('\n');
            break;
        case 6:                 /* gh */
        case 7:                 /* gl */
        case 8:                 /* gs */
            printf("height: %4d\n", bst->height);
            printf("leaves: %4d\n", bst->leafcount);
            printf("size:   %4d\n", bst->size);
            break;
        case 9:
            goto quit;
        case 10:
        default:
            printf("\
Usage:\n\
	rgl	read glist		\n\
	pgl	print as glist		\n\
	ppre	print using pre order	\n\
	pin	print using in order	\n\
	ppost	print using post order	\n\
	plv	print using level order	\n\
	gh	print tree height	\n\
	gl	print tree leaf count	\n\
	gs	print tree size		\n\
	quit	quit			\n\
	help	print this message	\n\
");
            break;
        } // switch
    } // while
 quit:
    return;
}

int main() {
    commander();
    return 0;
}
