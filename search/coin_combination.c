#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int DENOMINATIONS[] = {50, 20, 10, 5, 2, 1};

/* Note that both `prefixSize` and ``*pBufSize`` are sizes in bytes */
void coinCombination(int amount, int *prefix, int prefixSize, int smallestCoinIndex, int **pBuf, int *pBufSize) {
    if (smallestCoinIndex >= sizeof(DENOMINATIONS)/sizeof(*DENOMINATIONS))
        return;

    if (amount == 0) {
        // Warning: allocation failure is not handled
        // Warning: inefficient memory allocation
        int newSize = *pBufSize + prefixSize + sizeof(int);
        *pBuf = realloc(*pBuf, newSize);
        memcpy(*pBuf + *pBufSize / sizeof(int), prefix, prefixSize);
        (*pBuf)[newSize/sizeof(int) - 1] = 0;
        *pBufSize = newSize;

        return;
    }

    // case 1: Search results which have the DENOMINATIONS[smallestCoinIndex] in current position
    int largestCoin = DENOMINATIONS[smallestCoinIndex];
    if (amount >= largestCoin) {
        // Malloc new prefix (don't use realloc, otherwise the original `prefix` may be freed)
        int newPrefixSize = prefixSize + sizeof(int);
        int *newPrefix = malloc(newPrefixSize);
        if (prefixSize != 0)
            memcpy(newPrefix, prefix, prefixSize);
        newPrefix[newPrefixSize/sizeof(int)-1] = largestCoin;

        coinCombination(amount - largestCoin, newPrefix,
                newPrefixSize, smallestCoinIndex, pBuf, pBufSize);

        free(newPrefix);
    }

    // case 2: Search results which have coins < DENOMINATIONS[smallestCoinIndex] in current position
    coinCombination(amount, prefix, prefixSize, smallestCoinIndex + 1, pBuf, pBufSize);
}

int main(int argc, char *argv[])
{
    int *buf = 0, bufSize = 0;
    int amount = 0;

    while (1) {
        printf("Amount in cents: ");
        scanf("%d", &amount);
        coinCombination(amount, 0, 0, 0, &buf, &bufSize);

        // Print the results
        int bufSizeInInt = bufSize / sizeof(int);
        int i = 0;
        for (; i < bufSizeInInt; ++i) {
            if (buf[i] == 0)
                printf("\n");
            else
                printf("%d ", buf[i]);
        }

        free(buf);
        buf = 0;
        bufSize = 0;
    }

    return 0;
}
