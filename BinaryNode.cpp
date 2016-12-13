#include "BinaryTree.h"

int BinaryNode::size(BinaryNode *t)
{ 

	if (t == NULL)
	return 0;
	else
	return 1 + size(t->left) + size(t->right);
}

int BinaryNode::height(BinaryNode *t) 
{ 
	if (t == NULL)
	return -1;
	else 
	{
		int hlf = height(t->left), hrt = height(t->right);
		return (hlf > hrt) ? 1+hlf : 1+hrt; // 1+max(hlf,hrt)
	}
}

BinaryNode *BinaryNode::copy()
{ 
	BinaryNode *root = new BinaryNode(element);
	
	if (left != NULL)
	root->left = left->copy();
	
	if (right != NULL)
	root->right = right->copy();
	
	return root;
}
