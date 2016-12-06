#include <stdio.h>
#include <stdlib.h>
#define TYPE int
typedef struct
{
    TYPE data;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

bstNode* newNode (TYPE data) //argument: the data to be inserted
{
    bstNode *p=malloc(sizeof(bstNode)); //dynamically allocates memory for the new node
    p->data=data;
    //for initialization
    p->left=NULL;
    p->right=NULL;
    return p; //return a pointer to the node created

}

/* return the position of the smallest element,start at the root and go left as long as there is a left child. The
stopping point is the smallest element.*/
bstNode* find_min (bstNode* root)
{
    if (root==NULL)
        return NULL;
    else if ( root->left ==NULL)
    {
        return root;

    }
    else
        return find_min(root->left);
}
/* return the position of the largest element ,start at the root and go left as long as there is a right child. The
stopping point is the largest element.*/
bstNode* find_max (bstNode *root)
{

    if(root==NULL)
        return NULL;
    else if (root->right ==NULL)
        return root;
    else
        return find_max(root->right);
}
bstNode* insertNode(bstNode *root,TYPE data) //arguments:pointer to the root of the tree, data to be inserted
{
    if (root==NULL)
    {
        root=newNode(data);
    }
    //if data inserted is bigger than the node's current value, insert in the right subtree
    else if(root->data <data)
    {
        root->right=insertNode(root->right,data);
    }
    //if data inserted is smaller than the node's current value, insert in the left subtree

    else if(root->data > data)
    {
        root->left=insertNode(root->left,data);
    }
    else //if equal do nothing, in BST NO duplicate are allowed
    {

    }

    return root;
}

int search (bstNode* root, TYPE data)
{
    if( root==NULL)
    {
        return 0;
    }
    else if( root->data == data)
    {
        return 1;
    }
    else if (root->data <data)
    {
        return search(root->right,data);
    }
    else
    {
        return search(root->left,data);
    }
}
bstNode* deleteNode (bstNode *root, TYPE data )
{
    bstNode *temp_node,*child;
    if(root == NULL)
    {
        printf("Not found");
    }
    else if( root->data < data) //Go right
    {
        root->right=deleteNode(root->right,data);
    }
    else if (root-> data > data) //Go left
    {
        root->left=deleteNode(root->left, data);
    }
    else //element found
    {
        if(root->left && root->right)   //two children
        {
            //replace with smallest in right subtree
            temp_node=find_min(root->right);
            root->data=temp_node->data;
            root->right=deleteNode(root->right,root->data);
        }
        else //one child only
        {
            temp_node=root;
            if(root->left==NULL) //right child only
            {
                child=root->right;

            }
            if(root->right ==NULL) //left child only
            {
                child=root->left;

            }
            free(temp_node);
            return child;
        }

    }
    return root;

}

void print_inorder(bstNode *root)
{
    if(root !=NULL)
    {
        print_inorder(root->left);
        printf("%d \t",root->data);
        print_inorder(root->right);
    }
}
void printf_preorder (bstNode *root)
{
    if(root !=NULL)
    {
        printf("%d \t",root->data);
        print_preorder(root->left);
        print_preorder(root->right);
    }

}
void print_postorder (bstNode* root)
{
    if (root !=NULL)
    {
        print_postorder(root->left);
        print_postorder(root->right);
        printf("%d \t",root->data);

    }
}
void main ()
{
    bstNode *root=NULL;
    root=insertNode(root,4);
    root=insertNode(root,2);
    root=insertNode(root,9);
    root=insertNode(root,10);
    root=insertNode(root,8);
    root=deleteNode(root,10);
    printf("PreOrder: \n");
    printf_preorder(root);
    printf("\n \n");
    printf("InOrder: \n");
    print_inorder(root);
    printf("\n \n");
    printf("PostOrder: \n");
    print_postorder(root);
    printf("\n \n");




}
