#include<stdio.h>
#include<stdlib.h>

typedef struct node Node;

Node* create_linked_list();

int is_empty(Node *first);

Node* insert_node(Node *first, int item);

void print_linked_list(Node *first);

Node* search_linked_list(Node *first, int item);
