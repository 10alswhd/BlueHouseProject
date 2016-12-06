#include <stdbool.h>

struct bstnode
{
  int key;
  int val;
  struct bstnode *left;
  struct bstnode *right;
}

struct bst
{
struct bstnode *root
}

//recursive solution
bool bstnode_search (struct bstnode* node, int value)
{
  if (node==NULL)
  {
    return false;
  }
  if (value==(node->val))
  {
    return true;
  }
  
  else if (value<(node->val))
  {
    return bstnode_search(node->left,value);
  }
  
  else
  {
    return bstnode_search(node->right,value);
  }
}

//iterative solution
bood bstnode_search(struct bstnode *node, int value)
{
  while (node !=NULL)
  {
    if (value==(node->val))
    {
      return true;
    }
    
    else if (value<(node->val))
    {
      node==(node->left);
    }
    
    else 
    {
      node==(node->right);
    }
  }
  return false;
}

bool bst_search (struct bst* tree, int value)
{
  return bstnode_search (tree->root,value);
}
