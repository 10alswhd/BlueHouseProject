#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define side 200
#define h 0
#define w 1

typedef struct coordinates {
    int i;
    int j;
} coord;


int main() {
    char c;
    int* lab[side]; // Numeric labirint matrix
    int n, m; // Sides of labirint
    int i = 0, j;
    coord* START; // Start's coordinates
    coord* FINISH; // Finish's coordinates
    int* way[19901];
    int cellsCount = 0; // Number of points in turn
    int x,y;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    START = (coord*)malloc(sizeof(coord));
    FINISH = (coord*)malloc(sizeof(coord));
    for (i = 0; i < side; i++) lab[i] = (int*)malloc(side*sizeof(int));
    for (i = 0; i < 19901; i++) way[i] = (int*)malloc(2*sizeof(int));

    // Labirint matrix creating
    scanf("%d%d",&n, &m);
    for (i = 0; i < n; i++) {
        j = 0;
        while (j < m) {
            scanf("%c", &c);
            switch (c) {
                case '.': lab[i][j] = INT_MAX; j++; break;
                case 'x': lab[i][j] = -1; j++; break;
                case 'S': START->i = i; START->j = j; lab[i][j] = 1; j++; break;
                case 'T': FINISH->i = i; FINISH->j = j; lab[i][j] = INT_MAX; j++; break;
            }
        }
    }

    way[0][h] = START->i;
    way[0][w] = START->j;

    // Search short distance
    i = 0;
    while (i <= cellsCount) {
        x = way[i][h];
        y = way[i][w];
        i++;
        if (x == FINISH->i && y == FINISH->j) continue;
        if (x < n-1 && lab[x+1][y] > lab[x][y]+1) {
            lab[x+1][y] = lab[x][y]+1;
            cellsCount++;
            way[cellsCount][h] = x+1;
            way[cellsCount][w] = y;
            //printf("(%d; %d)--(%d; %d) || ", x, y, x+1, y);
        }
        if (x > 0 && lab[x-1][y] > lab[x][y]+1) {
            lab[x-1][y] = lab[x][y]+1;
            cellsCount++;
            way[cellsCount][h] = x-1;
            way[cellsCount][w] = y;
            //printf("(%d; %d)--(%d; %d) || ", x, y, x-1, y);
        }
        if (y < m-1 && lab[x][y+1] > lab[x][y]+1) {
            lab[x][y+1] = lab[x][y]+1;
            cellsCount++;
            way[cellsCount][h] = x;
            way[cellsCount][w] = y+1;
            //printf("(%d; %d)--(%d; %d) || ", x, y, x, y+1);
        }
        if (y > 0 && lab[x][y-1] > lab[x][y]+1) {
            lab[x][y-1] = lab[x][y]+1;
            cellsCount++;
            way[cellsCount][h] = x;
            way[cellsCount][w] = y-1;
            //printf("(%d; %d)--(%d; %d) || ", x, y, x-1, y-1);
        }
    }

    if (lab[FINISH->i][FINISH->j] == INT_MAX) printf("-1");
    else printf("%d", lab[FINISH->i][FINISH->j]-1);
    
    return 0;
}
