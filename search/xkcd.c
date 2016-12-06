#include <stdio.h>

int main(int argc, char **argv) {

	// State machine with three modes.
	// m == 0 is search.
	// m == 1 is display.
	// m == 2 is ignore rest.
	int m=0;

	// Pointer t is used to step through the characters
	// of the target string.
	char *t = argv[1];

	int c = 0; // Hold character from stdin.
	
	// While we still have input.
	while (c != EOF) {

		// We are in mode 1, so display up to the end of the line.
		if (m == 1) {

			if (c == 10 || c == 13) {
				// End of line reached, go to mode 2.
				printf("\n");
				m = 2;
			} else {
				// Otherwise show the character (ignore specials).
				if (c > 32) putchar(c);
			}
		}

		// We are in mode 0, so search for the colour name.
		if (m == 0) {

			// See if we are still inside the sequence of characters
			// that makes up the target string.
			if (c == *t) {
				// Yes, we are - next test will be for the next character.
				t++;

				// And if we are now at the end of the target string then
				// we've found it - it's a complete match.
				if (*t == 0) {

					// Got a match, so switch to mode 1.
					m = 1;

					// And print the colour name with the arrow.
					printf("%s -> ", argv[1]);

				}

			} else {

				// Ok, this character didn't match. So go back to the start.
				t = argv[1];
			}
		}

		// Get the next character from stdin.
		c = getchar();
	}
}
