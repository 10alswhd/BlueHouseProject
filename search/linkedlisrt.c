#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Defines a node for linked list
typedef struct node
{
    int n;
    struct node* next;
}
node;

// linked list
node* first = NULL;

// prototypes
void delete(void);
void insert(void);
void search(void);
void traverse(void);
