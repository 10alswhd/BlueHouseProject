#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	struct node* left;
	struct node* right;
	int value;
}treenode;

int add_node(treenode**tree, int value);
treenode* get_node();
treenode* search_value(treenode*tree,int searchvalue);
treenode* closest_ancestor(treenode*,treenode*,treenode*,int*count);




int main(){
	treenode* tree = NULL; // this will be the tree root pointer
	int input[17] = {15,7,50,2,12,25,75,1,4,8,14,20,40,60,80,100,120};
	int count=0;
	int i;
	for(i=0;i<17;i++)
	add_node(&tree,input[i]);

	printf("%d",(closest_ancestor(tree,search_value(tree,40),search_value(tree,120),&count))->value);
	return 0;
}
treenode* closest_ancestor(treenode*root,treenode* node1,treenode*node2,int*count){
	
	treenode* returnvalue = NULL;
	int sum;
	treenode*returnleft;
	treenode*returnright;
	
	if(root){
		//printf("%d ",*count);
		if(root==node1)(*count)+=1;
		if(root==node2)(*count)+=2;
		
		sum = 0;
		returnleft = closest_ancestor(root->left,node1,node2,&sum); 
		                                                                    
		if(returnleft)returnvalue = returnleft; 
		else
		{
			returnright = closest_ancestor(root->right,node1,node2,&sum);
			if(returnright)returnvalue = returnright;
			else if(sum==3)returnvalue = root;
		}
		*count +=sum;
		}
	return returnvalue;
}

treenode* search_value(treenode*tree,int searchvalue){
	treenode* trav = tree;
	while(trav!=NULL)
	{
		if(trav->value==searchvalue)   // made mistake in == vs =
		return trav;
		if(trav->value>searchvalue)
		trav = trav->left;
		else
		trav = trav->right;
		if(trav->value==searchvalue)
		return trav;
	}
	return NULL;
}

int add_node(treenode**tree, int value)  {   
	// TODO: implement recursive version of add_node
	int left;  // will decide the direction
	left=0;
	
	treenode* x = get_node(); // get the pointer to allocated memory
	x->value = value;
	// 2 cases arises
	// if it is the first node to be entered
	if(*tree==NULL)
	{
		*tree = x;
		return 0;
	}
	else // if not we will have to traverse
	{
		treenode* trav = *tree;
		treenode* follow = *tree; // will follow the trav
		while(trav!=NULL)
		{
			if(x->value<trav->value)
			{    // traversing left                
				follow = trav;
				left = 1;
				trav= trav->left;
				continue;
			}
			else
			{
				follow = trav;
				left = 0;
				trav = trav->right;
				continue;
			}
		}
		if(left)
		follow->left = x;
		else
		follow->right= x;
		return 0;
	}
	return 1;
}

treenode* get_node(){
	treenode* x = (treenode*)malloc(sizeof(struct node));
	x->right = NULL;
	x->left = NULL;
	x->value = -1;
	return x;
}
