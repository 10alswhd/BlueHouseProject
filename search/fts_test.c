#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

int mystrcmp (const void *vf, const void *vs)
{
	const char * const *f = vf;
	const char * const *s = vs;
	int i;

	for (i = 0; (*f)[i] && (*s)[i]; ++i)
		if ((*f)[i] < (*s)[i])
			return -1;
		else if ((*f)[i] > (*s)[i])
			return +1;

	return 0;
}

#define N	256

int main (int argc, char *argv[])
{
	int i, pos, n_search = 0, n_result = 0;
	static char input_buf[N], *input = input_buf;
	char *buf, **sindex;
	char *fn = argc > 1 ? argv[1] : "sometext.txt";
	long filelen;
	FILE *fp;

	setlocale(LC_CTYPE, "");

	fp = fopen(fn, "rb");
	if (fp == NULL) {
		fprintf(stderr, "fopen on %s failed!\n", fn);
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	filelen = ftell(fp);
	fprintf(stderr, "File length: %lu\n", filelen);
	buf = malloc((filelen/1024 + 1) * 1024 * 4);
	if (buf == NULL) {
		fprintf(stderr, "malloc failed!\n");
		fclose(fp);
		return 2;
	}
	sindex = (char **)(buf + ((filelen/1024 + 1) * 1024));
	fprintf(stderr, "buf: %p, sindex: %p\n", buf, sindex);
	fseek(fp, 0, SEEK_SET);
	fprintf(stderr, "Read: %d\n", fread(buf, 1, filelen, fp));
fprintf(stderr, "Clock: %6.2f sec\n", (double)clock()/CLOCKS_PER_SEC);

	for (pos = i = 0; pos < filelen; ++i) {
		sindex[i] = buf + pos;
		// Check if this byte starts a double-byte Big5-encoded character
		if (buf[pos++] & 0x80)
			pos += 1;
	}
	fprintf(stderr, "Items: %d\n", i);

	qsort(sindex, i, sizeof(char *), mystrcmp);
fprintf(stderr, "Clock: %6.2f sec\n", (double)clock()/CLOCKS_PER_SEC);

	printf("Input phrase to be search\n");
	while (fgets(input, N - 1, stdin)) {
		int len = strlen(input);
		const char **first;

		if (*input == '\n') continue;

		++n_search;
		input[len-1] = 0;	// remove new line
		printf("%s (%d):\n", input, len);
		first = bsearch(&input, sindex, i, sizeof(char *), mystrcmp);
		if (first == NULL) {
			printf("%s not found!\n", input);
			continue;
		}

		while (mystrcmp(&input, first) == 0) {
			printf("%d", *first - buf); // printf(" -> %72.72s\n", *first);
			++first;
			++n_result;
		}
		printf("\n");
	}
	fprintf(stderr, "Searchs: %d, results: %d, %8.2f per search\n",
		n_search, n_result, (double)n_result/n_search);
fprintf(stderr, "Clock: %6.2f sec\n", (double)clock()/CLOCKS_PER_SEC);

	free(buf);
	fclose(fp);

	return 0;
}
