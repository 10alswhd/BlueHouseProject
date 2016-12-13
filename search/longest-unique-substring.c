#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* lus(char* s)
{
	int s_len = strlen(s), i, j;

	int ascii[256]; 
	memset(ascii, -1, 256*4);

	int max = 0;
	int curr_max = 0;
	int max_pos_last;

	printf("%d\n", s_len);

	// loop through all letters
	for (i = 0; i < s_len; i++)
	{
		// if current letter didn't show up yet,
		// mark it
		if (ascii[s[i]] == -1)
		{
			printf("new %c \n", s[i]);
			ascii[s[i]] = i;
			curr_max++;
			max_pos_last = i;
		}
		// if it did show up already
		else
		{
			if (curr_max > max)
			{
				max = curr_max;
				max_pos_last = i-1;
			}

			// set i to the last occurence of current letter
			// the for loop will increment it by 1, so that
			// we continue our search one character after the
			// last occurence of current character
			i = ascii[s[i]];
			curr_max = 0;
			printf("reverting to %d\n", i);

			// clear array
			memset(ascii, -1, 256*4);

		}
	}

	// make sure max is up to date
	if (curr_max > max)
	{
		max = curr_max;
		max_pos_last = i-1;
	}

	// get the substring
	char* out = (char*)malloc(sizeof(char) * max + 1);
	out[max] = '\0';
	strncpy(out, &s[max_pos_last - max], max);

	return out;

}


int main()
{
	char* s = "abeadabrd";

	printf("%s\n", lus(s));
}
