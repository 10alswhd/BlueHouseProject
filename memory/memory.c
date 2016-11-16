#include <string.h>
#include <stdio.h>

void print_maps();

char *foo = "This string is allocated in the string pool within the text segment which is read and execute only so it should be considered a const char *\n";
char bar[] = "This string is allocated in the initialized data section of the data segement\n";
char *baz;

int
main() {
    char zap[] = "This string is allocated on the stack\n"; /* TODO this is being allocated in the data segement */
    static char zip[] = "This string is allocated in the initialized data section too\n";

    baz = strdup("Space for this string is allocated on the heap\n");
    print_maps();

    /* Print the addresses of these pointers */
    printf("%18p: main()\n", main);
    printf("%18p: print_maps()\n", print_maps);
    printf("%18p: %s", foo, foo);
    printf("%18p: %s", bar, bar);
    printf("%18p: %s", zip, zap);
    printf("%18p: %s", baz, baz);
    printf("%18p: %s", zap, zap);

    return 0;
}


/*
 * This function prints out the processes memory map
 */
void
print_maps() {
    FILE *fd;
    char line[100];

    fd = fopen("/proc/self/maps", "r");
    if (fd == NULL) {
        perror("open()");
        return;
    }

    printf("Memory map:\n");
    while (fgets(line, sizeof(line), fd) != NULL)
        fputs(line, stdout);

    fclose(fd);
}
