#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int brutesearch(char *p, char *a)
{
    int i, j, M = strlen(p), N = strlen(a);
    for (i = 0, j = 0; j < M && i < N; i++, j++)
    {
        if (a[i] != p[j])
        {
            i -= j-1;
            j = -1;
            i--;
        }
    }
    if (j == M)
    {
        return i-M;
    } else {
        return i;
    }
}

void printMatch(char *p, char *s)
{
    int cnt = brutesearch(p, s);
    char *first;
    char *rest;
    char *middle;
    char ESC=27;

    first = malloc(sizeof(char) * cnt+1);
    middle = malloc(sizeof(char) * strlen(p)+1);
    rest = malloc(sizeof(char) * strlen(s)-cnt-strlen(p)+1);

    if (cnt < strlen(s))
    {
        first = strncpy(first, s,cnt);
        middle = strncpy(middle, &s[cnt],strlen(p));
        rest = strncpy(rest,&s[cnt+strlen(p)],strlen(s)-strlen(p)-cnt);

        printf("%s", first);
        printf("%c[1m",ESC);
        printf("%s", middle);
        printf("%c[0m",ESC);
        printf("%s\n", rest);
    } else {
        printf("%s matches nothing in %s\n", p, s);
    }
    free(first);
    free(middle);
    free(rest);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage:\n");
        printf("%s \"pattern\" \"string to search\"\n", argv[0]);
        printf("\nExample:\n");
        printf("%s \"hello\" \"hello world\"\n",argv[0]);
        return 1;
    } else {
        printMatch(argv[1],argv[2]);
        return 0;
    }
}
