#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
const int RMAX=100; 	//increase it later if nodes > 100 (to set max level of priority )
typedef struct tree{
	int val;
	int prior;
	struct tree* left;
	struct tree* right;
}tree;
tree* root=NULL;
tree* right_rotate(tree* t){
	tree* temp;		//  if the value that has a higher 
	temp=t->left; 		//  prioirty is on the left side of parent
	t->left=t->left->right;
	temp->right=t;
	return temp;
}
tree* left_rotate(tree* t){
	tree* temp;		// if the value that has a higher 
	temp=t->right;		// priority is on the right side of parent
	t->right=t->right->left;
	temp->left=t;
	return temp;
}
tree* insert(tree* t,int num){
	if(t==NULL)              // recursively insert value and check priority 
	{			 // at each level , perform rotation if required
		t=(tree*)malloc(sizeof(tree));
		t->val=num;
		t->prior=rand()%RMAX;
		t->left=NULL;
		t->right=NULL;
	}
	else if(num<t->val){
		t->left=insert(t->left,num);
		if(t->left->prior<t->prior)
			t=right_rotate(t);	
	}
	else{
		t->right=insert(t->right,num);
		if(t->right->prior<t->prior)
			t=left_rotate(t);
	}
	return t;
}
void print(tree* root)
{			// inorder printing 
	if(root==NULL)
		return;
	else
	{
		print(root->left);
		printf("val => %d  ",root->val);
		printf("priority => %d  ",root->prior);
		printf("Node Complete\n");
		print(root->right);
	}
}	
tree* search(tree* t,int x)
{
	if(t==NULL)
		return 0;
	if(t->val==x)
		return t;
	else if(t->val<x)
		return search(t->right,x);
	else
		return search(t->left,x);
}
tree* getparent(tree* t,int x)
{				// return the address of parent
	if(t->val==x)
		return NULL;
	if(t->left!=NULL)
	{
		if(t->left->val==x)
			return t;
	}
	if(t->right!=NULL)
	{
		if(t->right->val==x)
			return t;
	}
	if(x<t->val)
		return getparent(t->left,x);
	else if(x>t->val)
		return getparent(t->right,x);
}
void deleten(tree* t,int x)
{
	if(root==NULL){
		printf("TREAP EMPTY\n");
		return;
	}
	if(search(root,x)==0){
		printf("NOT PRESENT\n");
		return;
	}
	tree* ptr=search(root,x);
	tree* temp;   // while it is not the leaf node 
	while(ptr->left!=NULL||ptr->right!=NULL)
	{
		if(ptr->left==NULL)
		{			// nodes are present only to the right side 
			temp=getparent(root,x); // of the node to be deleted
			if(temp!=NULL){
				if(temp->right!=NULL&&temp->right->val==x)
					temp->right=left_rotate(ptr);
				else 
					temp->left=left_rotate(ptr);

			}
			else{
				root=left_rotate(ptr);
			}
		}
		else if(ptr->right==NULL)
		{			// nodes are present only to the left side
			temp=getparent(root,x); // of the node to be deleted
			if(temp!=NULL){
				if(temp->left!=NULL&&temp->left->val==x)
					temp->left=right_rotate(ptr);
				else
					temp->right=right_rotate(ptr);
			}
			else{
				root=right_rotate(ptr);
			}
		}
		else if(ptr->left->prior<ptr->right->prior)
		{
			temp=getparent(root,x); // node are present on both sides 
			if(temp!=NULL){         // but left node has more priority (minheap)
				if(temp->right!=NULL&&temp->right->val==x) // so side with less prior value 
					temp->right=right_rotate(ptr);     // has more priority
				else
					temp->left=right_rotate(ptr);

			}
			else
				root=left_rotate(ptr);
		}
		else
		{
			temp=getparent(root,x); // nodes are present on both sides
			if(temp!=NULL){		// but right node has more priority (minheap)
				if(temp->left!=NULL&&temp->left->val==x) // so side with less prior value 
					temp->left=left_rotate(ptr);	 // has more priority 
				else
					temp->right=left_rotate(ptr);
			}
			else
				root=right_rotate(ptr);
		}
		ptr=search(root,x); // refresh the address of node to be deleted
	}
	temp=getparent(root,x);
	tree* del;
	if(temp!=NULL)  // node to be deleted becomes leaf node
	{		// delete the node and set parent pointer to NULL
		if(temp->left!=NULL&&temp->left->val==x){ 
			del=temp->left;
			temp->left=NULL;
			free(del);
		}
		else if(temp->right->val==x){
			del=temp->right;
			temp->right=NULL;
			free(del);
		}
	}
	else
	{
		free(ptr);
		root=NULL;
	}
	printf("%d DELETED\n",x);
}
int main()
{	
	time_t z;
	srand(time(&z));      //seeding of random function
	char arr[100];
	char c;
	int a;
	root=NULL;
	while(1){
		scanf("%s",arr);
		c=arr[0];
		switch(c){
			case 'i':
				scanf("%d",&a);
				if(search(root,a)==0){
					root=insert(root,a);
					printf("%d INSERTED\n",a);
				}
				else
					printf("ALREADY PRESENT\n");
				break;
			case 'd':
				scanf("%d",&a);
				deleten(root,a);
				break;
			case 's':
				scanf("%d",&a);
				if(search(root,a)==0)
					printf("NOT FOUND\n");
				else
					printf("FOUND\n");
				break;
			case 'p':
				if(root==NULL)
					printf("TREAP EMPTY\n");
				else
					print(root);
				break;
			case 'q':
				return 0;
		}
	}	
	return 0;
}
