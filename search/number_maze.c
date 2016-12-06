#include<cstdio>
#include<cstring>

#define EXPECTED_RESULT 2012
#define START_RESULT 2011
#define MAX_DEEP 40

typedef struct {
  int num;
  char way;
  int nextnodes;
  int nextnode[10];
  bool exit;
} Node;


int loadNodes(Node nodes[]);
void searchNode(Node nodes[],int targNode,double curResult,int curDeep,char* equ);
double cacul(double baseNum,Node *mynode);

int attemp=0;

int main(){
  Node nodes[20];
  int nodes_count;
  char equ[MAX_DEEP*2+1]="";

  nodes_count = loadNodes(nodes);
  searchNode(nodes,0,START_RESULT,1,equ);
  printf("Attemps: %d\n",attemp);

  return 0;
}

void searchNode(Node nodes[],int targNode,double curResult,int curDeep,char* equ){

  Node *curNode = &nodes[targNode];
  int equlen=0;

  sprintf(equ, "%s%c%d",equ,(*curNode).way,(*curNode).num);
  equlen = strlen(equ);

  curResult = cacul(curResult,curNode);
  ++attemp;

  if(curResult == EXPECTED_RESULT && (*curNode).exit == true)
    printf("%d%s=2012\n",START_RESULT,equ);

  if(curDeep+1 < MAX_DEEP){
    ++curDeep;
    int i;
    for(i=0;i<(*curNode).nextnodes;++i){
      searchNode(nodes,(*curNode).nextnode[i],curResult,curDeep,equ);
      equ[equlen] = '\0';
    }
  }
}

double cacul(double baseNum,Node *mynode){
  switch((*mynode).way){
    case '+':return baseNum+(*mynode).num;
    case '-':return baseNum-(*mynode).num;
    case '*':return baseNum*(*mynode).num;
    case '/':return baseNum/(*mynode).num;
  }
}

int loadNodes(Node nodes[]){

  /* +7 clockwise */
  nodes[0].num = 7;
  nodes[0].way = '+';
  nodes[0].nextnodes = 3;
  nodes[0].nextnode[0] = 1;
  nodes[0].nextnode[1] = 2;
  nodes[0].nextnode[2] = 6;
  nodes[0].exit = false;

  /* /2 clockwise */
  nodes[1].num = 2;
  nodes[1].way = '/';
  nodes[1].nextnodes = 1;
  nodes[1].nextnode[0] = 0;
  nodes[1].exit = false;

  /* *3 clockwise */
  nodes[2].num = 3;
  nodes[2].way = '*';
  nodes[2].nextnodes = 1;
  nodes[2].nextnode[0] = 5;
  nodes[2].exit = true;

  /* /2 anticlockwise */
  nodes[3].num = 2;
  nodes[3].way = '/';
  nodes[3].nextnodes = 3;
  nodes[3].nextnode[0] = 7;
  nodes[3].nextnode[1] = 6;
  nodes[3].nextnode[2] = 2;
  nodes[3].exit = false;

  /* +7 anticlockwise */
  nodes[4].num = 7;
  nodes[4].way = '+';
  nodes[4].nextnodes = 1;
  nodes[4].nextnode[0] = 3;
  nodes[4].exit = false;

  /* -5 clockwise */
  nodes[5].num = 5;
  nodes[5].way = '-';
  nodes[5].nextnodes = 3;
  nodes[5].nextnode[0] = 2;
  nodes[5].nextnode[1] = 4;
  nodes[5].nextnode[2] = 1;
  nodes[5].exit = false;

  /* -5 aiticlockwise */
  nodes[6].num = 5;
  nodes[6].way = '-';
  nodes[6].nextnodes = 1;
  nodes[6].nextnode[0] = 7;
  nodes[6].exit = true;

  /* *3 anticlockwise */
  nodes[7].num = 3;
  nodes[7].way = '*';
  nodes[7].nextnodes = 3;
  nodes[7].nextnode[0] = 6;
  nodes[7].nextnode[1] = 1;
  nodes[7].nextnode[2] = 4;
  nodes[7].exit = false;

  return 8;
}
