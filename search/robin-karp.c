#include <stdio.h>
#include <stdlib.h>

typedef long hash_t;
typedef long strlen_t;


char *string = NULL;
char *sample = NULL;
strlen_t n = 0;
const int base = 157;
hash_t base_n = 1;

void init_glob ()
{
    strlen_t l = 0;
    scanf("%ld %ld", &l, &n);

    string = (char *)malloc(l * sizeof(char));
    sample = (char *)malloc(n * sizeof(char));

    n = 0;

    scanf("%s", string);
    scanf("%s", sample);

    while (sample[n] != '\0') {
        n += 1;
        base_n *= base;
    }
    base_n /= base;

}

void free_glob ()
{
    free(string);
    free(sample);
}

hash_t hash (char *str)
{
    hash_t temp = 0;
    strlen_t i = 0;
    while (i < n) {
        temp *= base;
        temp += str[i];
        i += 1;
    }
    return temp;
}

inline hash_t rehash (char old_ch, char new_ch, hash_t old_hash)
{
    return (old_hash - old_ch * base_n) * base + new_ch;
}

strlen_t search ()
{
    hash_t h_samp = hash (sample);     // hash sample

    hash_t h_curr = hash (string);     // hash origin string

    strlen_t i = 0;
    strlen_t j = 0;
    strlen_t k = 0;
    strlen_t result = -1;

    while (result == -1) {
        while (h_curr != h_samp && string[n + i] != '\0') {
            h_curr = rehash(string[i], string[n + i], h_curr);
            i += 1;
        }
        if (h_curr == h_samp) {
            j = i;
            k = 0;
            while (k < n && string[j] == sample[k]) {
                k += 1;
                j += 1;
            }
            if (k == n)
                result = i;
			else
				printf("ff\n");
        }
        if (string[n + i] == '\0') {
            break;
        }
    }
    return result;
}

int main(void)
{
    init_glob();

    strlen_t res = search();
    printf("%ld\n", res);

    free_glob();
    return 0;
}
