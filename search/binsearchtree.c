#include <stdio.h>
#include <stdlib.h>

typedef struct __bnode 
{
	int data;
	struct __bnode *left;
	struct __bnode *right;

} BinNode;

BinNode *alloc_node ( void )
{
	return ( ( BinNode *) calloc( 1, sizeof ( BinNode ) ) );
}

void set_node ( BinNode* n, int data, BinNode* left, BinNode* right )
{
	n -> data = data;
	n -> left = left;
	n -> right = right;
}

BinNode *search_node ( BinNode* p, int data )
{
	if ( p == NULL )
		return NULL;
	else if ( data == p->data )
		return p;
	else if ( data < p->data )
		return search_node ( p->left, data );
	else
		return search_node ( p->right, data );
}

BinNode *insert_node ( BinNode* p, int data )
{
	if ( p == NULL )
	{
		p = alloc_node ();
		set_node ( p, data, NULL, NULL );
	}
	else if ( data == p->data )
		printf ( "すでに登録されています．\n" );
	else if ( data < p->data )
		p -> left = insert_node ( p->left, data );
	else
		p -> right = insert_node ( p->right, data );

	return p;
}

int delete_node ( BinNode **root, int data )
{
	BinNode *next, *tmp;
	BinNode **left;
	BinNode **p = root;

	while ( 1 )
	{
		if ( *p == NULL )
			return -1;
		else if ( data == (*p)->data )
			break;
		else if ( data < (*p)->data )
			p = &((*p)->left);
		else
			p = &((*p)->right);
	}

	if ( (*p)->left == NULL )
		next = (*p) -> right;
	else
	{
		left = &((*p)->left);

		while ( (*left)->right != NULL )
			left = &(*left) -> right;
		next = *left;
		*left = (*left) -> left;
		next -> left = (*p) -> left;
		next -> right = (*p) -> right;
	}
	tmp = *p;
	*p = next;
	free ( tmp );

	return 0;
}

void print_data ( BinNode* p )
{
	printf ( "%02d\n", p -> data );
}

void print_tree_ascending ( BinNode* p )
{
	if ( p != NULL )
	{
		print_tree_ascending ( p->left );
		print_data ( p );
		print_tree_ascending ( p->right );
	}
}

void print_tree_descending ( BinNode* p )
{
	if ( p != NULL )
	{
		print_tree_descending ( p -> right );
		print_data ( p );
		print_tree_descending ( p -> left );
	}
}



void free_tree ( BinNode* p )
{
	if ( p != NULL )
	{
		free_tree ( p->left );
		free_tree ( p->right );
		free ( p );
	}
}


int main ( void )
{
	BinNode *root;

	root = NULL;

	int i;
	for ( i = 0; i < 20; i++ )
	{
		int r = rand () %  1000;
		root = insert_node ( root, r );
	}

	print_tree_ascending ( root );
	printf("\n");

	print_tree_descending ( root );
	printf("\n");


	free_tree ( root );
}
