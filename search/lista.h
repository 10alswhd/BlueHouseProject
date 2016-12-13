/**
 * Queue using Linked Lists
 *
 * @author Bruno Alano Medina
 */

#ifndef _LISTA_H_INCLUDED
#define _LISTA_H_INCLUDED

/**
 * Node Structure
 *
 * Will be used for our linked list in
 * queue
 */
typedef struct node {
	/**
	 * Data of Variable
	 */
	int data;

	/**
	 * Previous Node
	 */
	struct node *prev;

	/**
	 * Next Node
	 */
	struct node *next;
} Node;

/**
 * Returns a new Linked List
 * 
 * @return address of the first element
 */
Node* createLinkedList();

/**
 * Insert Element into Linked List (FIFO)
 * 
 * @param  list existing linked list
 * @param  data value to insert
 * @return      new linked list
 */
Node* insert(Node *list, int data);

/**
 * Output Linked List
 * @param list Linked list
 */
void printLinkedList(Node *list);

/**
 * Find first element based on criteria and remove it
 * 
 * @param  list   linked list
 * @param  search value to search
 * @return        new linked list without element
 */
Node* findAndRemove(Node *list, int search);

/**
 * Deallocate memory of linked list
 * @param list linked list
 */
void freeLinkedList(Node *list);

/**
 * Length of the List (aka: conta_nos)
 *
 * @return number of nodes in list
 */
int list_length(Node *list);

/**
 * Find element in List
 */
Node* findElement(Node *list, int criteria);

/**
 * Slice a list based on index(N) + 1
 */
Node* slice(Node *list, int criteria);

#endif
