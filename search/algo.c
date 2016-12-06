#include <stdio.h>
#include <string.h>
#define MAX_N 1048576
#define BUF_N 2097152

int load(char*, char**, int*);
void search(char**, int*);

int main(int argc, char const *argv[]) {
    static char str[MAX_N];
    static char* original_list[MAX_N * 10];
    int length_list[10];

    load(str, original_list, length_list);
    search(original_list, length_list);

    return 0;
}

int load(char* str, char** original_list, int* length_list) {
    int length = 0;
    static char buf[BUF_N];
    int n, i;

    for(i = 0 ; i < 10 ; i++) {
        length_list[i] = 0;
    }

    while((n = fread(buf, sizeof(char), BUF_N, stdin)) > 0) {
        for(i = 0 ; i < n ; i++) {
            if(buf[i] < '0' || buf[i] > '9') {
                /* 数字でない文字は無視する */
                continue;
            } else {
                int index = buf[i] - '0';
                str[length] = buf[i];

                /* この時にもうバケツに入れてしまう */
                original_list[index*MAX_N + length_list[index]] = str + length;
                ++length_list[index];
                ++length;
            }
        }
    }

    /* 最後の文字列は念のためNULL文字に */
    str[length] = '\0';

    printf("String Length: %d\n", length);
    return length;
}

void search_tmp(char**, int, int);
void update_longest_word(int, char*);
void print_longest_word();

void search(char** original_list, int* length_list) {
    int i;
    for(i = 0 ; i < 10 ; i++) {
        if(length_list[i] > 1) {
            search_tmp(original_list + i*MAX_N, length_list[i], 1);
        }
    }
    print_longest_word();
}

void search_tmp(char** list, int length, int pnt) {
    static char* bucket[10 * MAX_N];
    int bucket_length[10];
    int bucket_length_max = 0;
    int i, j;

    /* 配列の初期化 */
    for(i = 0 ; i < 10 ; i++) {
        bucket_length[i] = 0;
    }

    /* バケツに振り分け */
    for(i = 0 ; i < length ; i++) {
        if(list[i][pnt] != '\0') {
            int index = list[i][pnt] - '0';
            bucket[index * MAX_N + bucket_length[index]] = list[i];
            ++bucket_length[index];
        }
    }

    /* バケツの要素数の最大値を求める */
    for(i = 0 ; i < 10 ; i++) {
        if(bucket_length_max < bucket_length[i]) {
            bucket_length_max = bucket_length[i];
        }
    }

    if(bucket_length_max <= 1) {
        /* バケツの要素数がすべて1以下なら、今見ている文字数以上一致することはない */
        update_longest_word(pnt, list[0]);
    } else {
        int tmp = 0;
        int bucket_pos[10];
        for(i = 0 ; i < 10 ; i++) {
            if(bucket_length[i] == 2) {
                /* 2個しか入っていないバケツは優先的に探索する */
                /* 一致する文字数を数える */
                for(j = pnt + 1 ; bucket[i*MAX_N][j] == bucket[i*MAX_N+1][j] ; j++) ;
                update_longest_word(j, bucket[i*MAX_N]);
            }
            else if(bucket_length[i] >= 3) {
                /* 3個以上入っているバケツは、元のリストに戻す */
                memcpy(list + tmp, bucket + i*MAX_N, bucket_length[i] * sizeof(char*));
                bucket_pos[i] = tmp;
                tmp += bucket_length[i];
            }
        }

        for(i = 0 ; i < 10 ; i++) {
            if(bucket_length[i] >= 3) {
                /* 3個以上入っているバケツを探索 */
                search_tmp(list + bucket_pos[i], bucket_length[i], pnt + 1);
            }
        }
    }
}

/* Longest Word System */

int longest_length = 0;
char* longest_list[MAX_N/2];
int longest_count = 0;

void update_longest_word(int length, char* sample) {
    if(longest_length == length) {
        longest_list[longest_count++] = sample;
    } else if(longest_length < length) {
        longest_list[0] = sample;
        longest_count = 1;
        longest_length = length;
    }
}

void print_longest_word() {
    printf("Length: %d\n", longest_length);
    printf("Count: %d\n", longest_count);
    printf("Word: ");
    int i;
    for(i = 0 ; i < longest_count ; i++) {
        int j;
        if(i != 0) {
            printf(", ");
        }
        for(j = 0 ; j < longest_length ; j++) {
            putchar(longest_list[i][j]);
        }
    }
    putchar('\n');
}
