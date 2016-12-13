#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>

#include "btree.h"

static btree_node_t *btree_min(btree_node_t *x) {
	if (!x)
		return NULL;

	while(x->left)
		x = x->left;

	return x;
}

static btree_node_t *btree_max(btree_node_t *x) {
	if (!x)
		return NULL;

	while(x->right)
		x = x->right;

	return x;
}

static btree_node_t *btree_successor(btree_node_t *x) {
	btree_node_t *y;

	if (x->right)
		return btree_min(x->right);

	y = x->parent;
	while (y && x == y->right) {
		x = y;
		y = y->parent;
	}

	return y;
}

static btree_node_t *btree_search(btree_node_t *x, uint32_t key) {
	while (x && key != x->key) {
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

static void btree_insert_node(btree_t *tree, btree_node_t *z) {
	btree_node_t *x, *y;

	y = NULL;
	x = tree->root;
	while (x) {
		y = x;
		assert(z->key != x->key);
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (!y) {
		tree->root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	tree->count++;
}

static btree_node_t *btree_delete_node(btree_t *tree, btree_node_t *z) {
	btree_node_t *x, *y;

	if (!z->left || !z->right)
		y = z;
	else
		y = btree_successor(z);

	if (y->left)
		x = y->left;
	else
		x = y->right;

	if (x)
		x->parent = y->parent;

	if (!y->parent) {
		tree->root = x;
	} else if (y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}

	z->key  = y->key;
	z->data = y->data;

	tree->count--;
	return y;
}

int btree_create(btree_t **tree) {
	btree_t *t = (btree_t*)malloc(sizeof(btree_t));
	if (t) {
		t->count = 0;
		t->root = NULL;
		*tree = t;
		return 1;
	}
	return 0;
}

int btree_destroy(btree_t **tree) {
	btree_t *t = *tree;

	if (t->root) {
		printf("Tree not empty - cannot destroy\n");
		return 0;
	}

	free(t);
	*tree = NULL;
	return 1;
}

int btree_find(btree_t *tree, uint32_t key, void **d) {
	btree_node_t *x;

	x = btree_search(tree->root, key);
	if (x) {
		*d = x->data;
		return 1;
	}
	return 0;
}

int btree_add(btree_t *tree, uint32_t key, void *data) {
	btree_node_t *x;

	x = btree_search(tree->root, key);
	if (x) {
		printf("Item already exists - key %ul\n", key);
		return 0;
	}

	x = (btree_node_t *)malloc(sizeof(btree_node_t));
	x->key    = key;
	x->data   = data;
	x->parent = NULL;
	x->left   = NULL;
	x->right  = NULL;
	btree_insert_node(tree, x);

	return 1;
}

int btree_remove(btree_t *tree, uint32_t key, void **data) {
	btree_node_t *x;

	x = btree_search(tree->root, key);
	if (!x) {
		printf("Item not on tree - key %ul\n", key);
		*data = NULL;
		return 0;
	}

	/* Note value that gets freed is not necessarily the the same
	 * as node that gets removed from tree since there is an
	 * optimization to avoid pointer updates in tree which means
	 * sometimes we just copy key and data from one node to
	 * another.
	 */

	*data = x->data;
	x = btree_delete_node(tree, x);
	free(x);

	return 1;
}

int btree_get_min_key(btree_t *tree, uint32_t *key) {
	btree_node_t *x;

	if (!tree->root)
		return 0;

	x = btree_min(tree->root);
	if (!x)
		return 0;

	*key = x->key;
	return 1;
}

int btree_get_max_key(btree_t *tree, uint32_t *key) {
	btree_node_t *x;

	if (!tree->root)
		return 0;

	x = btree_max(tree->root);
	if (!x)
		return 0;

	*key = x->key;
	return 1;
}

int btree_get_next_key(btree_t *tree, uint32_t cur_key, uint32_t *next_key) {
	btree_node_t *x;

	x = btree_search(tree->root, cur_key);
	if (!x)
		return 0;

	x = btree_successor(x);
	if (!x)
		return 0;

	*next_key = x->key;
	return 1;
}

#ifdef TEST

static int btree_depth(btree_node_t *x) {
	int l, r;

	if (!x)
		return 0;

	l = btree_depth(x->left);
	r = btree_depth(x->right);

	if (l > r)
		return l+1;
	else
		return r+1;
}

static void btree_dump_node(btree_node_t *x, int depth, int c, int w) {
	if (!x)
		return;

	printf("%u ", x->key);

	btree_dump_node(x->left, depth+1, c-w/2, w/2);
	btree_dump_node(x->right, depth+1, c+w/2, w/2);
}

static void btree_dump(btree_t *b) {
	btree_dump_node(b->root, 0, 40, 48);
	putchar('\n');
}

int main() {
	btree_t *b;
	uint32_t i, *x;
	uint32_t v[] = {15, 5, 16, 3, 12, 20, 10, 13, 18, 23, 6, 7};
	uint32_t nv = sizeof(v) / sizeof(v[0]);

	btree_create(&b);

	for(i=0; i<nv; ++i) {
		x = (uint32_t*)malloc(sizeof(uint32_t));
		*x = (uint32_t)rand();
		printf(">>%u\n", *x);
		if (!btree_add(b, v[i], (void*)x))
			printf("Fail Add %u %u\n", v[i], *x);
	}

	printf("depth %d\n", btree_depth(b->root));
	btree_dump(b);

	btree_remove(b, 5, (void*)&x);
	free(x);
	btree_dump(b);

	btree_remove(b, 16, (void*)&x);
	free(x);
	btree_dump(b);

	btree_remove(b, 13, (void*)&x);
	free(x);
	btree_dump(b);

	while (btree_get_min_key(b, &i)) {
		if (!btree_remove(b, i, (void*)&x))
			fprintf(stderr, "Failed to remove %u\n", i);
		free(x);
		btree_dump(b);
	}

	if (!btree_destroy(&b))
		printf("Failed to destroy \n");

	return 0;
}

#endif
