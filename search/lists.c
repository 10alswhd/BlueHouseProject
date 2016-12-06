#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} boolean;
typedef struct Node{
                    int value;
                    struct Node *next;
                    }Node;

Node *getNode()
{
    Node *node;
    node=(Node*)malloc(sizeof(Node));
    
    if(node==NULL){
                   printf("Den mporei na dimiourgei o komvos!\n");
                   return NULL;
                   }
    return node;
}

Node *CreateList()
{
     int num, value, i;
     Node *node, *temp, *firstnode;
     printf("Dwse ari8mo komvwn tis listas: ");
     scanf("%d",&num);
                         
     for(i=num; i>0; i--){
                          printf("Dwse timi gia ton upari8mo %d komvo: ", num-i);
                          scanf("%d", &value);
                          
                          node = getNode();
                          node->value = value;
                          node->next = NULL;
                                              
                          if (i==num) firstnode = node;
                          else {
                                temp->next = node;
                                }
                          temp = node;
                          }
     return firstnode;
}

Node *Search(Node *firstnode)
{
     Node *node = firstnode;
     int counter=0;
     int n;
     
     printf("Dwse thesi komvou: ");
     scanf("%d",&n);
     
     while (node != NULL){
                          if (counter==n){
                                          printf("\nSton upari8mo %d komvo uparxei h timi %d.\n",n,node->value);
                                          return node;
                                          }
                          else{
                               counter++;
                               node = (*node).next;
                               }
                          }
     printf("\nSton upari8mo %d komvo uparxei h timi %d.\n",n,node->value);
     return NULL;
}

Node *subSearch(Node *firstnode)
{
     Node *node = firstnode;
     int counter=0;
     int n;
     
     printf("Dwse thesi komvou: ");
     scanf("%d",&n);
     
     while (node != NULL){
                          if (counter==n){
                                          return node;
                                          }
                          else{
                               counter++;
                               node = (*node).next;
                               }
                          }
     return NULL;
}

boolean Insert(Node *previousnode)
{
     int value;
     
     printf("\nDwse stoixeio gia eisagwgi: ");
     scanf("%d",&value);
     
     Node *node=getNode();
     if (node != NULL){
                       node->value = value;
                       node->next = previousnode->next;
                       previousnode->next = node; 
                       return true;
                       }
     else return false;
}      

Node *Delete(Node *previousnode)
{
    Node *node = previousnode->next;
    if (node != NULL){
                      previousnode->next = node->next;
                      return node;
                      }
    else return NULL;
}

void ListData(Node *firstnode)
{
     Node *node = firstnode;

     printf("\nOi times tis listas einai:\n");
     while (node != NULL){
                          printf("%d ",node->value);
                          node=node->next;
                          }
     printf("\n");
}

Node* lastNode(Node *firstnode)
{
      Node *n = firstnode;
      
      while (n->next != NULL){
                              n = n->next;
                              }
      return n;
}

Node* Concatenation(Node *list1Head, Node *list2Head)
{
 Node *list1Tail = lastNode(list1Head);
 list1Tail->next = list2Head;
 return list1Head;
}

Node* Inverse(Node *firstnode)
{
      Node *p = firstnode;
      Node *q = NULL;
      Node *r;
      
      while(p != NULL){
                        r = q;
                        q = p;
                        p = p->next;
                        q->next = r;
                        }
      firstnode = q;
      return firstnode;
}

int main(int argc, char *argv[])
{
 char c='y';
 int position, value,num,ep;
 boolean b;
 Node *n, *t;
 
 Node *firstnode = CreateList();
 ListData(firstnode);
     
  do{ 
  printf("\nDiale3e energeia epi listas:\n");
  printf(" 1. Eisagwgi\n 2. Akurwsi\n 3. Search\n 4. Sunenwsi\n 5. Antistrofi\n");
  scanf("%d",&ep);
  
  switch (ep){
              case 1: printf("\nH eisagwgi tou neou komvou 8a ginei stin epomeni thesi apo auti pou 8a do8ei.\n");
                      n=subSearch(firstnode);
                      Insert(n);
                      ListData(n);
                      break;
              case 2: printf("\nH diagrafi 8a ginei ston epomeno komvo tis thesis pou 8a do8ei.\n");
                      n=subSearch(firstnode);
                      Delete(n);
                      ListData(n);
                      break;
              case 3: Search(firstnode);
                      break;
              case 4: printf("\nDwse stoixeia prwtis listas.\n");
                      Node *list1 = CreateList();
                      ListData(list1);
                      Node *list2 = CreateList();
                      printf("\nDwse stoixeia deuteris listas\n");
                      ListData(list2);
                      printf("\nEpituxis sunenwsi twn 2 listwn.\n");
                      n = Concatenation(list1, list2);
                      ListData(n);
                      break;
              case 5: n=Inverse(firstnode);
                      printf("\nH lista antistrafike.");
                      ListData(n);
                      break;
              default: printf("La8os!");
              }
  printf("\nPatise Y gia epistrofi 'h otidipote allo gia e3odo: ");
  scanf("%s",&c);
    }while(c=='y' || c=='Y');

  printf("\nTermatismos programmatos!!\n");
  
system("PAUSE");	
return 0; 
}    
