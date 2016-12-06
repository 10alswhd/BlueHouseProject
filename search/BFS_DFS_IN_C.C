#include <stdio.h>
#include <stdlib.h>

static const int MAX = 100;
static int q[MAX], matrix[MAX][MAX], visited[MAX];
int top = -1, rear= -1, n= 0;

void push(int val){
  if(rear==MAX-1){
    printf("\nQUEUE FULL\n");
    return;
  }
  if(top==-1){
    ++top;
  }
  q[++rear] = val;
}

int pop(){
  int ans= -1;
  if(top==-1 || top>rear) {
    printf("\nQUEUE EMPTY\n");
    return -1;
  }
  else{
    ans = q[top];
    q[top] = -1;
    ++top;
    return ans;
  }
}

int empty(){
  if(top>rear || top==-1) return 1;
  else return 0;
}

void bfs(){
  printf("Breadth first search:\n");
  int source, i;

  for(i=0; i<n; i++) visited[i] = 0;

  for(i=0; i<n; i++){
    if(visited[i])
      continue;

    push(i);
    visited[i] = 1;

    while(!empty()){
      source = pop();
      printf("%d ", source+1);

      for(i=0; i<n; i++){
        if(matrix[source][i] && !visited[i]){
          push(i);
          visited[i] = 1;
        }
      }
    }
  }
  printf("\n");
}

void _dfs(int node){
  int  i;
  printf("%d ", node+1);
  visited[node] = 1;
  for(i=0; i<n; i++){
    if(matrix[node][i] && !visited[i]){
      _dfs(i);
    }
  }
}

void dfs(){
  int i;
  printf("Depth First Search: \n");
  for(i=0; i<n; i++) visited[i]=0;
  for(i=0; i<n; i++){
    if(!visited[i]){
      _dfs(i);
    }
  }
  printf("\n");
}

int main(){
  int x, y;
  printf("Enter number of elements: ");
  scanf("%d", &n);

  if(n>MAX){
    printf("Exceeding memory capacity!!!\n");
    return 1;
  }

  printf("Enter ordered pairs of vertices with edges between them\nEnter -1 at any time to stop\n");
  while(1){
    scanf("%d %d", &x, &y);
    if(x==-1 || y==-1) {
        break;
    }
    else if(x>n || y>n || x<=0 || y<=0){
      printf("Exceeding memory capacity!!!\n");
      return 1;
    }
    else{
      matrix[x-1][y-1]=1;
    }
  }
  bfs();
  dfs();
  return 0;
}
