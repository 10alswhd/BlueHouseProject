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

int main(void)
{
	/* Creates the linked list */
	Node *list = createLinkedList();

	/* Add elements to list */
	list = insert(list, 5);
	list = insert(list, 7);
	list = insert(list, 9);
	list = insert(list, 4);
	list = insert(list, 3);
	list = insert(list, 1);

	/* Debug it */
	printf("Lista bruta: \n");
	printLinkedList(list);

	/* Remove some element */
	list = findAndRemove(list, 7);

	/* Debug it */
	printf("Lista com elemento 7 removido: \n");
	printLinkedList(list);

	/* Number of elements */
	printf("A lista tem %d elementos\n", list_length(list));

	/* Find a number */
	printf("O valor 3 está na posição de memória: %p\n", (void *)findElement(list, 75));

	/* Create a new list */
	Node *slicedList = slice(list, 4);
	printLinkedList(slicedList);

	/* Clear it */
	freeLinkedList(list);

	/* Return to operating system */
	return 0;
}
