#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <time.h> 


struct node { 
  int value; 
  struct node *next; 
}; 
 

 struct node *head; 
 

 struct node *create_node(int value){ 
   struct node *n = (struct node*)malloc(sizeof(struct node)); 
   n->next = NULL; 
   n->value = value; 
   return n; 
 } 
 

 int insert_node(int value){ 
   struct node *n; 
   for(n = head; n != NULL; n = n->next){ 
     if(n->value == value) break; 
     if(n->next == NULL){ 
        n->next = create_node(value); 
        break; 
      } 
   } 
 } 
 

 int print(){ 
   struct node *n = head; 
   while(n->next != NULL){ 
     n = n->next; 
     printf("%d\n", n->value); 
   } 
 } 
 

 int main(void){ 
   srand((unsigned)time(NULL)); 
   int i = 0; 
   int LIMIT = 10; 
   int RANGE = 100; 
   head = create_node(0); 
   while(i<LIMIT){ 
     insert_node(rand()%RANGE+1); 
     i++; 
   } 
   print(); 
   return 0; 
 } 
