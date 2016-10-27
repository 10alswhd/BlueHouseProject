// BinaryTree.cpp : Defines the entry point for the console application.
// L.D.C.Lakmal

#include "stdafx.h"
#include <iostream>

using namespace std;

typedef int element;

//bintree_node class for store nodes with values and operate their functions...
class bintree_node{
private:
	element value;
	bintree_node* left;
	bintree_node* right;
	int index;
public:
	element getValue();
	void setValue(element val);
	bintree_node* getLeft();
	void setLeft(bintree_node* node);
	bintree_node* getRight();
	void setRight(bintree_node* node);
	int getIndex();
	void setIndex(int index);
};
element bintree_node::getValue(){
	return this->value;
}
void bintree_node::setValue(element val){
	this->value = val;
}
bintree_node* bintree_node::getLeft(){
	return this->left;
}
void bintree_node::setLeft(bintree_node* node){
	this->left = node;
}
bintree_node* bintree_node::getRight(){
	return right;
}
void bintree_node::setRight(bintree_node* node){
	this->right = node;
}
int bintree_node::getIndex(){
	return this->index;
}
void bintree_node::setIndex(int index){
	this->index = index;
}

//method for add node as a left child...
int add_left_child(bintree_node* parent, element value, int index){
	bintree_node* leftNode = new bintree_node();
	leftNode->setValue(value);
	leftNode->setLeft(NULL);
	leftNode->setRight(NULL);
	leftNode->setIndex(index);

	if(parent->getLeft() == NULL){
		parent->setLeft(leftNode);
		return 1;
	}
	return 0;
}

//method for add node as a right child...
int add_right_child (bintree_node* parent, element value, int index){
	bintree_node* rightNode = new bintree_node();
	rightNode->setValue(value);
	rightNode->setLeft(NULL);
	rightNode->setRight(NULL);
	rightNode->setIndex(index);

	if(parent->getRight() == NULL){
		parent->setRight(rightNode);
		return 1;
	}
	return 0;
}

bintree_node* create_tree(bintree_node* tree, element* elements, int size);
void insert(bintree_node* tree, element value, int index);
bintree_node* expand_tree(bintree_node* root, element* elements, int size);
void traverse_inOrder(bintree_node* root);
void traverse_preOrder(bintree_node* root);
void traverse_postOrder(bintree_node* root);

int index = 0;		//variable for keep the position of the nodes....
void main(){
	bintree_node* tree = new bintree_node();
	element arr1[7] = {10,20,30,40,50,60,70};
	create_tree(tree, arr1, 7);

	cout << "In order traversal : ";
	traverse_inOrder(tree);
	cout << endl << "Pre order traversal : ";
	traverse_preOrder(tree);
	cout << endl << "Post order traversal : ";
	traverse_postOrder(tree);
	cout << endl << endl;

	cout << "After expanding the tree...." << endl;
	element arr2[8] = {80,90,100,110,120,130,140,150};
	expand_tree(tree, arr2, 8);

	cout << "In order traversal : ";
	traverse_inOrder(tree);
	cout << endl << "Pre order traversal : ";
	traverse_preOrder(tree);
	cout << endl << "Post order traversal : ";
	traverse_postOrder(tree);
	cout << endl << endl;

	system("PAUSE");
}

//method for create tree with the given set of values...
bintree_node* create_tree(bintree_node* tree, element* elements, int size){
	for(int i=0; i<size; i++){
		insert(tree, elements[i], ++index);
	}
	return tree;
}

//method for insert a node to the relavant place of the tree...
void insert(bintree_node* parent, element value, int index){
	if (parent == NULL){
		return;
	}
	if(index == 1){
		parent->setValue(value);
		parent->setLeft(NULL);
		parent->setRight(NULL);
		parent->setIndex(index);
	}else if(parent->getIndex() * 2 == index){
		add_left_child(parent, value, index);
	}else if(parent->getIndex() * 2 + 1 == index){
		add_right_child(parent, value, index);
	}else{
		insert(parent->getLeft(), value, index);	
		insert(parent->getRight(), value, index);
	}
}

//method for expand the tree with a given set of values...
bintree_node* expand_tree(bintree_node* root, element* elements, int size){
	for(int i=0; i<size; i++){
		insert(root, elements[i], ++index);
	}
	return root;
}

//method for in-order traversal of the tree...
void traverse_inOrder(bintree_node* root){
	if (root == NULL)
		return;
	traverse_inOrder(root->getLeft());
	cout << root->getValue() <<  " ";
	traverse_inOrder(root->getRight());
}

//method for pre-order traversal of the tree...
void traverse_preOrder(bintree_node* root){
	if (root == NULL)
		return;
	cout << root->getValue() << " ";
	traverse_preOrder(root->getLeft());
	traverse_preOrder(root->getRight());
}

//method for post-order traversal of the tree...
void traverse_postOrder(bintree_node* root){
	if (root == NULL)
		return;
	traverse_postOrder(root->getLeft());
	traverse_postOrder(root->getRight());
	cout << root->getValue() << " ";
}
