#include <stdio.h>
#include <string.h>

#define N 7

int visited[N];
int graph[N][N];

int front = 0;
int rear = 0;
int q[N] = { 0 };

void bfs (int v, int n);

int main ()
{
        int i, j, number;
        memset (visited, 0, sizeof (visited)); //setting visited to 0
        printf("Enter the number of vertices: \n");
        scanf("%d", &number);

        printf("Enter the adjacency matrix: ");

        for(i = 0; i < number; i++){
            for(j = 0; j < number; j++){
                scanf("%d", &graph[i][j]);
            }
        }

        bfs (0,number);
        return 0;
}

void bfs (int v, int n)
{

        visited[v] = 1;
        q[rear] = v;
        rear++;

        while (rear != front)
        {

                int u = q[front];
                printf ("%d ", u);
                front++;


                int i = 0;
                for (i = 0; i < n; i++)
                {

                        if (!visited[i] && graph[u][i])
                        {
                                q[rear] = i;
                                rear++;
                                visited[i] = 1;
                        }
                }
        }
        printf ("\n");
}

/*
Enter the number of vertices:
8
Enter the adjacency matrix: 0 1 1 1 1 0 0 0
1 0 0 0 0 1 0 0
1 0 0 0 0 1 0 0
1 0 0 0 0 0 1 0
1 0 0 0 0 0 1 0
0 1 1 0 0 0 0 1
0 0 0 1 1 0 0 1
0 0 0 0 0 1 1 0
0 1 4 7 5 6
*/
