#include <stdio.h>
#include <stdlib.h>
struct Node{
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* root=NULL;
//struct Node* newNode = (struct Node*)malloc(sizeof(struct Node*));
//struct Node** newNode=(struct Node* )malloc(sizeof(struct Node*));
	Node* newNode =new Node();
void GetNewNode(int data){
	newNode->data=data;
	newNode->left=newNode->right=NULL;
	root=newNode;
}
void Insert(struct Node* root,int data){
	if(root==NULL){
		GetNewNode(data);
	}
	else if(data<=root->data){
		Insert(root->left,data);
	}
	else Insert(root->right,data);
}
void search(Node* root, int key){
	if(root ==NULL){
		printf("No Element to Search\n");
	}
	else if(root->data==key){
		printf("FOUND");
	}
	else if(key<=root->data){
	search(root->left, key);
	}else {
	search(root->right,key);
	}

}
int main(){
	int Q;
	Insert(root,10);
	Insert(root, 8);
	Insert(root,4);
	Insert(root,120);
	scanf("%d",&Q);
	return 0;
}
