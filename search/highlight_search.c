#include <stdio.h>
#include <string.h>

char* highlight_word(char* text, char* word, char* final);

int main(int argc, char *argv[]){

    char tracks[][80] = {"i am not a dog you fool",
                         "what do you mean by this, bear?",
                         "now this is a silly situation",
                         "I got lost on the way to work",
                         "I lost my heart here",
                         "what do you think about this?",
                        };

    int num = sizeof(tracks) / 80;
    printf("Num of tracks: %d\n", num);
    printf("terms to search for: %d\n", argc - 1);
    int i;
    int j;
    for(i = 1; i < argc; i++){
        char* term = argv[i];
        printf("-= SEARCH TERM TO PROCESS: %s =-\n", term);
        puts("-----------------------------------\n");
        for (j = 0; j < num; j++){
            char* match = strstr(tracks[j], term);
            if (match){
                printf("track[%d]:\n", j, tracks[j]);
                char word[40] = "";
                strncpy(word, match, strlen(term));
                char final[100];
                highlight_word(tracks[j], term, final);
                printf("match: %s\n", final);

            }
        }
    }
    return 0;
}

char* highlight_word(char* text, char* word, char* final){

    char* right = strstr(text, word) + strlen(word);
    //printf("sizes - text: %d, word: %d, right: %d\n", strlen(text), strlen(word), strlen(right));
    //printf("'%s'\n'%s'\n'%s'\n", text, word, right);

    int i;
    int j;
    int limit = strlen(text) - (strlen(word) + strlen(right));
    for(i = 0;i < limit;i++){
        final[i] = text[i];
        }
    final[i] = '[';
    j = i;
    i++;
    limit = strlen(text) - strlen(right);
    for(;j < limit;i++, j++){
        final[i] = text[j];
        }
    final[i] = ']';
    j = i;
    i++;
    final[i] = ' ';
    i++;
    limit = strlen(text);
    for(;j < limit;i++, j++){
        final[i] = text[j];
        }
    final[i] = '\0';
    //printf("final(%d): '%s'\n", strlen(final), final);
    text = final;
    }
