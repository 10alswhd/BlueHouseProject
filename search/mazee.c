#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N   5

typedef enum{BLACK, WHITE, START, END} tile;
typedef enum{UNDISCOVERED, DISCOVERED, PROCESSED}graph_state;

typedef struct {
    int x;
    int y;
}Coord;

graph_state status[N*N];
Coord*      parent[N*N];


Coord* process_coord(tile M[][N], int x, int y, Coord *parent);
Coord* search_maze(tile M[][N], Coord *start);

void initialize() {
    int i;

    for (i = 0; i < N*N; i++) {
        status[i] = UNDISCOVERED;
        parent[i] = NULL;
    }
    return;
}


/* Translate (x, y) into an index in a 1D array */
int translate_coord(int x, int y) {
    return (N*x) + (y+1);
}

/* Does (x, y) fall within the NxN matrix */
bool is_valid_coord(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

Coord* process_coord(tile M[][N], int x, int y, Coord *p) {
    int index = translate_coord(x, y);
    Coord *coord;
    if (status[index] == UNDISCOVERED) {
        coord = malloc(sizeof(Coord));
        coord->x = x;
        coord->y = y;
        parent[index] = (Coord*) p;
        return search_maze(M, coord);
    } else return NULL;
}

//dfs on maze
Coord* search_maze(tile M[][N], Coord *start) {

    int x = start->x;
    int y = start->y;
    int index = translate_coord(x, y);
    tile type = M[x][y];

    status[index] = DISCOVERED;
    if (type == END) 
        return start;
    else if (type == BLACK)
        return NULL;

    Coord *end;

    //check above
    if (is_valid_coord(x-1, y)) {
        end = process_coord(M, x-1, y, start);
        if (end) return end;
    }
    //check right
    if (is_valid_coord(x, y+1)) {
        end = process_coord(M, x, y+1, start);
        if (end) return end;
    }
    //check below
    if (is_valid_coord(x+1, y)) {
        end = process_coord(M, x+1, y, start);
        if (end) return end;
    }
    //check left
    if (is_valid_coord(x, y-1)) {
        end = process_coord(M, x, y-1, start);
        if (end) return end;
    }

    return NULL;
}

void print_path(Coord *end) {
    if (!end) {
        printf("No path exists between Start and End\n");
        return;
    }

    int index = translate_coord(end->x, end->y);
    Coord *next = parent[index];

    if (next) {
        print_path(next);
        printf("M(%d, %d) ", next->x, next->y); 
    } else printf("start ");
}

/* 0 1 0 E 0 */
/* 0 1 0 1 0 */
/* 0 0 0 0 1 */
/* 0 1 0 1 0 */
/* S 0 0 1 0 */
int main() {
    int i, j;
    tile M[N][N];
    Coord *start, *end;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            M[i][j] = WHITE;
        }
    }
    M[0][1] = BLACK;
    M[0][3] = END;
    M[1][1] = BLACK;
    M[1][3] = BLACK;
    M[2][4] = BLACK;
    M[3][1] = BLACK;
    M[3][3] = BLACK;
    M[4][0] = START;
    M[4][3] = BLACK;

    start = malloc(sizeof(Coord));
    start->x = 4;
    start->y = 0;
    end = search_maze(M, start);
    print_path(end);
    printf(" M(%d, %d) end\n", end->x, end->y);
    return 0;
}
