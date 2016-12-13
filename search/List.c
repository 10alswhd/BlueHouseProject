#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/*
  list.c 
		Contains functions to manipulate a doubly-linked list.
 
*/


/* private methods */

static NodePtr reverse(NodePtr L);
static void print(NodePtr node);



ListPtr createList()
{
	ListPtr list = malloc(sizeof(List));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;
}

void freeList(ListPtr L)
{
	NodePtr node = L->head;

	while(node)
	{
		NodePtr next = node->next;
		freeNode(node);
		node = next;
	}

	free(L);
}

int getSize(ListPtr L)
{
	return L->size;
}

Boolean isEmpty(ListPtr L)
{
	if (L->size == 0)
		return TRUE;
	else
		return FALSE;
}

ListPtr addAtFront(ListPtr list, NodePtr node)
{
	if (list == NULL) return NULL;
	if (node == NULL) return NULL;

	list->size++;
	node->prev = NULL;

	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	} else {
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}

	return list;
}

//Adds a node to the rear of the list.
void addAtRear(ListPtr list, NodePtr node)
{
	if (list == NULL) return;
	if (node == NULL) return;

	//Increment the size since we're adding a node.
	list->size++;

	//In case there aren't any nodes in the list yet.
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->prev = list->tail;    //Set up the previous pointer.
		list->tail->next = node;    //Set up next pointer for previous node.
		list->tail = node;          //Set up tail pointer.
		list->tail->next = NULL;    //Set up the next pointer for node to be NULL.
	}
}

//Remove the node at the front of the list.
NodePtr removeFront(ListPtr list)
{
	if (list == NULL) return NULL;
	if (list->head == NULL) return NULL;

	//In case there is only one node in the list.
	if (list->size == 1)
	{
		list->size--;
		NodePtr temp = list->head;
		list->head = NULL;
		list->tail = NULL;

		return (temp);
	}
	else if(list->size == 0)
	{
		return NULL;
	}
	else
	{
		NodePtr tmp = list->head;       //Make a temp node that points to head.
		list->head = list->head->next;  //Reset the head pointer to the next node.
		list->head->prev = NULL;        //Set the previous pointer for new head to NULL.
		list->size--;                   //Decrement size since we removed a node.

		return(tmp);
	}
}

NodePtr removeRear(ListPtr list)
{
	if (list == NULL) return NULL;
	if (list->head == NULL) return NULL;

	//In case there is only one node in the list.
	if (list->size == 1)
	{
		list->size--;
		NodePtr temp = list->head;
		list->head = NULL;
		list->tail = NULL;

		return (temp);
	}
	else if (list->size == 0)
	{
		return NULL;
	}
	else
	{
		NodePtr tmp = list->tail;          //Make a temp node that points to the tail.
		list->tail = list->tail->prev;     //Make the tail pointer go to the previous node.
		list->tail->next = NULL;           //Make the next pointer for new tail NULL.
		list->size--;                      //Decrement the size since we removed a node.

		return(tmp);
	}
}

NodePtr removeNode(ListPtr list, NodePtr node)
{
	if (list == NULL) return NULL;
	if (node == NULL) return NULL;


	if (list->size == 0)
	{
		return NULL;
	}
	else if ( (list->head) == node)   //In case the node to be removed is the head.
	{
		return removeRear(list);
	}
	else if ( (list->tail) == node)    //In case the node to be removed is the tail.
	{
		return removeFront(list);
	}
	else
	{
		node->prev->next = node->next; //Reroute the next pointer around removed node.
		node->next->prev = node->prev; //Reroute the prev pointer around removed node.
		list->size--;
		return node;
	}
}

NodePtr search(ListPtr list, char* key)
{
	if (list == NULL) return NULL;

	NodePtr tmp = list->head;           //Make a temp node to start search at head.

	while(tmp)
	{
		if( ((HashObjectPtr) (tmp->data))->key == key)     //See if there is a match, casted as HashObjectPtr.
		{
			return tmp;                 //Match.
		}
		else
		{
			if (tmp->next)               //Make sure the next node exists.
				tmp = tmp->next;         //Move on to the next node for search.
			else
				return NULL;
		}
	}

	return NULL;                         //No match.
}

void reverseList(ListPtr L)
{
	if (L == NULL) return;
	L->tail = L->head;
	L->head  = reverse (L->head);
}

static NodePtr reverse(NodePtr L)
{
	NodePtr list = NULL;
	while (L != NULL) {
		NodePtr tmp = L;
		L = L->next;
		if (L != NULL) L->prev = tmp;
		tmp->next = list;
		tmp->prev = L;
		list = tmp;
	}
	return list;
}

void printList(ListPtr L)
{
	if (L) print(L->head);
}

static void print(NodePtr node)
{
	int count = 0;
	char *output;

	while (node) {
		output = ((HashObjectPtr)(node->data))->key;
		printf(" %s ||", output);

		if((output = ((HashObjectPtr)(node->data))->value))
			printf(" %s -->", output);

		node = node->next;
		count++;
		if ((count % 6) == 0)
			printf("\n");
	}
    printf(" NULL \n");
}
