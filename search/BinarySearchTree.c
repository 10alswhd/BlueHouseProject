#include<stdio.h>
#include<malloc.h>
//#include<conio.h>

/* Node structure defination */
struct element {
	int key;
	struct element *parent;
	struct element *left;
	struct element *right;
};
typedef struct element NODE;

NODE* BINARY_SEARCH_BST(NODE *x, int value_to_search){
	while(x != NULL && value_to_search != x->key){
		if(value_to_search < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

void INSERT_NODE(NODE **T, NODE *z){
	NODE *y = NULL;
	NODE *x = *T;

	while(x != NULL){
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if(y == NULL)
		*T = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

void TRANSPLANT(NODE **T, NODE *u, NODE *v){
	if(u->parent == NULL)
		*T = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if(v != NULL)
		v->parent = u->parent;
}

NODE* MINIMUM_NODE(NODE *x){
	while(x->left != NULL)
		x = x->left;

	return x;
}

void DELETE_NODE(NODE **T, NODE *z){
	NODE *y;
	if(z->left == NULL)
		TRANSPLANT(T, z, z->right);
	else if(z->right == NULL)
		TRANSPLANT(T, z, z->left);
	else{
		y = MINIMUM_NODE(z->right);
		y->right = z->right;
		y->right->parent = y;

		TRANSPLANT(T, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
}

void TRAVERSE_BST(NODE *T){
	if(T != NULL){
		TRAVERSE_BST(T->left);
		printf("%d ", T->key);
		TRAVERSE_BST(T->right);
	}
}

NODE* new_node(int key){
	NODE *z = (NODE *) malloc(sizeof(NODE));
	z->key = key;
	z->parent = z->left = z->right = NULL;
	return z;
}

int main(){
	int ch = 0, element;
	NODE *root = NULL; /* Initial condition */
	NODE *temp;

	//clrscr();

	do{
		printf("\n\nAvailable Operations:\n1. INSERT\n2. DELETE\n3. TRAVERSE\n4. SEARCH\n5. QUIT");
		printf("\nEnter your choice (1 - 5): "); scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("\nEnter an element to insert: ");  scanf("%d", &element);
				temp = new_node(element); INSERT_NODE(&root, temp);
				printf("\nTREE STATUS ::\n\t"); TRAVERSE_BST(root);
			break;
				
			case 2:
				printf("\nEnter an element to delete: ");  scanf("%d", &element);
				temp = BINARY_SEARCH_BST(root, element);
				if(temp != NULL)
					DELETE_NODE(&root, temp);
				else
					printf("No such element found");					
				printf("\nTREE STATUS ::\n\t"); TRAVERSE_BST(root);
			break;

			case 3:
				printf("\nTREE TRAVERSAL ::\n\t"); TRAVERSE_BST(root);
			break;

			case 4:
				printf("\nEnter an element to search for: ");  scanf("%d", &element);
				temp = BINARY_SEARCH_BST(root, element);
				if(temp != NULL)
					printf("%d exists in the tree.", element);
				else
					printf("No such element found.");
				printf("\nTREE STATUS ::\n\t"); TRAVERSE_BST(root);
			break;

			case 5: break;

			default:
				printf("\nInvalid options! Choose between [1,2,3,4,5]");
		}
	}while(ch != 5);

	printf("\n");
	//getch();
	return 0;
}
