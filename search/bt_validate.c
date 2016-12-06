#include <stdio.h>
#include <stdlib.h>

// given a root noot, determine whether the tree is ordered or not

struct node {
    int data;
    struct node *left;
    struct node *right;
};


struct node * newNode(int data){
    struct node *node = malloc(sizeof(struct node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    
    return node;
}

struct node * insert_bst(struct node *node, int data){
    if(node == NULL){
        return newNode(data);
    }
    else {
        if(data < node->data)
            node->left = insert_bst(node->left, data);
        else
            node->right = insert_bst(node->right, data);
    }
    
    return node;

}

struct node * insert_bt(struct node *node, int data){
    if(node == NULL){
        return newNode(data);
    }
    else {
        if(data > node->data)
            node->left = insert_bt(node->left, data);
        else
            node->right = insert_bt(node->right, data);
    }
    
    return node;

}


int validate(struct node *node){
    
    if(node == NULL)
        return 1;
    
    struct node *leftnode = node->left;
    struct node *rightnode = node->right;
    
    if(leftnode && rightnode){
        if((leftnode->data > node->data) || (node->data > rightnode->data))
            return 0;
        else
            return (validate(leftnode) &&  validate(rightnode));
    }
   
    return (validate(leftnode) &&  validate(rightnode));

}


int main(void){
    struct node *root = NULL;
    
    root = insert_bst(root, 2);
    root = insert_bst(root, 1);
    root = insert_bst(root, 3);
    
    int is_bst = validate(root);
    
    if(is_bst)
        printf("Is a binary search tree\n");
    else
        printf("Is not binary search tree\n");
    
    struct node *head = NULL;
    
    head = insert_bt(head, 2);
    head = insert_bt(head, 1);
    head = insert_bt(head, 3);
    
    is_bst = validate(head);
    
    if(is_bst)
        printf("Is a binary search tree\n");
    else
        printf("Is not binary search tree\n");
    
    
    
    return 0;
}
