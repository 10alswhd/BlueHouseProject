#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline unsigned int
min(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned int m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}

int edit_distance(char *a, char *b) {
	if (a[0] == '\0' && b[0] == '\0') // finished
		return 0;

	if (a[0] == '\0') // return the number of chars lesf in b
		return strlen(b);

	if (b[0] == '\0') // return the number of chars to remove from a
		return strlen(a);

	if (a[0] == b[0])
		return edit_distance(a+1, b+1);

	int distance_change = edit_distance(a+1, b+1) + 1;
	int distance_addition = edit_distance(a, b+1) + 1;
	int distance_deletion = edit_distance(a+1, b) + 1;

	return min(distance_change, distance_addition, distance_deletion);
}


int main(int argc, char *argv[]) {
	if (argc < 3)
		return 0;

	char *a = argv[1];
	char *b = argv[2];

	int distance = edit_distance(a, b);

	printf("The distance between %s and %s is %d.\n", a, b, distance);

	return 0;
}
