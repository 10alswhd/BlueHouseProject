#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

Node *list_append(Node *list, void *data) {
	if (list) list_last(&list);
	Node *node = malloc(sizeof(Node));
	if (node) {
		node->data = data;
		node->next = NULL;
		node->prev = list;
		if (list) {
			list->next = node;
		}
	}
	return node;
}

void list_traverse(Node *list, void (*traverser)(void *data)) {
	list_head(&list);
	for (; list; traverser(list->data), list = list->next);
}

void list_free(Node *list) {
	list_head(&list);
	for (Node *next; list; list = next) {
		next = list->next;
		free(list->data);
		free(list);
	}
}

int list_length(Node *list) {
	int len = 1;
	Node *temp;
	if (!list) return 0;
	for (temp = list; temp->prev; ++len, temp = temp->prev);
	for (temp = list; temp->next; ++len, temp = temp->next);
	return len;
}

Node *list_search(Node *list, bool (*comparer)(void const *data)) {
	if (!list) return NULL;
	list_head(&list);
	for (; list; list = list->next) {
		if (comparer(list->data)) {
			return list;
		}
	}
	return NULL;
}

Node *list_remove(Node *node) {
	if (!node->prev) {
		Node *temp = node->next;
		temp->prev = NULL;
		free(node->data);
		free(node);
		return temp;
	} else {
		node->prev->next = node->next;
		if (node->next) node->next->prev = node->prev;
		free(node->data);
		free(node);
		return NULL;
	}
}
