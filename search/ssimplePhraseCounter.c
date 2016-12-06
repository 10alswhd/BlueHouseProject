#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

struct Counter_ { 
    char* string;
    int count;
};

typedef struct Counter_ Counter;

Counter* CCreate(char* searchString) {
    Counter* counter = malloc(sizeof(Counter));

    if (counter) {

        size_t t = strlen(searchString);
        counter->string = calloc(t+1, sizeof(char));
        strcpy(counter->string,searchString);

        for ( ; * counter->string; counter->string ++)
            * counter->string = tolower(* counter->string);
        counter->string -= t;

        counter->count = 0;
    }

    return counter;
}

void CDestroy(Counter* counter) {
    free(counter->string);
    free(counter);
}

void syscallReadfile(const char* fileName, char** buff, long* fileSizePtr) {

    int fd = open(fileName, O_RDONLY);
    if (fd < 0) {
        perror("./p05"); exit(1); 
    }

    *fileSizePtr = (long) lseek(fd, 0, SEEK_END);
    if (*fileSizePtr < 0) { 
        perror("./p05"); exit(1); 
    }
    lseek(fd, 0, SEEK_SET);

    *buff = calloc(1, (*fileSizePtr) + 1);

    if (*buff == NULL) 
        close(fd), perror("./p05"), exit(1);

    int i;
    for (i = 0; i < *fileSizePtr; i++) {
        if (read(fd, *buff + i, 1) == -1)
            close(fd), free(*buff), perror("./p05"), exit(1);
    }
    *(*buff + *fileSizePtr) = '\0';

    // if (read(fd, *buff, (size_t) *fileSizePtr )  == -1)
    //     close(fd), free(*buff), perror("./p05"), exit(1);

    // Need to null-terminate string
    // *buff += *fileSizePtr;
    // **buff = '\0';
    // *buff -= *fileSizePtr;

    close(fd);

}

void stdioReadfile(const char* fileName, char** buff, long* fileSizePtr) {

    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) {
        perror("./p05"), exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    *fileSizePtr = ftell(fp);
    rewind(fp);

    *buff = calloc(1, (*fileSizePtr) + 1);

    if ((*buff) == NULL)
        fclose(fp),perror("./p05"),exit(1);
    if (1!=fread(*buff, *fileSizePtr, 1, fp))
        fclose(fp), free(*buff), perror("./p05"), exit(1);
    fclose(fp);

}

int specialcmp(const char* a, const char* b) {
    const unsigned char* c = (const unsigned char*) a;
    const unsigned char* d = (const unsigned char*) b;

    while (*c != '\0') {
        if (*d == '\0') return 0;
        if (*d > *c) return -1;
        if (*c > *d) return 1;

        c++;
        d++;
    }

    return 0;
}

int main(int argc, char** argv) {

    if (argc < 3)
        puts("Not enough arguments!"),exit(1);

    // clock_t start, stop;
    // start = clock();

    char* fileName = NULL;
    int i, j, num = 0, systemcallsFlag = 0;

    Counter** counters = calloc(argc - 2, sizeof(Counter*));

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--systemcalls") == 0) {
            systemcallsFlag = 1;
        }
        else if (!fileName) {
            fileName = argv[i];
        }
        else {
            counters[num] = CCreate(argv[i]);
            num++;
        }
    }

    char* buffer = NULL;
    long fileSize;
    void (*readFileFunc)(const char*, char**, long*);
    readFileFunc = systemcallsFlag ? (&syscallReadfile) : (&stdioReadfile);

    readFileFunc(fileName, &buffer, &fileSize);

    for ( ; *buffer; ++(buffer) ) 
        *buffer = tolower(*buffer);
    buffer -= fileSize;

    for (i = 0; i < num; i++) {
        for (j = 0; j < fileSize; j++) {
            if (specialcmp(counters[i]->string, (buffer)+j) == 0)
                counters[i]->count++;
        }
        printf("%d\n", counters[i]->count);
    }

    free(buffer);
    for (i = 0; i < num; i++)
        CDestroy(counters[i]);
    free(counters);

    // stop = clock();
    // float elapsed = 1000*((float) stop - (float) start) / (CLOCKS_PER_SEC);
    // printf("Elapsed time: %fd ms \n", elapsed);

    return 0;
}
