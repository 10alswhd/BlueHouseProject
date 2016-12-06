#include<stdio.h>
#include<stdlib.h>

struct node{
	int info;
	struct node *left;
	struct node *right;
}*root;
int flag;

struct node *insert(struct node *root,int data){
	if(root == NULL){
		struct node *temp;
		temp = (struct node *)malloc(sizeof(struct node));
		temp -> info = data;
		temp -> right = temp -> left = NULL;
		return temp; 
	}
	else{
		if(data > (root -> info))
		root -> right = insert(root -> right,data);
		else if(data <= (root -> info))
		root -> left = insert(root -> left,data);
		return root;
		}
}

void search(struct node *root, int key) {
	if(root == NULL){
		return;
	}
	search(root -> left , key);
	if(root -> info == key){
		printf("there");
		flag = 1;
	}
	search(root -> right, key);
}

int main() {
	int num,i,n,key;

	struct node *temp;
	scanf("%d", &num);
	for(i=0;i<num;i++){
		scanf("%d", &n);
		root = insert(root,n);
	}
	scanf("%d", &key);
	search(root,key);
	if(flag == 0){
		printf("not there");
	}
	return 0;
}
