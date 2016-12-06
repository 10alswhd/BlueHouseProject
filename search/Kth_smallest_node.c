#include<stdio.h>
#include<stdlib.h>
 
struct node{
        int value;
        struct node *left;
        struct node *right;
};
typedef struct node Node;

/* This function calculates the size of tree rooted at Node */
int find_size_of_left_tree(Node *node){
  if(!node)
    return 0;

  return 1 + find_size_of_left_tree(node->left)
           + find_size_of_left_tree(node->right);
}

int find_kth_node(Node *root, int K){

    if(!root)
      return 0;

    int no_left = find_size_of_left_tree(root->left); 
    /* If there are K-1 nodes in left sub tree */     
    
    if(no_left  == K-1){
      return root->value;
    }
   /* If there are more than K-1 nodes in left sub tree */
    else if(no_left > K-1){
      return find_kth_node(root->left, K);
    }
    /* If there are less than K nodes in left sub tree */
    else{
      return find_kth_node(root->right, K-no_left-1);
    }
}
Node * create_node(int value){
  Node * temp =  (Node *)malloc(sizeof(Node));
  temp->value = value;
  temp->right= NULL;
  temp->left = NULL;
  return temp;
  
}
Node * addNode(Node *node, int value){
  if(node == NULL){
      return create_node(value);
  }
  else{
     if (node->value > value){
        node->left = addNode(node->left, value);
      }
      else{
        node->right = addNode(node->right, value);
      }
  }
  return node;
}
 
/* Driver program for the function written above */
int main(){
  Node *root = NULL;
  
  //Creating a binary tree
  root = addNode(root,30);
  root = addNode(root,20);
  root = addNode(root,15);
  root = addNode(root,25);
  root = addNode(root,40);
  root = addNode(root,37);
  root = addNode(root,45);
  
  find_kth_node(root, 4);
  
  return 0;
}
