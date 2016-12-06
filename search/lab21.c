#include <stdio.h>
#include <limits.h>
#include <malloc.h>

#define side 200

typedef struct coordinates {
    int i;
    int j;
} coord;

typedef struct turn {
    int i;
    int j;
    struct turn* next;
} turn;



void newElem(turn*, int, int);

int main() {
    char c;
    int* lab[side]; // Лабиринт в виде числовой матрицы
    int n,m; // Высота и ширина лабиринта
    int i,j;
    coord* START;
    coord* FINISH;
    turn* curr;
    turn* head;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Выделение памяти
    START = (coord*)malloc(sizeof(coord));
    FINISH = (coord*)malloc(sizeof(coord));
    for (i = 0; i < side; i++) lab[i] = (int*)malloc(side*sizeof(int));

    // Создание числовой матрицы лабиринта
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
    
    curr = (turn*)malloc(sizeof(turn));
    head = (turn*)malloc(sizeof(turn));
    
    head->i = START->i;
    head->j = START->j;
    curr = head;
    curr->next = NULL;

    // Нахождение кратчайшего расстояния
    while(curr != NULL) {
        if (curr->i == FINISH->i && curr->j == FINISH->j) {
            curr = curr->next;
            continue;
        }
        if (curr->i < n-1 && lab[curr->i+1][curr->j] > lab[curr->i][curr->j]+1) {
            lab[curr->i+1][curr->j] = lab[curr->i][curr->j]+1;
            printf("(%d, %d):", curr->i+1, curr->j+1);
            newElem(curr, curr->i+1, curr->j);
        }
        if (curr->i > 0 && lab[curr->i-1][curr->j] > lab[curr->i][curr->j]+1) {
            lab[curr->i-1][curr->j] = lab[curr->i][curr->j]+1;
            printf("(%d, %d):", curr->i+1, curr->j+1);
            newElem(curr, curr->i-1, curr->j);
        }
        if (curr->j < m-1 && lab[curr->i][curr->j+1] > lab[curr->i][curr->j]+1) {
            lab[curr->i][curr->j+1] = lab[curr->i][curr->j]+1;
            printf("(%d, %d):", curr->i+1, curr->j+1);
            newElem(curr, curr->i, curr->j+1);
        }
        if (curr->j > 0 && lab[curr->i][curr->j-1] > lab[curr->i][curr->j]+1) {
            lab[curr->i][curr->j-1] = lab[curr->i][curr->j]+1;
            printf("(%d, %d):", curr->i+1, curr->j+1);
            newElem(curr, curr->i, curr->j-1);
        }
        curr = curr->next;
    }
    
    if (lab[FINISH->i][FINISH->j] == INT_MAX) printf("-1");
    else printf("%d", lab[FINISH->i][FINISH->j]-1);

    return 0;
}

void newElem(turn* p, int i, int j) {
    turn* r = (turn*)malloc(sizeof(turn));
    
    printf("(%d, %d) - ", i+1,j+1);
    r->i = i;
    r->j = j;
    r->next = p->next;
    p->next = r;
}
