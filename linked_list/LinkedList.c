#include "stdafx.h"
#include "stdlib.h"

typedef struct Node
{
   int su;
   struct Node *next;
}node;
node *head = NULL;

int insert(int num)
{
   node *tmp, *last;
   tmp = (node*)malloc(sizeof(node));
   tmp->su = num;
   tmp->next = NULL;
   if(head == NULL)
   {
      head = tmp;
      return 1;
   }
   last = head;
   while(last->next != NULL)
      last = last->next;
   last->next = tmp;
   return 1;
}

void deleteNode(int num, node *head)
{
   node *pre = head;
   node *tmp = pre->next;
   if(pre==NULL)
      return;
   if(pre->next==NULL){
      head = NULL;
      free(pre);
   }
   else {
      while(tmp->next!=NULL)
      {
         pre = tmp;
         tmp = tmp->next;
      }
      pre->next = NULL;
      free(tmp);
   }

}
void printList(node *head)
{
   node *p;
   printf("L = (");
   p = head;
   while(p != NULL)
   {
      printf("%d", p->su);
      p = p->next;
      if(p!=NULL) printf(", ");
   }
   printf(") \n");
}

int _tmain(int argc, _TCHAR* argv[])
{
   insert2(10);
   printList(head);
   insert2(30);
   printList(head);
   insert2(5);
   printList(head);
   deleteNode(5, head);
   printList(head);

   system("pause");
   return 0;
}
