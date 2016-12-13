#include <stdio.h>
#include <stdlib.h>


struct Node
{
     struct Node *previous;
     struct Node *next;
     int data;
};

struct List 
{
	struct Node *head;
	struct Node *tail;
};

struct List *new_empty_list()
{
	struct List *new = (struct List*) malloc(sizeof(struct List));
  new->head = NULL;
  new->tail = NULL;
	return new;
}

struct Node* new_node(int value) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->previous = NULL;
  newNode->next = NULL;
  return newNode;
}

void clear(struct List *list)
{

}

void insert_head(struct List *list, int value)
{
  struct Node* newNode = new_node(value);
  if(list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
    return;
  } else {
    list->head->previous = newNode;
    newNode->next = list->head; 
    list->head = newNode;
  }
}

void insert_tail(struct List *list, int value)
{
  struct Node* newNode = new_node(value);
  if(list->tail == NULL) {
    list->head = newNode;
    list->tail = newNode;
    return;
  } else {
    list->tail->next = newNode;
    newNode->previous = list->tail; 
    list->tail = newNode;
  }
}

void delete_value(struct List *list, long value)
{

}

long get(struct List *list, int index)
{
return 1;
}

int search(struct List *list, long value)
{
return 1;
}

unsigned int size(struct List *list)
{
return 1;
}

void print_list(struct List *list)
{
  struct Node* temp = list->head;
  printf("Forward: ");
  while(temp != NULL) {
    printf("%d ",temp->data);
    temp = temp->next;
  }
  printf("\n");
}

void print_reverse(struct List *list)
{

}

int main(int argc, char **argv)
{
  struct List *myList = new_empty_list();
  insert_head(myList, 3);
  insert_head(myList, 3);
  insert_head(myList, 1);
  insert_tail(myList, 7);
  print_list(myList);
  return 0;
}
