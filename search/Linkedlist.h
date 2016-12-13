#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define UNLIMITED 1

typedef enum
{
    HEAD=0,TAIL
}List_order;

typedef enum
{
    FALSE=0,SUCCESS
}Answer;

typedef struct node
{
    void* value;
    struct node* next;
    struct node* last;
}Node;

typedef struct
{
    Node* head;
    Node* tail;
    int datasize;
}List;

typedef int (*Cmp)(void*,void*);

void Add_list(void*,List*,int);
Node* Search_list(List*,Cmp,void*);
int Delete_list(List*,Cmp,void*);
int Edit_list(List*,Cmp,void*,void Edit(void*));
void QuickSort(Node*,Node*,Cmp);

#endif // LINKEDLIST_H_INCLUDED
Raw
 main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linkedlist.h"
#include "Qsort.h"

//Link_list test

int Compare(void* value,void* use)
{
    return (*(int*)value-*(int*)use);
}

void E(void* value)
{
    *(int*)value=9;
}

int main()
{
    List use={NULL,NULL,sizeof(int)};
    int a=10;
    Add_list(&a,&use,HEAD);
    a=20;
    Add_list(&a,&use,TAIL);
    Node* b=Search_list(&use,Compare,&a);
    printf("%d\n",*(int*)b->value);
    QuickSort(use.head,use.tail,Compare);
    printf("%d",*(int*)use.head->value);
    return 0;
}
