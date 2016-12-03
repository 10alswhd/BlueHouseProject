#include <stdio.h>
#include <string.h>

// See: https://en.wikibooks.org/wiki/Algorithm_implementation/Strings/Levenshtein_distance#C

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
 
int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

const int num_items = 10;

struct _witem
{
	char data[80];
	int rating;
};

typedef struct _witem witem;

void swapwitem(witem* a, witem* b) {
	witem* swap;
	swap = a;
	a = b;
	b = swap;
}

void witemsort(witem array[]) {
	for (int i = num_items-1; i >= 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (array[j].rating > array[j+1].rating)
			{
				witem swap = array[j];
				array[j] = array[j+1];
				array[j+1] = swap; 
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc > 1) {

		witem matchwords[num_items];
		// firefox, thunderbird, internet, sublime, gedit
		
		strcpy(matchwords[0].data, "firefox");
		strcpy(matchwords[1].data, "thunderbird");
		strcpy(matchwords[2].data, "internet");
		strcpy(matchwords[3].data, "sublime");
		strcpy(matchwords[4].data, "gedit");
		strcpy(matchwords[5].data, "minecraft");
		strcpy(matchwords[6].data, "handbrake");
		strcpy(matchwords[7].data, "music");
		strcpy(matchwords[8].data, "blender");
		strcpy(matchwords[9].data, "inkscape");

		char* const word = argv[1];

		printf("Matching: %s\n", word);

		puts("--------------------");

		for (int i = 0; i < num_items; ++i)
		{
			matchwords[i].rating = levenshtein(matchwords[i].data, word) + 1;
		}

		witemsort(matchwords);

		for (int i = 0; i < num_items; ++i)
		{
			printf("%s -> %d\n", matchwords[i].data, matchwords[i].rating);
		}
		puts("--------------------");

		printf("Best Match: %s \n", matchwords[0].data);

	} else {
		printf("Usage: %s <word>\n", argv[0]);
	}

	return 0;
}
