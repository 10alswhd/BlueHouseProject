/**
 * Queue using Linked Lists
 *
 * @author Bruno Alano Medina
 */

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>

/* Linked List */
#include "lista.h"

Node* createLinkedList()
{
	return NULL;
}

Node* insert(Node *list, int data)
{
	/* Allocate a new Node */
	Node *elem = malloc(sizeof(Node));
	elem->data = data;

	/* Assign the tail */
	elem->next = list;

	/* Assign the previous node */
	if (list != NULL)
		list->prev = elem;
	elem->prev = NULL;

	/* Return the new list */
	return elem;
}

void printLinkedList(Node *list)
{
	/* Store temporary node */
	Node *temp = malloc(sizeof(Node));

	/* Iterate over all elements */
	for (temp = list; temp != NULL; temp = temp->next)
		printf("[Linked List] %d\n", temp->data);
}

Node* findAndRemove(Node *list, int criteria)
{
	/* Store current node */
	Node *current = malloc(sizeof(Node));
	current = list;

	while( (current != NULL) && (current->data != criteria) )
	{
		/* Skip to next */
		current = current->next;
	}

	if (current == NULL)
		return list;
	else if (current->prev == NULL)
		return current->next;
	else
	{
		current->prev->next = current->next;
		free(current);
	}
	return list;
}

void freeLinkedList(Node *list)
{
	/* Store current node */
	Node *current = malloc(sizeof(Node));
	Node *temp = malloc(sizeof(Node));
	current = list;

	while( current != NULL )
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

int list_length(Node *list)
{
	/* Counter */
	int i = 0;

	/* Store current node */
	Node *current = malloc(sizeof(Node));
	current = list;

	while( (current != NULL) )
	{
		i++;
		current = current->next;
	}

	return i;
}

Node* findElement(Node *list, int criteria)
{
	/* Store current node */
	Node *current = malloc(sizeof(Node));
	current = list;

	while( (current != NULL) )
	{
		if ( current->data == criteria ) return current;
		current = current->next;
	}

	return NULL;
}

Node* slice(Node *list, int criteria)
{
	Node *current = malloc(sizeof(Node));
	current = findElement(list, criteria);
	return current->next;
}
