#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int do_alloc(char **buffer) {
    int cpos = 0;

    if (!*buffer) {
        *buffer = calloc(2, sizeof(char));
        assert(*buffer);
    }
    else {
        cpos = strlen(*buffer);
        *buffer = realloc(*buffer, cpos + 2);
        assert(*buffer);
        (*buffer)[cpos + 1] = 0;
    }
    return cpos;
}


void do_free(char **buffer) {
    if (*buffer) {
        free(*buffer);
        *buffer = NULL;
    }
}


int scan_word(char **buffer, FILE *input) {
    int c;
    int pos = 0;

    do_free(buffer);
    while ((c = fgetc(input)) != EOF) {
        pos = do_alloc(buffer);
        if (c == '\n' || c == ' ') {
            break;
        }
        (*buffer)[pos] = (unsigned char) c;
    }
    return pos;
}


int readInt() {
    char *buffer = NULL;
    int retVal =  -999;
    scan_word(&buffer, stdin);
    retVal = atoi(buffer);
    do_free(&buffer);
    return retVal;
}


int *make_array(int count) {
    int *arrayInt = (int *)calloc(count, sizeof(int));
    assert(arrayInt);
    return arrayInt;
}


void do_populate(int *items, int count) {
    int i;
    for (i = 0; i < count; i++) {
        *items = readInt();
        items++;
    }
}


int *search(int count, int *items, int credits) {
    int *ab = make_array(2);
    int i, j;
    do_populate(items, count);
    for (i = 0; i < count - 1; i++) {
        ab[0] = i + 1;
        for (j = i + 1; j < count; j++) {
            ab[1] = j + 1;
            if (items[i] + items[j] == credits) {
                return ab;
            }
        }
    }
    return ab;
}


void print_result(int cNum, int first, int second) {
    printf("Case #%d: %d %d\n", cNum, first, second);
}


void free_array(void *thing) {
    if (thing) { free(thing); }
}


void spendCredits(int cNum, int credits) {
    int itemNums = readInt();
    int *items = make_array(itemNums);
    int *ab = search(itemNums, items, credits);
    print_result(cNum, ab[0], ab[1]);
    free_array(items);
    free_array(ab);
}


int main() {
    int cases = readInt();
    int i = 0;

    for (; i < cases; i++) {
        spendCredits(i + 1, readInt());
    }
}
