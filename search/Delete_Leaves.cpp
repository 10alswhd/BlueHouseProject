#include<iostream>
using namespace std;
struct node{
	int data;
	node *next;
};
node *head=NULL;
void insert(int info){
	node *temp = new node;
	temp->data = info;
	temp->next = NULL;
	
	if (head != NULL){
		temp->next = head;
	}
	head = temp;
}
struct nodeBST{
	int data;
	nodeBST *left;
	nodeBST *right;
};
nodeBST *root = NULL;
int Insert(int iteam){
	nodeBST *curr, *prev,*p;
	curr = root;
	prev = NULL;
	while (curr!=NULL){
		prev = curr;
		if (curr->data > iteam){
			curr = curr->left;
		}
		else{
			curr = curr->right;
		}
	}
	 p = new nodeBST;
	if (p == NULL){
		cout << "Can't allocated new() memory" << endl;
	}
	p->data = iteam;
	p->left = NULL;
	p->right = NULL;

	if (prev == NULL){
		root = p;
	}
	else{
		if (iteam > prev->data){
			prev->right = p;
		}
		else{
			prev->left = p;
		}
	}
	return (1);
}
void Del_Leaves(nodeBST *root){
	if (root == NULL){
		return;
	}
	if (root->right == NULL && root->left == NULL){
		insert(root->data);
	}

		Del_Leaves(root->left);
		Del_Leaves(root->right);
	
}
void Del(){
	node *temp = head;
	while (temp != NULL){
		Delete(root, temp->data);
		temp = temp->next;
	}
}
nodeBST *FindMin(nodeBST *root){
	while (root->left != NULL){
		root = root->left;
		return root;
	}
}
nodeBST *Delete(nodeBST *root,int iteam){
	if (root == NULL){
		return 0;
	}
	else if (root->data < iteam){
		root->right = Delete(root->right, iteam);
	}
	else if (root->data>iteam){
		root->left = Delete(root->left, iteam);
	}
	else{
	// case 1
		if (root->left == NULL &&	root->right == NULL){
			delete root;
			root = NULL;
		}
	//case 2
		else if (root->left == NULL){
			nodeBST *temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL){
			nodeBST *temp = root;
			root = root->left;
			delete temp;
		}
	//case 3
		else{
			nodeBST *temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}
	return root;
}
void In_Order(nodeBST *root){
	if (root != NULL){
		In_Order(root->left);
		cout << root->data;
		In_Order(root->right);
	}
}
void Del(){
	node *temp = head;
	while (temp != NULL){
		Delete(root, temp->data);
		temp = temp->next;
	}
}
int main(){
	Insert(5);
	Insert(2);
	Insert(9);
	Insert(3);
	Insert(7);
	In_Order(root);
	Del_Leaves(root);
	Del();
	cout << endl;
	In_Order(root);
//	Delete(root,3);
//	In_Order(root);

}
