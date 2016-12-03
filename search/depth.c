#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#define MAX 1000

typedef struct Node Node;

struct Node {
  int id;
  Node* next;
};//Node like a linked list

Node* new_node(int i, Node* n);//Node constructor
void read();//read the input stream
void depth_search();
void get_adj(int currentState);
void print_list(Node* n);

Node* openList[MAX];
Node* closedList[MAX];

int adjMatx[SIZE][SIZE];//Adjacency Matrix
int size;//Final size
int openPos;//position in open list
int closedPos;//position in closed list
int initialState;
int finalState;

int main(int argc, char const *argv[]) {

  read();

  openPos = -1;
  closedPos = -1;

  openList[++openPos] = new_node(initialState, NULL);

  depth_search();

  return 0;
}

Node* new_node(int i, Node* n) {

  Node* node = malloc(sizeof(*node));
  node->id = i;
  node->next = n;

  return node;
}

void read() {

  scanf("%d", &size);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      scanf("%d", &adjMatx[i][j]);
    }
  }

  scanf("%d", &initialState);
  scanf("%d", &finalState);
}

void get_adj(int currentState) {

  for (size_t i = 0; i < size; i++) {
    if (adjMatx[currentState][i] == 1)
      openList[++openPos] = new_node(adjMatx[currentState][i], closedList[closedPos]);
  }
}

void print_list(Node* n){

  Node* node = n;

  while(node != NULL){
    printf("%d ", node->id);
    node = node->next;
  }

  printf("\n");
}

void depth_search() {

  int currentState;

  if (openPos == -1)
    return;

  do {
    closedList[++closedPos] = openList[openPos--];
    currentState = closedList[closedPos]->id;
    if (currentState == finalState)
      print_list(closedList[closedPos]);
    else
      get_adj(currentState);
  } while (openPos != -1);
}
