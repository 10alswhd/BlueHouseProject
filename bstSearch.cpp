#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <queue>
 
using namespace std;
 
struct BstNode
{
  int data;
  struct BstNode *left;
  struct BstNode *right;
};
 
 
struct BstNode *newNode(int data)
{
  struct BstNode *node = (struct BstNode*)malloc(sizeof(struct BstNode));
 
  node->data = data;
  node->left = NULL; 
  node->right = NULL;
  return node;
}
 
 
struct BstNode* 
insert(struct BstNode *node, int data)
{
 
	if(node == NULL) {
		return newNode(data);
	}
 
	if(data > node->data){
		node->right = insert(node->right, data);
	} else {
		node->left = insert(node->left, data);
	}
 
	return node;
} 


struct BstNode*
searchKey(struct BstNode *root, int data)
{

	if(root == NULL || root->data == data) {
		return root;
	}

	// if data is less than current roots data 
	// then we need to traverse left
	if(data < root->data){
		return searchKey(root->left, data);
	} else {
		return searchKey(root->right, data);
	}

} 


struct BstNode*
searckey_nr(struct BstNode *root, int data) {

	while (root != NULL && root->data != data){

		// this condition is not required, when it enters the loop 
		// root->data will be equal to data anyway
		if(root->data == data){
			break;
		}

		if(data < root->data){
			root = root->left;
		} else {
			root = root->right;
		}
	}

	return root;
}
 
int main()
{
	int arr[] = {5,3,1,4,2,7,6,8,9};
 
	struct BstNode *root = NULL;
 
	for(unsigned int i=0; i < sizeof(arr)/sizeof(arr[0]); i++){
		root = insert(root, arr[i]);
	}

	int key;
	printf("Enter key to search: ");
	scanf("%d", &key);

	
	struct BstNode *found = searckey_nr(root, key);

	if(found == NULL){
		printf("search key %d is not found \n", key);
	} else {
		printf("Search key %d is found in the tree\n", key);
	}
 
}
