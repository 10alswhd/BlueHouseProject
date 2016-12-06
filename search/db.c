typedef unsigned int sz;
typedef unsigned short ix;

int compare(const char* a, const char* b, sz n) {
    while (n) {
        if (*a != *b) {
            return (unsigned char)*a - (unsigned char)*b;
        }
        if (*a == 0) {
            return 0;
        }
        n--;
        a++;
        b++;
    }
    return 0;
}

void copy(char* a, const char* b, sz n) {
    while (n && *b) {
        *a = *b;
        n--;
        a++;
        b++;
    }
    *a = 0;
}

int search(const char* storage, const char* key, ix i, ix *r) {
    const char* index = storage + 100 * 1024;
    const char* keys = storage + 200 * 1024;
    const char* current = keys + 65 * i;
    int c = compare(key, current, 64);
    if (c < 0) {
        ix left = *((ix*)(index + 4 * i));
        if (left) {
            return search(storage, key, left, r);
        }
    } else if (c > 0) {
        ix right = *((ix*)(index + 4 * i + 2));
        if (right) {
            return search(storage, key, right, r);
        }
    }
    *r = i;
    return c;
}

ix allocate(char *storage) {
    char* meta = storage;
    ix n = *((ix*)(meta));
    *((ix*)(meta)) = n + 1;
    return n;
}

bool db(char* storage, const char* key, char** data) {
    char* index = storage + 100 * 1024;
    char* keys = storage + 200 * 1024;
    char* values = storage + 500 * 1024;
    ix i;
    int c = search(storage, key, 0, &i);
    if (*data) {
        if (!c) {
            return false;
        }
        ix n = allocate(storage);
        copy(keys + 65 * n, key, 64);
        copy(values + 129 * n, *data, 128);
        if (c < 0) {
            *((ix*)(index + 4 * i)) = n;
        } else if (c > 0) {
            *((ix*)(index + 4 * i + 2)) = n;
        }
        return true;
    } else {
        if (!c) {
            *data = values + 129 * i;
            return true;
        }
        return false;
    }
}

#ifdef MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* storage = (char*)(malloc(1024 * 1024));
    char* key1 = (char*)(malloc(64));
    char* key2 = (char*)(malloc(64));
    char* key3 = (char*)(malloc(64));
    char* key4 = (char*)(malloc(64));
    char* key5 = (char*)(malloc(64));
    char* value1 = (char*)(malloc(128));
    char* value2 = (char*)(malloc(128));
    char* value3 = (char*)(malloc(128));
    char* value4 = (char*)(malloc(128));
    char* value5 = (char*)(malloc(128));
    char* buf = 0;
    memset((void*)storage, 0, 1024 * 1024);
    copy(key1, "key1", 64);
    copy(key2, "key2", 64);
    copy(key3, "key3", 64);
    copy(key4, "key4", 64);
    copy(key5, "key5", 64);
    copy(value1, "value1", 128);
    copy(value2, "value2", 128);
    copy(value3, "value3", 128);
    copy(value4, "value4", 128);
    copy(value5, "value5", 128);
    bool r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    r1 = db(storage, key1, &value1);
    r2 = db(storage, key3, &value3);
    r3 = db(storage, key5, &value5);
    r4 = db(storage, key2, &value2);
    r5 = db(storage, key4, &value4);
    r6 = !db(storage, key1, &value1);
    r7 = !db(storage, key2, &value2);
    r8 = !db(storage, key3, &value3);
    r9 = !db(storage, key4, &value4);
    r10 = !db(storage, key5, &value5);
    printf("%d %d %d %d %d %d %d %d %d %d\n",
        r1, r2, r3, r4, r5, r6, r7, r8, r9, r10);
    r1 = db(storage, key1, &buf);
    r2 = !compare(buf, value1, 64);
    buf = 0;
    r3 = db(storage, key2, &buf);
    r4 = !compare(buf, value2, 64);
    buf = 0;
    r5 = db(storage, key3, &buf);
    r6 = !compare(buf, value3, 64);
    buf = 0;
    r7 = db(storage, key4, &buf);
    r8 = !compare(buf, value4, 64);
    buf = 0;
    r9 = db(storage, key5, &buf);
    r10 = !compare(buf, value5, 64);
    buf = 0;
    printf("%d %d %d %d %d %d %d %d %d %d\n",
        r1, r2, r3, r4, r5, r6, r7, r8, r9, r10);
    return 0;
}
#endif
