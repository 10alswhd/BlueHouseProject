#include <stdlib.h>
#include <stdio.h>

typedef struct tagPATTERN {
    unsigned long hash;
    int pattern_from;
} PATTERN;
PATTERN *history;

int history_count = 0;
int queue_bottom;

unsigned long make_hash(char* pattern)
{
    unsigned long hash;
    int i;

    hash = 0;
    for (i = 0; i < 8; i++) {
        hash |= ((unsigned long)pattern[7 - i]) << (i * 4);
    }

    return hash;
}

void pattern_from_hash(char* pattern, unsigned long hash) 
{
    int i;
    for (i = 0; i < 8; i++) {
        pattern[7 - i] = (char)((hash >> (i * 4)) & 0xf);
    }
}

void save_history(char* pattern, int pattern_from)
{
    int i;
    unsigned long hash;

    hash = make_hash(pattern);
    for (i = 0; i < history_count; i++) {
        if (history[i].hash == hash)
            return;
    }

    history_count++;
    history = (PATTERN*)realloc(history, sizeof(PATTERN) * history_count);
    if (history == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    history[history_count - 1].hash = hash;
    history[history_count - 1].pattern_from = pattern_from;
}

int solve_7puzzle(void)
{
    int blank_pos;
    unsigned long hash;
    char pattern[8];

    queue_bottom = 0;
    while (queue_bottom != history_count) {
        hash = history[queue_bottom].hash;
        if (hash == 0x12345670)
            return 1;

        pattern_from_hash(pattern, hash); 
        for (blank_pos = 0; blank_pos < 8; blank_pos++) {
            if (pattern[blank_pos] == 0)
                break;
        }

        // move blank upward
        if (blank_pos > 3) {
            pattern[blank_pos] = pattern[blank_pos - 4];
            pattern[blank_pos - 4] = 0;

            save_history(pattern, queue_bottom);
            pattern_from_hash(pattern, hash);
        }
        // move blank downward
        if (blank_pos < 4) {
            pattern[blank_pos] = pattern[blank_pos + 4];
            pattern[blank_pos + 4] = 0;

            save_history(pattern, queue_bottom);
            pattern_from_hash(pattern, hash);
        }
        // move blank leftward
        if (blank_pos != 0 && blank_pos != 4) {
            pattern[blank_pos] = pattern[blank_pos - 1];
            pattern[blank_pos - 1] = 0;

            save_history(pattern, queue_bottom);
            pattern_from_hash(pattern, hash);
        }
        // move blank rightward
        if (blank_pos != 3 && blank_pos != 7) {
            pattern[blank_pos] = pattern[blank_pos + 1];
            pattern[blank_pos + 1] = 0;

            save_history(pattern, queue_bottom);
            pattern_from_hash(pattern, hash);
        }
        queue_bottom++;
    }
    return 0;
}


int main(void)
{
    int last, i;
    char pattern[8] = {2, 7, 1, 4, 5, 0, 3, 6};

    history = NULL;
    save_history(pattern, -1);

    if(solve_7puzzle() != 0) {
        last = -1;
        while (last != queue_bottom) {
            for(i = queue_bottom; history[i].pattern_from != last;) {
                i = history[i].pattern_from;
            }
            last = i;

            pattern_from_hash(pattern, history[last].hash);
            for (i = 0; i < 8; i++) {
                printf("%c ", pattern[i] ? pattern[i] + '0' : ' ');
                if (i % 4 == 3)
                    printf("\n");
            }
            getchar();
        }
    }

    free(history);
    return EXIT_SUCCESS;
}
