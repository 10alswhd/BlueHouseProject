#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_failure_fn(char *p, int lenp, int table[]);
int search_kmp(char *s, int lens, char *p, int lenp, int table[]);

int
main()
{
    int i;
    char *str = "ABC ABCDAB ABCDABCDABDE";
    char *pattern = "ABCDABD";
    int lens = strlen(str);
    int lenp = strlen(pattern);
    int table[lenp];

    create_failure_fn(pattern, lenp, table);
    printf("%d\n", search_kmp(str, lens, pattern, lenp, table));
}

// create_failure_fn is creates a failure function for pattern  p. Where
// table[0] = -1, table[1] = 0 and table[i] is the value of the longest
// suffix that also a prefix of p[0:i-1]. Such that 1 < i < lenp.
void
create_failure_fn(char *p, int lenp, int table[])
{
    // the current position we are computing in table
    int pos = 2;
    // the zero-based index in pattern p of the next character of the current
    // candidate substring
    int cnd  = 0;

    table[0] = -1;
    table[1] = 0;

    while(pos < lenp) {
        // first case: the substring continues
        if (p[pos-1] == p[cnd]) {
            cnd += 1;
            table[pos] = cnd;
            pos += 1;
        } else if(cnd > 0) {
            // second case: it doesn't, but we can fall back
            cnd = table[cnd];
        } else {
            // third case: we have run out candidates
            table[pos] = 0;
            pos += 1;
        }
    }
}

// search_kmp search a pattern using KMP algorithm.
int
search_kmp(char *s, int lens, char *p, int lenp, int table[])
{
    // the beginning of the current match in string s
    int m = 0;
    // the position of the current char in pattern p
    int i = 0;

    while(m+i < lens) {
        if(p[i] == s[m+i]) {
            if(i == lenp-1)
                return m;
            i += 1;
        } else {
            if(table[i] > -1) {
                m += i - table[i];
                i = table[i];
            } else {
                i = 0;
                m += 1;
            }
        }
    }

    // pattern p not found in string s
    return -1;
}
