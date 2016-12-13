#if 1
//
#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE *root;
typedef enum{LEFT, RIGHT}TYPE;

void insert_data(int data){
	NODE *temp;
	NODE **p = &root;
	temp = (NODE *)malloc(sizeof(NODE));
	temp->data = data;
	temp->left = temp->right =0;

	while(*p){
		if((*p)->data > data)
			p = &(*p)->left;
		else if((*p)->data < data)
			p = &(*p)->right;
		else 
			return;
	}
	*p = temp;
}

void __display(NODE *temp, int (*a)[10], int *row, int *col){
	if(temp ==0) return ;
	++*row;
	__display(temp->left, a, row, col);
	a[*row][(*col)++] = temp->data;
	__display(temp->right, a, row, col);
	--*row;
	return;
}

void display(NODE *temp){
	int i,j;
	int row = -1;
	int col = 0;
	int a[10][10] = {0,};

	system("clear");
	__display(temp, a, &row, &col);
	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			if(a[i][j]!=0)
				printf("%4d", a[i][j]);
			else
				printf("%4c", ' ');
		}
		printf("\n");
	}
	getchar();
}

NODE *__fill(NODE *temp, int *a, int *n){
	if(temp ==0)
		return;
	__fill(temp->left, a, n);
	a[(*n)++] = temp->data;
	__fill(temp->right, a, n);
}
NODE *__bal(int *a, int n){
	int mid = n/2;
	NODE *temp;

	if(n<1) return 0;
	temp = malloc(sizeof(NODE));
	temp->data = a[mid];
	temp->left = __bal(a, mid);
	temp->right = __bal(a+mid+1, n-mid-1);

	return temp;
}

void bal(NODE *temp){
	int a[100];
	int n = 0;
	__fill(temp, a, &n);
	root = __bal(a, n);
}
NODE *search(NODE *node, int key){
	if(node == NULL) return NULL;
	printf("%d-> ",node->data);
	if(key == node->data) return node ;
	else if(key < node->data) search(node->left, key);
	else search(node->right, key);
}	

NODE *rotate_RR(NODE *parent){
	NODE *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

NODE *rotate_LL(NODE *parent){
	NODE *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
/*
NODE *rotate_LR(NODE *parent){
	NODE *child = parent->left;
	NODE *child_R = child->right;
	child->right = child_R->left;
	child_R->left = child;
	parent->left = child_R->right;
	child_R->right = parent;
	return child_R;	
}*/
NODE *rotate_LR(NODE *parent){
	NODE *child = parent->left;
	parent->left = rotate_RR(child);
uu	return rotate_LL(parent);
}

NODE *rotate_RL(NODE *parent){
	NODE *child = parent->right;
	parent->right = rotate_LL(child);
	return rotate_RR(parent);
}
/*
NODE *rotate_RL(NODE *parent){
	NODE *child = parent->right;
	NODE *child_L = child->left;
	parent->right = NULL;
	child->left = child_L->right;
	//child->left = child->left->right;
	child_L->right = child;
	child_L->left = parent;
	return child_L;
}
*/
#define max(a,b) (((a) > (b)) ? (a) : (b))
int get_height(NODE *node){
	int height = 0;
	if(node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

int main(){
	NODE *node = 0;
	int i;
	int height;
	int in;
	//RR Rotation
/*	int a[] = {6,3,1,5,7,11};
	display(root);
	for(i=0; i<6; i++){
		insert_data(a[i]);
		display(root);
	}
	insert_data(12);
	display(root);
	printf("RR rotation test \n");
	getchar();
	node = search(root, 6);
	node->right = rotate_RR(node->right);
*/	
	//LL rotation
/*	int a[] = {7,6,3,12};
	display(root);
	for(i=0; i<4; i++){
		insert_data(a[i]);
		display(root);
	}
	insert_data(1);
	display(root);
	printf("LL rotation test \n");
	getchar();
	node = search(root, 3);
	node->left = rotate_LL(node->left);
*/
	//LR Rotation
/*	int a[] = {7,3,6,1,12};
	display(root);
	for(i=0; i<5; i++){
		insert_data(a[i]);
		display(root);
	}
	insert_data(5);
	display(root);
	printf("LR Rotation test \n");
	getchar();
	node = search(root,7);
	root = rotate_LR(node);
	display(root);
*/
/*//RL Rotation
	int a[] = {5,3,9,6};
	display(root);
	for(i=0; i<5; i++){
		insert_data(a[i]);
		display(root);
	}
	insert_data(7);
	display(root);
	printf("RL Rotation test \n");
	getchar();
	//node = search(root, 3);
	root = rotate_RL(root);
	display(root);
*/
	int a[] = {6,3,1,5,7,12};
	display(root);
	for(i=0; i<6; i++){
		insert_data(a[i]);
		display(root);
	}
	insert_data(9);
	display(root);
	printf("Tree height test\n");
	getchar();

	height = get_height(root);
	printf("root height : %d\n", height);
	return 0;	
}



#endif
