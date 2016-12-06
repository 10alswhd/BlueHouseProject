#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordsearch.h"
	
// counts the number of newlines in the input,
// i.e. the number of rows.
int count_rows(char string[]) {
	
	int len = strlen(string);
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (string[i] == '\n')
			count++;
		else if (string[i] == '\r') {
			if (i + 1 < len && string[i + 1] == '\n') {
				count++;
				i++;
			}
			else
				count++;
		}
	}
	
	return string[len - 1] == '\n' ? count : count + 1;
}

// counts the number of characters per line.
// returns -1 if the number of characters is not the same for every line.
int count_cols(char string[]) {
	
	int rows = count_rows(string);
	
	int count = 0;
	int last_count = -1;
	int total = 0;
	
	int len = strlen(string);
	
	for (int i = 0; i < len; i++) {
		
		if (string[i] != '\n' && string[i] != '\r') {
			count++;
			total++;
		} else {
			// if not all the line lengths are the same, return -1.
			if (last_count != -1 && last_count != count)
				return -1;
				
			last_count = count;
			count = 0;
			
			while (string[i] == '\n' || string[i] == '\r')
				i++;
			
			i--; // seems weird, but it's to counteract the i++ in the for loop,
				 // since we've iterated just as much as we need with the while loop.
		}
		
	}
		
	// 1 needs to be subtracted to account for the null byte.
	return (total - 1) / rows;

}
	
int init_matrix(char matrix[MAX_MAT_SIZE][MAX_MAT_SIZE], char string[]) {
	
	int rows = count_rows(string);
	int cols = count_cols(string);

	// verify the preconditions
	if (cols == -1) {
		printf("Error, the line lengths are not equal in the input.");
		exit(1);
	} else if (cols != rows) {
		printf("Error, the number of rows and columns is not equal.");
		exit(1);
	}

	// first, initialize all the values to null.
	for (int i = 0; i < MAX_MAT_SIZE; i++) {
		for (int k = 0; k < MAX_MAT_SIZE; k++) {
			matrix[i][k] = '\0';
		}
	}
	
	int j = 0; // used to index into the string;
	
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < rows; k++) {
			if (string[j] == '\0')
				return 0; // failure!!!
			while (string[j] == '\n' || string[j] == '\r')
				j++; // increment j so it skips the newlines in the string
			matrix[i][k] = string[j];
			j++; // increment here so we advance normally through the string
		}
	}
	
	// the function returns rows so that the caller
	// can get info on how big of a square matrix the result effectively is.
	return rows;
	
}
		
void search_word(char matrix[MAX_MAT_SIZE][MAX_MAT_SIZE], char word[MAX_WORD_LEN], char direction, int matsize) {
	
	// first, if the direction argument is invalid, we can't continue.
	if (!(direction == 'U' ||
		  direction == 'D' ||
		  direction == 'L' ||
		  direction == 'R' )) {
		
		printf("Error, the `direction` argument must be one of 'U', 'D', 'L', 'R'.");
		exit(1);
	
	}
	
	// i is the index into the word to be advanced when checking it against the matrix.
	// j and k are the offsets to be changed when checking the word.
	// x and y are the coordinates to be changed when iterating over the matrix.
	int i, j, k, x, y;
	
	// these affect the direction j and k change in when searching
	int dj, dk;
	
	// these always need to start at 0.
	j = 0;
	k = 0;
	i = 0;
	
	// we pretty obviously need this.
	int word_len = strlen(word);
	
	// set up dj and dk based on what direction we're searching.
	switch (direction) {
		case 'R':
			dj = 1;
			dk = 0;
			break;
		case 'L':
			dj = -1;
			dk = 0;
			break;
		case 'U':
			dj = 0;
			dk = -1;
			break;
		case 'D':
			dj = 0;
			dk = 1;
			break;
		default:
			break;
	}
	
	
	// here we initialize y and x and then search the matrix
	for (y = 0; y < matsize; y++) {
		for (x = 0; x < matsize; x++) {
			
			// if the first character of the word matches, start searching.
			if (matrix[y][x] == word[0]) {
				
				// reset j, k, and i for the check
				j = 0;
				k = 0;
				i = 0;
				
				// as long as we're still within the bounds of the matrix,
				// and the word characters match, we can keep checking.
				while ((y + k < matsize) && (y + k >= 0) &&
					   (x + j < matsize) && (x + j >= 0) &&
					   (matrix[y + k][x + j] == word[i])) {
					
					//printf("comparing matrix[%d][%d] (%c) to word[%d] (%c)\n", y + k, x + j, matrix[y + k][x + j], i, word[i]);
					
					// advance through the word
					i++;
					
					// adjust j and k based on the iteration direction
					j += dj;
					k += dk; 
					
					// if this is true, all the characters matched.
					if (i == word_len) {
						// notify of the match
						printf("matched at (%d, %d) in direction %c\n", x, y, direction);
						
						// and break out of the checking loop this time
						break;
					}
					
				}				
				
			}
		
		}
		
	}
	
}


// reads data from the file argv[1] and matches it with the inputted words.
void main(int argc, char* argv[]) {
	
	// prepare file handle and data location
	char file_data[MAX_MAT_SIZE * MAX_MAT_SIZE];
	FILE *file_handle = fopen(argv[1], "r");
	
	int data_index = 0;
	char next_char;
	
	// read all of the file's data into a buffer
	while (!feof(file_handle)) {
		
		next_char = fgetc(file_handle);
		file_data[data_index] = next_char;
		data_index++;
		
		if (data_index >= 128) {
			printf("Error, file data is too long! The data array was too small!");
			exit(1);
		}
		
	}
	
	// add the null byte to the end so it can be used as a valid string
	file_data[data_index] = '\0';
	
	printf("rows: %d\n", count_rows(file_data));
	printf("cols: %d\n", count_cols(file_data));
	printf("\n");
	
	// declare and initialize the matrix of characters to search
	char matrix[MAX_MAT_SIZE][MAX_MAT_SIZE];
	int mat_size = init_matrix(matrix, file_data);

	// print out the data for the user to see
	for (int y = 0; y < mat_size; y++) {
		for (int x = 0; x < mat_size; x++) {
			printf("%c ", matrix[y][x]);
		}
		printf("\n");
	}

	// declare the variable to hold the user input
	char input[MAX_WORD_LEN];
	
	// the main loop for getting/responding to input
	while (1) {
		// prompt and receive input data		
		printf("\nenter a word to search for: ");
		gets(input);
		
		// ensure the input will be a valid string
		input[MAX_WORD_LEN - 1] = '\0';
		if (strlen(input) < 1) {
			printf("No input provided; ending.\n");
			exit(0);
		}
		
		// search for the word in all directions.
		search_word(matrix, input, 'U', mat_size);
		search_word(matrix, input, 'D', mat_size);
		search_word(matrix, input, 'L', mat_size);
		search_word(matrix, input, 'R', mat_size);
	
	}
	
}
