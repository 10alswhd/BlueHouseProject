// GistID: f43a768e331ee7fbb9fa 
//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 100

struct vocab_word {
  long long cn;
  char *word;
};

const int vocab_hash_size = 30000000;  // Maximum 30 * 0.7 = 21M words in the vocabulary

struct vocab_word *vocab;
int *vocab_hash;
long long vocab_max_size = 1000, vocab_size = 0, train_words = 0, file_size = 0;
int debug_mode = 2, min_count = 5, min_reduce = 1;

void write_word(char* word, FILE* file) {
    fwrite(word, sizeof(char), strlen(word), file);
    fwrite(" ", sizeof(char), 1, file);
}

void read_word(char* word, FILE* file) {
    int i = 0, c;
    while (!feof(file)) {
        c = fgetc(file);
        if (c == ' ' || c == '\n') break;
        word[i] = c;
        i++;
        if (i >= MAX_STRING - 1) i--;
    }
    word[i] = 0;
}

int get_arg_pos(char* str, int argc, char** argv) {
    int i;
    for (i = 0; i < argc; ++i) {
        if (strcmp(str, argv[i]) == 0) {
            if (i + 1 < argc) {
                return i + 1;
            } else {
                fprintf(stderr, "No value povided for argument %s\n", str);
                exit(0);
            }
        }
    }
    return -1;
}

int get_word_hash(char *word) {
    unsigned long long a, hash = 0;
    for (a = 0; a < strlen(word); a++) hash = hash * 257 + word[a];
    hash = hash % vocab_hash_size;
    return hash;
}

// Returns position of a word in the vocabulary; if the word is not found, returns -1
int search_vocab(char *word) {
    unsigned int hash = get_word_hash(word);
    while (1) {
        if (vocab_hash[hash] == -1) return -1;
        if (!strcmp(word, vocab[vocab_hash[hash]].word)) return vocab_hash[hash];
        hash = (hash + 1) % vocab_hash_size;
    }
    return -1;
}

// Adds a word to the vocabulary
int add_word_to_vocab(char *word) {
    word[MAX_STRING - 1] = 0;
    unsigned int hash, length = strlen(word) + 1;
    if (length > MAX_STRING) length = MAX_STRING;
    vocab[vocab_size].word = (char *)calloc(length, sizeof(char));
    strcpy(vocab[vocab_size].word, word);
    vocab[vocab_size].cn = 0;
    vocab_size++;
    // Reallocate memory if needed
    if (vocab_size + 2 >= vocab_max_size) {
        vocab_max_size += 1000;
        vocab = (struct vocab_word *)realloc(vocab, vocab_max_size * sizeof(struct vocab_word));
    }
    hash = get_word_hash(word);
    while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
    vocab_hash[hash] = vocab_size - 1;
    return vocab_size - 1;
}

void read_vocab(char* read_vocab_file) {
    long long a, i = 0;
    char c;
    char word[MAX_STRING];
    FILE *fin = fopen(read_vocab_file, "rb");
    if (fin == NULL) {
        printf("Vocabulary file not found\n");
        exit(1);
    }
    for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;
    vocab_size = 0;
    while (1) {
        read_word(word, fin);
        if (feof(fin)) break;
        a = add_word_to_vocab(word);
        fscanf(fin, "%lld%c", &vocab[a].cn, &c);
        i++;
    }
    fclose(fin);
}

// Reduces the vocabulary by removing infrequent tokens
void reduce_vocab() {
  int a, b = 0;
  unsigned int hash;
  for (a = 0; a < vocab_size; a++) if (vocab[a].cn > min_reduce) {
    vocab[b].cn = vocab[a].cn;
    vocab[b].word = vocab[a].word;
    b++;
  } else free(vocab[a].word);
  vocab_size = b;
  for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;
  for (a = 0; a < vocab_size; a++) {
    // Hash will be re-computed, as it is not actual
    hash = get_word_hash(vocab[a].word);
    while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
    vocab_hash[hash] = a;
  }
  fflush(stdout);
  min_reduce++;
}

void save_vocab(char* save_vocab_file) {
  long long i;
  FILE *fo = fopen(save_vocab_file, "wb");
  for (i = 0; i < vocab_size; i++) fprintf(fo, "%s %lld\n", vocab[i].word, vocab[i].cn);
  fclose(fo);
}

