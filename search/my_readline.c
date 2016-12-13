#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <time.h>
#include <stdlib.h>

int my_readline(const int fd, char *const buf, const size_t count);
void my_print_lines(int fd, char *linebuf, size_t count);

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: ./program data.txt\n");
        return 1;
    }
    srandom(time(NULL));
    char linebuf[32];
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        err(1, NULL);
    }
    my_print_lines(fd, linebuf, sizeof(linebuf));
    return 0;
}

void my_print_lines(int fd, char *linebuf, size_t count) {
    int ret;
    while((ret = my_readline(fd, linebuf, count))) {
        if (ret < 0) {
            printf("yo there was an error %d", ret);
            break;
        }
        printf("%s", linebuf);
    }
}


int linear_search_for_char(const char *buf, const size_t count,
                           const char target) {
    unsigned i = 0;
    for (; i < count; i++) {
        if (buf[i] == target) {
            return i;
        }
    }
    return -1;
}

/*
 * this function simulates read(2), which does not guarantee
 * reading the amount you request (although that almost always happens in
 * practice), in a more volatile manner
 */
int my_read(int fd, void *buf, size_t nbyte) {
    size_t bogus = nbyte ? (random() % nbyte) + 1 : nbyte;
    printf(" >> myread. requested: %lu, gave: %lu\n", nbyte, bogus);
    return read(fd, buf, bogus);
}

/*
 * my_readline - read a line from a file descriptor
 *
 * @arg fd: file descriptor to read from
 * @arg buf: buffer to read into
 * @arg count: maximum number of bytes to write to buf including null
 * terminator
 *
 * @return n: total number of bytes written, success
 * @return 0: eof
 * @return -1: system error
 * @return -2: no newline found within count-1 bytes
 */
int my_readline(const int fd, char *const buf, const size_t count) {
    size_t total_read = 0;
    ssize_t ret = 0;
    int newline_loc = 0;
    unsigned buf_offset = 0;

    const size_t max_read = count - 1;
    const off_t seek = lseek(fd, 0, SEEK_CUR);
    if (seek < 0) {
        return seek;
    }

    ret = my_read(fd, buf, max_read);
    if (ret <= 0) {
        return ret;
    }

    total_read = ret;
    while (total_read <= max_read) {
        newline_loc = linear_search_for_char(buf+buf_offset, ret, '\n');
        if (newline_loc != -1 || total_read == max_read) {
            break;
        }
        buf_offset += ret;
        ret = my_read(fd, buf+buf_offset, max_read-total_read);
        if (ret <= 0) {
            return ret;
        }
        total_read += ret;
    }

    if (newline_loc == -1) {
        return -2;
    }

    const unsigned newline_offset = newline_loc + buf_offset;
    const off_t new_seek = seek + newline_offset + 1;
    if (lseek(fd, new_seek, SEEK_SET) < 0) {
        return -1;
    }
    buf[newline_offset + 1] = '\0';
    return newline_offset + 1 + 1;
}
