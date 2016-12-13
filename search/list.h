#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct _Node {
	void *data;
	struct _Node *next;
	struct _Node *prev;
} Node;


// Appends a new node to the tail of the list
Node *list_append(Node *list, void *data);

// Frees the memory used by the list
void list_free(Node *list);

// Returns length of the list
int list_length(Node *list);

// Finds the first node where comparer returns true.
// Returns first matching node or NULL
Node *list_search(Node *list, bool (*comparer)(void const *data));

// Applies function to each of the nodes
void list_traverse(Node *list, void (*traverser)(void *data));

// Removes node from the list and returns NULL.
// If removed node was head of the list (prev = NULL) return pointer to the new list head
Node *list_remove(Node *node);

// Traverses pointer to the first node of the list
static inline void list_head(Node **list) {
	for (; (*list)->prev; *list = (*list)->prev);
}

// Traverses pointer to the last node of the list
static inline void list_last(Node **list) {
	for (; (*list)->next; *list = (*list)->next);
}

#endif
