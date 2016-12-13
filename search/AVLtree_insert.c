#if 1

#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}NODE;

NODE *root;
typedef enum{LEFT, RIGHT}TYPE;

NODE *balance_tree(NODE **node);

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

NODE *insert(NODE **root, int data){
	NODE **p = root;
	if(*p == NULL){
		*p = (NODE *)malloc(sizeof(NODE));
		if(*p == NULL){
			printf("메모리 할당 실패 \n");
			exit(-1);
		}
		(*p)->data = data;
		(*p)->left = (*p)->right = NULL;
	}else if(data < (*p)->data)
	{
		(*p)->left = insert(&((*p)->left),data);
		(*p) = balance_tree(p);
	}else if(data > (*p)->data){
		(*p)->right = insert(&((*p)->right), data);
		(*p) = balance_tree(p);
	}
	else{
		printf("중복데이터 입력\n");
		exit(-1);
	}	
	return *p;
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
	if(node->data == key)
		printf("%d\n",node->data);
	else
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
NODE *rotate_LR(NODE *parent){
	NODE *child = parent->left;
	parent->left = rotate_RR(child);

	return rotate_LL(parent);
}
NODE *rotate_RL(NODE *parent){
	NODE *child = parent->right;
	parent->right = rotate_LL(child);
	
	return rotate_RR(parent);
}

#define max(a,b) (((a) > (b)) ? (a) : (b))
int get_height(NODE *node){
	int height = 0;
	if(node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}
int get_balance(NODE *node){
	if(node ==NULL) return 0;
	return get_height(node->left) - get_height(node->right);
	//왼쪽에서 오른쪾 빼서 음수면 오른쪽이 크고, 양수면 왼쪽큼
}
NODE *balance_tree(NODE **node){
	int height_diff;
	height_diff = get_balance(*node);
	printf("밸런스 값 : %d\n", height_diff);
	if(height_diff > 1){
		if(get_balance((*node)->left) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if(height_diff < -1){
		if(get_balance((*node)->left) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	display(root);
	return *node;
}	

NODE *search_parent(NODE *node , int key){
	if(node->left->data == key) return node;
	if(node->right->data == key) return node;
	if(key < node->data) search_parent(node->left, key);
	else search_parent(node->right, key);
}

int main(){
	int a[] = {6,4,1,5,7,12,8,2};
	int i;
	display(root);

	for(i=0; i<8; i++){
		insert(&root, a[i]);
		display(root);	
	}

	return 0;
}

#endif
