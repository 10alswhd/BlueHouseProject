/*
 * eqver.c
 * Copyright (C) 2014 Michael Cook <mcook@mackal.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int fileexists(const char *filename);

int main(int argc, char *argv[])
{
    long fSize = 0;
    size_t search_length = 0;
    size_t result = 0;
    int found = 0;
    FILE *pFile = NULL;
    char *pBuffer = NULL;
    char *search = "Client Version: %s %s";
    char *filename = "eqgame.exe";
    /* these shouldn't ever really need to be this big */
    char build_date[25] = { 0 };
    char build_time[25] = { 0 };
    unsigned int pos = 0;
    unsigned int index = 0;
    char cur = 0;

    search_length = strlen(search);

    if (argc == 2 && fileexists(argv[1]))
        filename = argv[1];

    printf("Finding version of %s\n", filename);

    pFile = fopen(filename, "rb");
    if (!pFile) {
        fprintf(stderr, "File not found\n");
        exit(2);
    }

    /* get size of binary */
    fseek(pFile, 0, SEEK_END);
    fSize = ftell(pFile);
    rewind(pFile);

    /* memory allocate */
    pBuffer = (char *)malloc(sizeof(char) * fSize);
    if (!pBuffer) {
        fprintf(stderr, "Memory error\n");
        exit(12);
    }

    /* copy EXE into memory buffer */
    result = fread(pBuffer, 1, fSize, pFile);
    if (result != fSize) {
        fprintf(stderr, "Reading error\n");
        exit(1);
    }
    /* copied, can close this */
    fclose(pFile);

    while (pos <= fSize) {
        /* current char at pos in buffer */
        cur = pBuffer[pos];
        /* matches index byte we want */
        if (cur == search[index]) {
            /* increase index to next need byte */
            index++;
            if (index > search_length) {
                /* we matched the whole string, time to exit and print */
                found = 1;
                break;
            }
        } else {
            /* we didn't match and we're not done yet, so reset */
            index = 0;
        }
        pos++;
    }

    if (found) {
        /* prune off remaining nulls */
        while (pBuffer[pos] == 0x0)
            pos++;

        strncpy(build_date, pBuffer + pos, 25);
        build_date[24] = '\0';
        strncpy(build_time, pBuffer + pos + strlen(build_date) + 1, 25);
        build_time[24] = '\0';

        printf(search, build_date, build_time);
        putchar('\n');
    } else {
        printf("Couldn't determine version\n");
    }

    free(pBuffer);

    return 0;
}

int fileexists(const char *filename)
{
    struct stat buf;
    return (stat(filename, &buf) == 0);
}