void learn_vocab_from_train_file(char* train_file) {
  char word[MAX_STRING];
  FILE *fin;
  long long a, i;
  for (a = 0; a < vocab_hash_size; a++) vocab_hash[a] = -1;
  fin = fopen(train_file, "rb");
  if (fin == NULL) {
    printf("ERROR: training data file not found!\n");
    exit(1);
  }
  vocab_size = 0;
//  add_word_to_vocab((char *)"</s>");
  while (1) {
    read_word(word, fin);
    if (feof(fin)) break;
    train_words++;
    if ((debug_mode > 1) && (train_words % 100000 == 0)) {
      printf("%lldK%c", train_words / 1000, 13);
      fflush(stdout);
    }
    i = search_vocab(word);
    if (i == -1) {
      a = add_word_to_vocab(word);
      vocab[a].cn = 1;
    } else vocab[i].cn++;
    if (vocab_size > vocab_hash_size * 0.7) reduce_vocab();
  }
//  SortVocab();
  if (debug_mode > 0) {
    printf("Vocab size: %lld\n", vocab_size);
    printf("Words in train file: %lld\n", train_words);
  }
  file_size = ftell(fin);
  fclose(fin);
}

void second_process_text(FILE* input, FILE* output) {
    char word[MAX_STRING];
    while(1) {
        read_word(word, input);
        if (feof(input)) break;
        if (word[0] == 0) continue;
        int pos = search_vocab(word);
        if (pos >= 0) {
            if (vocab[pos].cn > min_count) {
                write_word(word, output);
            } else {
                write_word((char*)"NUMBER", output);
            }
        }
    }
}

void process_text(FILE* input, FILE* output) {
    char word[MAX_STRING];
    char new_word[2 * MAX_STRING];
    while(1) {
        read_word(word, input);
        if (feof(input)) break;
        int pos = search_vocab(word);
        if (pos >= 0) {
            if (vocab[pos].cn > min_count) {
                write_word(word, output);
            } else {
                int j, a = 0, d = 0;
                for (j = 0; word[j] != 0; ++j) {
                    if (isdigit(word[j])) {
                        new_word[a++] = 'D';
                        new_word[a++] = 'G';
                        d = 1;
                    } else {
                        new_word[a++] = word[j];
                    }
                }
                new_word[a] = 0;
                if (d == 0) write_word((char*)"UNKNOWN", output);
                else write_word(new_word, output);
            }
        }
    }
}

void update_word_counts(char* filename) {
    FILE* in = fopen(filename, "r");
    char word[MAX_STRING];
    while (1) {
        read_word(word, in);
        if (feof(in)) break;
        vocab[search_vocab(word)].cn += 10000;
    }
    fclose(in);
}

int main(int argc, char** argv) {
    char input_filename[MAX_STRING];
    char output_filename[MAX_STRING];
    char vocab_filename[MAX_STRING];
    char pw_filename[MAX_STRING];
    int i, build_vocab = 0, second_pass = 0, pw = 0;

    if ((i = get_arg_pos((char*) "--input", argc, argv)) > 0) strcpy(input_filename, argv[i]);
    if ((i = get_arg_pos((char*) "--output", argc, argv)) > 0) strcpy(output_filename, argv[i]);
    if ((i = get_arg_pos((char*) "--words", argc, argv)) > 0) {
        // Don't delete specified words
        pw = 1;
        strcpy(pw_filename, argv[i]);
    }
    if ((i = get_arg_pos((char*) "--min-count", argc, argv)) > 0) min_count = atoi(argv[i]);
    if ((i = get_arg_pos((char*) "--vocab", argc, argv)) > 0) strcpy(vocab_filename, argv[i]);
    if ((i = get_arg_pos((char*) "--build-vocab", argc, argv)) > 0) build_vocab = atoi(argv[i]);
    if ((i = get_arg_pos((char*) "--second-pass", argc, argv)) > 0) second_pass = atoi(argv[i]);


    vocab = (struct vocab_word *)calloc(vocab_max_size, sizeof(struct vocab_word));
    vocab_hash = (int *)calloc(vocab_hash_size, sizeof(int));

    if (!build_vocab) {
        FILE* f_input = fopen(input_filename, "r");
        FILE* f_output = fopen(output_filename, "w");

        read_vocab(vocab_filename);

        if (pw) update_word_counts(pw_filename);

        if (!second_pass) {
            process_text(f_input, f_output);
        } else {
            second_process_text(f_input, f_output);
        }

        fclose(f_input);
        fclose(f_output);
    } else {
        learn_vocab_from_train_file(input_filename);
        save_vocab(output_filename);
    }

    free(vocab);
    free(vocab_hash);

    return 0;
}
