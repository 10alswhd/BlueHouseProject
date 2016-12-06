//
//  main.c
//  LinkedList-C
//
//  Created by Ryan Breaker on 5/15/16.
//  Copyright © 2016 Ryan Breaker. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int value;
    struct node_s* next;
} node;

node* BuildList() {
    node* head = NULL;

    for (int i = 5; i >= 0; i--)
    {
        node* newNode = (node*)malloc(sizeof(node));
        newNode->value = i;
        newNode->next = head;
        head = newNode;
    }

    return head;
}

node* RemoveNode(node** head, int searchValue) {
    node** doublePointer = head;

    while (*doublePointer && (*doublePointer)->value != searchValue)
    {
        doublePointer = &((*doublePointer)->next);
    }

    if (*doublePointer == NULL)
        return NULL;

    node* deletedNode = *doublePointer;
    *doublePointer = deletedNode->next;
    deletedNode->next = NULL;
    free(deletedNode);

    return deletedNode;
}

int main(int argc, const char * argv[]) {
    node* head = BuildList();
}
