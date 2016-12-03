#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ht_entry_s { char* a; char* b; } ht_entry_t;
typedef struct ht_s { ht_entry_t* table; int size; } ht_t;
ht_t* ht_create(int size);
void ht_set(ht_t* ht, char* a, char* b); // Sets key a, value b
char* ht_get(ht_t* ht, char* a); // Gets the value b with the key a
char* strapp(char* old_str, char* add_str); // Safely appends the second string to first one

int main() {
    ht_t* stop_words = ht_create(541), * words = ht_create(809);

    // Read stop words into the stop_words hash-table
    FILE* inf = fopen("stopWordList.txt", "r");
    if(inf == NULL) {
        printf("ERROR: Could not open the %s!", "stopWordList.txt");
        exit(-1);
    }

    char result;
    while(1) {
        char buffer[32];
        result = fscanf(inf, "%s", buffer);
        if(result != EOF) ht_set(stop_words, buffer, buffer);
        else break;
    }
    fclose(inf);

    // Read document words into the words hash-table
    int i;
    for(i = 0; i < 10; ++i) {
        char file_name[32];
        strcpy(file_name, "documents/");
        char text_name[32], tmp[20];
        strcpy(text_name, itoa(i + 1, tmp, 10)); // eg. 1.txt
        strcat(text_name, ".txt");
        strcat(file_name, text_name); // eg. documents/1.txt

        if((inf = fopen(file_name, "r")) == NULL) {
            printf("ERROR: Could not open the %s!", file_name);
            exit(-1);
        }

        char result;
        do { // Loop the words inside documents
            char buffer[32];
            if((result = fscanf(inf, "%s", buffer)) != EOF && // We're not at the end
               ht_get(stop_words, buffer) == NULL) { // This word is not a stop word
                char* in_files = ht_get(words, buffer); // Which files this word in?
                if(in_files != NULL) { // Found this word at least once
                    if(strstr(in_files, text_name) == NULL){ // We did not check this file for this word yet
                        char append_text[16];
                        strcpy(append_text, ", ");
                        strcat(append_text, text_name);
                        ht_set(words, buffer, strapp(in_files, append_text)); // Append this file to others
                    }
                } else ht_set(words, buffer, text_name); // Put this file to the hash table
            }
        } while(result != EOF);
        fclose(inf);
    }

    printf("\n ~~ DOCUMENT SEARCH ENGINE");
    char input[32];
    while(1) {
        printf("\n\n Quit(q), Search: ");
        scanf("%s", input);
        if(strcmp(input, "q") != 0){
            char* files = ht_get(words, input);
            if(ht_get(stop_words, input) != NULL) printf(" %s is a stop word.", input);
            else{
                if(files != NULL) printf(" %s", ht_get(words, input));
                else printf(" Could not find %s in any documents.", input);
            }
        }
        else break;
    }

    system("pause");
    return 0;
}

int calc_key(char* str) {
    int key, i, length = strlen(str);
    for(i = key = 0; i < length; ++i) key += (str[i] - 'a')*26*i;
    return key;
}

int h(int size, int key, int i) { return ((key % size) + i*(1 + (key % (size-1)))) % size; }

void ht_set(ht_t* ht, char* a, char* b) {
    unsigned int key = calc_key(a), i = 0, idx = h(ht->size, key, i++);
    unsigned int start = idx;
    do {
        if(ht->table[idx].a != NULL && strcmp(ht->table[idx].a, a) == 0) {
            // Already exists
            strcpy(ht->table[idx].b, b);
            return;
        }
        idx = h(ht->size, key, ++i);
    } while(idx != start && ht->table[idx].a != NULL);
    // Not exists, allocate memory and put it in
    ht->table[idx].a = (char*) malloc(32);
    strcpy(ht->table[idx].a, a);
    ht->table[idx].b = (char*) malloc(32);
    strcpy(ht->table[idx].b, b);
}

char* ht_get(ht_t* ht, char* a) {
    unsigned int key = calc_key(a), i = 0, idx = h(ht->size, key, i++);
    unsigned int start = idx;
    do {
        if(ht->table[idx].a != NULL && strcmp(ht->table[idx].a, a) == 0) {
            return ht->table[idx].b; // Found
        }
        idx = h(ht->size, key, ++i);
    } while(idx != start && ht->table[idx].a != NULL);

    return NULL; // Could not find
}

ht_t* ht_create(int size){
    ht_t* ht = (ht_t*) malloc(sizeof(ht_t));
    ht->size = size;
    ht->table = (ht_entry_t*) calloc(size, sizeof(ht_entry_t));
    return ht;
}

char* strapp(char* old_str, char* add_str) {
    char* out = (char*) malloc(strlen(old_str) + strlen(add_str));
    sprintf(out, "%s%s", old_str, add_str);
    return out;
}
