#include "stdio.h"

int BinSearch(int[], int, int, int);

int main () {
	int a[] = {3,6,7,9,11,23,32};
	printf("%d\n", BinSearch(a,4,0,6));
}

int BinSearch(int a[], int x, int i, int j) {
	int c;
	if(i > j) {
		return -1;
	}
	c = (i+j)/2;
	if (a[c] == x) {
		return c;
	}
	if (x < a[c]) {
		return BinSearch(a, x, i, c-1);
	} else {
		return BinSearch(a, x, c+1, j);
	}
}
