#include "bst.h"

void insert(tree_node_t** root, tree_node_t* node) {
  if(!(*root)) {
    *root = node;
  }
  else {
    if(node->data < (*root)->data) {
      insert(&(*root)->left, node);
    }
    else if(node->data > (*root)->data) {
      insert(&(*root)->right, node);
    }
    else {
      printf("\n>>> Duplicate data!!\n");
    }
  }
}

void find(tree_node_t* root, int* data) {
  if(!root) {
    printf("\n>>> Data does not exist!!\n");
  }
  else {
    if(*data < root->data) {
      find(root->left, data);
    }
    else if(*data > root->data) {
      find(root->right, data);
    }
    else {
      printf("\n>>> Data found!!\n");
    }
  }
}

void display(tree_node_t* root) {
  if(root->left) {
    display(root->left);
  }
  printf("%d ", root->data);
  if(root->right) {
    display(root->right);
  }
}
