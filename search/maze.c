#include <stdio.h>
#include <conio.h>

#define SIZE_X 6
#define SIZE_Y 6

// Visibility and Walls around
typedef struct CELL { char mid, N, E, S, W; } CELL;
CELL maze[SIZE_X][SIZE_X];

typedef struct POINT { int i, j; } POINT;
POINT spawn = {0, 0}, end = {1, 5};

#define MAX_STACK_SIZE 50
typedef struct STACK {
    POINT stk[MAX_STACK_SIZE];
    int top;
} STACK;

STACK s;

void stack_push(POINT p) {
    if(s.top == (MAX_STACK_SIZE - 1)) {
        return;
    } else {
        s.top = s.top + 1;
        s.stk[s.top] = p;
    }
    return;
}

int stack_empty() { return  s.top == 0; }

POINT stack_pop() {
    POINT p = s.stk[s.top];
    s.top = s.top - 1;
    return(p);
}

void initMaze() {
    int i, j;
    for(i = 0; i < SIZE_Y; ++i) {
        for(j = 0; j < SIZE_X; ++j) {
            CELL* curr = &maze[i][j];
            curr->mid = 0;
            curr->N = i == 0; // Set borders as walls
            curr->S = i == SIZE_X-1;
            curr->W = j == 0;
            curr->E = j == SIZE_X-1;
        }
    }

    maze[0][0].E = maze[0][1].W = 1;
    maze[0][2].E = maze[0][3].W = 1;
    maze[0][3].E = maze[0][4].W = 1;
    maze[0][4].E = maze[0][5].W = 1;
    maze[1][1].E = maze[1][2].W = 1;
    maze[1][3].E = maze[1][4].W = 1;
    maze[2][0].E = maze[2][1].W = 1;
    maze[2][2].E = maze[2][3].W = 1;
    maze[3][3].E = maze[3][4].W = 1;
    maze[0][1].S = maze[1][1].N = 1;
    maze[0][5].S = maze[1][5].N = 1;
    maze[1][3].S = maze[2][3].N = 1;
    maze[1][5].S = maze[2][5].N = 1;
    maze[2][1].S = maze[3][1].N = 1;
    maze[2][2].S = maze[3][2].N = 1;
    maze[2][4].S = maze[3][4].N = 1;
    maze[2][5].S = maze[3][5].N = 1;
    maze[3][0].S = maze[4][0].N = 1;
    maze[3][3].S = maze[4][3].N = 1;
    maze[3][4].S = maze[4][4].N = 1;
    maze[5][4].S = maze[4][4].N = 1;
}

void printMaze() {
    printf("\n Maze: \n");
    int i, j;
    for(i = 0; i < SIZE_Y; ++i) {
        for(j = 0; j < SIZE_X; ++j) {
            CELL* curr = &maze[i][j];
            printf("+ ");
            printf(curr->N ? "- " : "  ");
        }
        printf("+\n");

        for(j = 0; j < SIZE_X; ++j) {
            CELL* curr = &maze[i][j];
            printf(curr->W ? "| " : "  ");
            printf(j == end.j && i == end.i ? "X " :
                   j == spawn.j && i == spawn.i ? "* " :
                   curr->mid ? "I " : "  ");
        }
        printf("| \n");
    }
    for(j = 0; j < SIZE_X; ++j) {
        printf("+ - ");
    }
    printf("+\n");
}

void findPath() {
    stack_push(spawn); // Put start position in stack

    while(!stack_empty()) {
        POINT c = stack_pop();
        if(c.i == end.i && c.j == end.j) break; // We're at the end

        if(maze[c.i][c.j].mid == 0) { // Not visited
            printf("\n Press a key... \n");
            getch();
            maze[c.i][c.j].mid = 1; // Visited now
            printMaze();

            // Push available directions into stack
            if(maze[c.i][c.j].N == 0 && c.i - 1 >= 0) {
                POINT n = {c.i - 1, c.j}; stack_push(n);
            }
            if(maze[c.i][c.j].E == 0 && c.j + 1 < SIZE_X) {
                POINT n = {c.i, c.j + 1}; stack_push(n);
            }
            if(maze[c.i][c.j].S == 0 && c.i + 1 < SIZE_Y) {
                POINT n = {c.i + 1, c.j}; stack_push(n);
            }
            if(maze[c.i][c.j].W == 0 && c.j - 1 >= 0) {
                POINT n = {c.i, c.j - 1}; stack_push(n);
            }
        }
    }
}

int main() {
    initMaze();
    findPath();
    return 0;
}
