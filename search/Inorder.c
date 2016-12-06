#include <stdlib.h>
#include <stdio.h>

/**
* Node structure of the BST
*/
struct Node
{
   int data;
   struct Node* left;
   struct Node* right;
};

/**
 * Traverse the tree without using stack or recursion
 */
void inorder_traversal(struct Node *root)
{
  struct Node *curr, *prev;

  if(root == NULL)
     return;

  curr = root;
  while(curr != NULL)
  {
    if(curr->right == NULL)
    {
      printf("%d ", curr->data);
      curr = curr->left;
    }
    else
    {
      prev = curr->right;
      while(prev->left != NULL && prev->left != curr)
        prev = prev->left;

      if(prev->left == NULL)
      {
        prev->left = curr;
        curr = curr->right;
      }
      else
      {
        prev->left = NULL;
        printf("%d ",curr->data);
        curr = curr->left;
      }
    }
  }

  printf("\n");
}

/**
 * Insert a new node into the tree
 */
void new_node(int data, struct Node *root)
{
  struct Node *node = (struct Node*) malloc(sizeof(struct Node));
  node->data = data; node->left = NULL; node->right = NULL;

  struct Node *temp = root;

  while(1)
  {
    if (temp->data > data)
    {
      if (temp->right != NULL)
        temp = temp->right;
      else
      {
        temp->right = node;
        break;
      }
    }
    else if (temp-> data < data)
    {
      if (temp->left != NULL)
        temp = temp->left;
      else
      {
        temp->left = node;
        break;
      }
    }
    else
      break;
  }
}

int main()
{
  int i = 0, size, *values;

  printf("\nEnter the number of values: ");
  scanf("%d", &size);

  values = (int *) malloc(size * sizeof(int));

  printf("\nEnter data: ");
  for (i = 0; i < size; ++i)
    scanf("%d", &values[i]);

  // Create the root node
  struct Node *root = (struct Node*) malloc(sizeof(struct Node));
  root->data = values[0]; root->left = NULL; root->right = NULL;

  // Insert other values
  for (i = 1; i < size; ++i)
    new_node(values[i], root);

  printf("\nIn-order traversal: ");
  inorder_traversal(root);
  return 0;
}
