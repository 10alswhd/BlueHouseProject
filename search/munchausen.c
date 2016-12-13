// calculate munchausen numbers
#include <stdio.h>
#include <math.h>

int limit = 5000; // the upper bound of the search

int i;
int main() {
	for (i = 1; i < limit; i++) {
		// loop through each digit in i
		// e.g. for 1000 we get 0, 0, 0, 1.
		int number = i;
		int sum = 0;
		while (number > 0) {
			int digit = number % 10;
			number = number / 10;
			// find the sum of the digits 
			// raised to themselves 
			sum += pow(digit, digit);
		}
		if (sum == i) {
			// the sum is equal to the number
			// itself; thus it is a 
			// munchausen number
			printf("%i (munchausen)\n", i);
		} 
	}	
	return 0;
}
