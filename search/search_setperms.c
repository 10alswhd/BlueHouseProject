#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// fast int
#if __WORDSIZE == 64
typedef unsigned long int uint_fast_t;
#define UINT_FAST(c) c ## UL
#else
typedef unsigned int uint_fast_t;
#define UINT_FAST(c) c ## U
#endif

typedef uint8_t alphabet;

// there is terminator so can't be longer than 255
typedef uint_fast8_t sublen_t;

typedef uint_fast_t chunk_t;

struct example {
    const alphabet * substr;
    const alphabet * string;
};

struct example examples[] = {
    {.substr = "ron", .string = "xxxxxxronxxxxnorxxxxxrno"},
    {.substr = "ron", .string = "ronronron"},
    {.substr = "ABC", .string = "ABCRTYBACXCAB"},
};

enum {
    alphabet_len = UINT8_MAX + 1,
    chunk_bits   = sizeof(chunk_t)*8,
    chunks       = (alphabet_len + chunk_bits - 1)/chunk_bits,
    no_examples  = sizeof(examples)/sizeof(struct example) 
};

struct state {
    const alphabet *pos;
    sublen_t sublen;
    sublen_t len;
    chunk_t member[chunks];
    chunk_t found[chunks];
    const alphabet *backref[alphabet_len];
};

#define shift(i) ((i) % chunk_bits)
#define chunk_no(i) ((i) / chunk_bits)
#define chunk(m, i) ((m)[chunk_no(i)])
#define mask(i) (UINT_FAST(1) << shift(i))
#define is_set(m, i) (!!(chunk(m, i) & mask(i)))
#define set(m, i) (chunk(m, i) |= mask(i))
#define reset(m, i) (chunk(m, i) &= ~(mask(i)))

void substr_init_state(struct state *state, const alphabet *substr) {
    for (; *substr; ++substr)
        if (!is_set(state->member, *substr)) {
            set(state->member, *substr);
            ++state->sublen;
        };
}

size_t search(struct state *state, const int print) {
    size_t count = 0;
    for (; *state->pos; ++state->pos) {
        if (is_set(state->member, *state->pos)) {
            // char belongs to substring

            if (is_set(state->found, *state->pos)) {
                // already found so remove all characters found before this
                // char found last time
                for (const alphabet *p = state->pos - state->len + 1;
                        // begin current substring found so far
                        p < state->backref[*state->pos];
                        // while not previous position of current char
                        ++p) {
                    --state->len;            // subtract length
                    reset(state->found, *p); // remove from found
                } // don't touch current char bit, it's useless to reset and set same bit
            }
            else { // this character not found yet
                set(state->found, *state->pos);
                ++state->len;
            }
            state->backref[*state->pos] = state->pos;
            count += state->len == state->sublen; // count if found
            if (print && state->len == state->sublen) {
                for (const alphabet *p = state->pos - state->len + 1;
                        p <= state->pos; ++p)
                    putchar(*p);
                putchar(' ');
            }
        }
        else if (state->len) { // char doesn't belong to substring
            state->len = 0;
            for (unsigned i = 0; i < chunks; ++i)
                state->found[i] = 0;
        }
    }
    return count;
}

size_t count_occurences(const alphabet *pos, const alphabet *substr, const int print) {
    struct state state = {.pos = pos};
    substr_init_state(&state, substr);
    return search(&state, print);
}

int main(int argc, char *argv[]) {
    for (unsigned i = 0; i < no_examples; ++i) {
        printf("substr=%s in string=%s\n", examples[i].substr, examples[i].string);
        printf("\nfound=%zd times\n", count_occurences(examples[i].string, examples[i].substr, 1));
    }
    return 0;
}
