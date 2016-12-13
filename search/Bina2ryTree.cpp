#include "BinaryTree.h"
#include "BinaryNode.h"
#include "RuntimeException.h"
#include <iostream>

int searchCostCount = 0;

using namespace std;

BinaryNode *BinarySearchTree::findMin(BinaryNode *t)
	throw(EmptyTree)
{
	if (t == NULL) throw EmptyTree();
	
	while (t->getLeft() != NULL) t = t->getLeft();

	return t;
}

BinaryNode *BinarySearchTree::find(int x, BinaryNode *t)
throw(ItemNotFound)
{
	while (t != NULL)
	
		if (x < t->getElem()) t = t->getLeft();
		else if (x > t->getElem()) t = t->getRight();
		else return t; // found
	throw ItemNotFound();
}

BinaryNode *BinarySearchTree::insert(int x, BinaryNode *t) 
throw(DuplicateItem)
{
	
	if (t == NULL)
	{
		t = new BinaryNode(x);
		searchCostCount++;
		t->setCost(searchCostCount);
		searchCostCount = 0;
		
	}
	else if (x < t->getElem())
	{	
		searchCostCount++;	
		t->setLeftNode(insert(x, t->getLeft()));		
	}
	else if (x > t->getElem()) 
	{	
		searchCostCount++;
		t->setRightNode(insert(x, t->getRight())); 		
	}
	else                     throw DuplicateItem();
	
	

	return t;
}

BinaryNode *BinarySearchTree::removeMin(BinaryNode *t)
throw(ItemNotFound)
{
	if (t == NULL) throw ItemNotFound();
	if (t->getLeft() != NULL) t->setLeftNode(removeMin(t->getLeft()));
	else
	{
		BinaryNode *node = t;
		t = t->getRight();
		delete node;
	}
	
	return t;
}

BinaryNode *BinarySearchTree::remove(int x, BinaryNode *t)
throw(ItemNotFound)
{
	if (t == NULL) throw ItemNotFound();
	if (x < t->getElem()) t->setLeftNode(remove(x, t->getLeft()));
	else if (x > t->getElem()) t->setRightNode(remove(x, t->getRight()));
	else if (t->getLeft() != NULL && t->getRight() != NULL)
	{
		t->setElem(findMin(t->getRight())->getElem());
		t->setRightNode(removeMin(t->getRight()));
	} 
	else 
	{
		BinaryNode *node = t;
		t = (t->getLeft() != NULL) ? t->getLeft() : t->getRight();
		delete node;
	}

	return t;
}

void BinarySearchTree::merge(int rootItem, BinarySearchTree& t1, BinarySearchTree& t2)
{
	if (t1.root == t2.root && t1.root != NULL)
	{
			cerr << "Left tree == right tree, merge aborted" 
				 << endl;
			return;
	}

	if (this != &t1 && this != &t2) deleteTree(root);
	root = new BinaryNode(rootItem, 0, t1.root, t2.root);
	if (this != &t1) t1.root = NULL;
	if (this != &t2) t2.root = NULL;
}

void BinarySearchTree::deleteTree(BinaryNode *root)
{ 
	if (root == NULL) return; // nothing to delete
	if (root->getLeft() != NULL)  deleteTree(root->getLeft());
	if (root->getRight() != NULL) deleteTree(root->getRight());
	delete root;
}
