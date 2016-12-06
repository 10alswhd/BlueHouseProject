#include <stdio.h>
#include <stdlib.h>

#define WIDTH 4
#define HEIGHT 4
#define LENGTH 16 // WIDTH * HEIGHT
#define MAX_HITS 11 // increase this to use your laptop as a stove

// -----------------------------------------------------------------------------
// A board is represented as an integer. I'm choosing integers simply because 
// they're easy to copy and I don't need to worry about memory allocation 
// (unlike arrays). 
// 
// We only need a 4x4 board with 16 possible positions, so 16 bits are enough to 
// store the board (int is by standard at least 16 bits). The right-most bit 
// is the starting position 1. Ones represent a mole and zeros an empty hole. 
// 
// For example, the following board contains moles at positions 2, 3 and 5:
// 
//   board:     0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 0
//                            ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑
//   positions:           ... 9 8 7 6 5 4 3 2 1
// 
// The functions below are used to manipulate boards.
// -----------------------------------------------------------------------------

// Returns the bit at the given position of the board.
// Can be 1 (mole) or 0 (no mole).
int at(int board, int pos) {
    return (board >> pos-1) & 1;
}

// Toggles the bit at the given position and returns the resulting board.
// So if the bit at pos is 1, it changes to 0 and vice versa.
int toggle(int board, int pos) {
    if (pos >= 1 && pos <= LENGTH)
        board ^= 1 << pos-1;
    return board;
}

// Applies a "hit" at the specified position and returns the resulting board.
int hit(int board, int pos) {
    board = toggle(board, pos);
    board = toggle(board, pos+WIDTH); // no need to worry about bounds here,
    board = toggle(board, pos-WIDTH); // as toggle() does the checks             
    // But we do need to check if pos is on the left or right edge of the board, 
    // because we don't want to toggle position 5 if 4 was hit.
    if (pos % WIDTH != 0)
        board = toggle(board, pos+1);
    if (pos % WIDTH != 1)
        board = toggle(board, pos-1);
    return board;
}

// Prints the board in the same 
// order as in the assignment:
//   
//   [13] [14] [15] [16]
//   [ 9] [10] [11] [12]
//   [ 5] [ 6] [ 7] [ 8]
//   [ 1] [ 2] [ 3] [ 4]
// 
// Useful for debugging.
void display(int board) {
    int i, j;
    printf("\n");
    for (i = 3; i >= 0; i--) {
        for (j = 1; j <= 4; j++) {
            printf("%s ", at(board, i * WIDTH + j) ? " O" : " -" );
        }
        printf("\n");
    }
    printf("\n");
}

// Returns a board containing moles at the positions specified in moles array.
int board_from_moles(int *moles, int len) {
    int i;
    int board = 0;
    for (i = 0; i < len; i++) {
        board = toggle(board, moles[i]);
    }
    return board;
}

// Returns the length of an array of hits. Since only 1 to 16 are valid 
// positions, we can check the length by counting until we reach a 0.
int length(int *hits) {
    int len = -1;
    while (hits[++len]);
    return len;
}

// Appends a number to an array of hits
int* append(int *hits, int hit) {
    hits[length(hits)] = hit;
    return hits;
}

// Performs depth-first search to a prespecified depth.
// http://en.wikipedia.org/wiki/Depth-limited_search
int* depth_first(int board, int depth) {
    int i, pos, *hits;
    if (board == 0) {
        // if the board is solved,
        // return allocated memory for the array of hits
        return calloc(MAX_HITS+1, sizeof(int));
    } else if (depth > 0) {
        // otherwise, if maximum depth is not reached...
        for (pos = 1; pos <= LENGTH; pos++) { // for all positions on the board...
            if (at(board, pos)) {             // if there is a mole at current position...
                hits = depth_first(hit(board, pos), depth-1); // hit it and initiate another search on the result
                if (hits)                     // if the search does not return NULL...
                    return append(hits, pos); // append the current position to the array of hits
            }
        }
    }
    return NULL;
}

// Calls depth_first(), increasing the depth each time, until a solution is found.
// http://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search
int* search(int board) {
    int depth = 1;
    int* result;
    while (depth < MAX_HITS) {
        result = depth_first(board, depth);
        if (result)
            return result;
        else
            depth++;
    }
    return NULL;
}

int main() {

    int i = 0;
    int len = 0;
    int board;
    int moles[LENGTH];
    int emptied;
    int *result;

    char c;
    char buffer[10];

    printf("Enter the positions of the moles: "); 

    do {
        c = getchar();
        if (c >= '0' && c <= '9') {
            buffer[i++] = c;
            emptied = 0;
        } else if (!emptied) {
            sscanf(buffer, "%d", &moles[len++]);
            emptied = 1;
            i = 0;
        }
    } while (c != '\n' && c != EOF);

    board = board_from_moles(moles, len);
    result = search(board);

    if (result != NULL) {
        for (i = length(result)-1; i >= 0; i--)
            printf("%d ", result[i]);
        printf("\n");
    } else {
        printf("Could't find solution.\n");
    }

    free(result);

    return 0;
}
