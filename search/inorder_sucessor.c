#include<stdio.h>
#include<stdlib.h>

struct node{
        int value;
        struct node *left;
        struct node *right;
};
typedef struct node Node;
 
Node * find_minimum(Node *root){
        if(!root)
                return NULL;

        while(root->left){
                root = root->left;

        }
        return root;
}

Node *inorder_success(Node *root, int K){

        Node * successor = NULL;
        Node *current  = root;
        if(!root)
                return NULL;

        while(current->value != K){
                if(current->value >K){
                        successor = current;
                        current= current->left;
                }
                else
                        current = current->right;
        }
        if(current && current->right){
                successor = find_minimum(current->right);
        }

        return successor;
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
        Node * last = NULL;
        Node *ptrToHead = NULL;
        //Creating a binary tree
        root = addNode(root,30);
        root = addNode(root,20);
        root = addNode(root,15);
        root = addNode(root,25);
        root = addNode(root,40);
        root = addNode(root,37);
        root = addNode(root,45);
 
        Node *successor = inorder_success(root);
        if(successor){
                printf("%d" , successor->value);
        }
 
        return 0;
}
