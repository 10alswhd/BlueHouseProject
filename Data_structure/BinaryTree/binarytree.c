#include <stdio.h>
#include <stdlib.h>
#define ElemType int
typedef struct tree{
    ElemType item;
    tree *left;
    tree *right;
}tree;

/*
void Init(tree *T){
    T=(tree *)malloc(sizeof(tree));
    T->left=NULL;
    T->right=NULL;
}
*/
tree * search_tree(tree *T,ElemType e){
    if (T==NULL)
        return NULL;
    if(T->item==e)
        return T;
    if(T->item<e)
        return search_tree(T->right,e);
    else
        return search_tree(T->left,e);
}

tree *find_min(tree *T){
    tree *iter=T;
    if iter==NULL
        return NULL;
    while(iter->left!=NULL)
        iter=iter->left;
    return iter;
}

void traverse_tree(tree *T){
    if (T!=NULL){
        traverse_tree(T->left);
        process(T->item);
        traverse_tree(T->right);
    }
}

void insert_tree(tree *T,ElemType e){
    if(T==NULL){
        tree *p;
        p=malloc(sizeof(tree));
        p->item=e;
        p->right=p->left=NULL;
        T=p;
        return;
    }
    if(T->item>e)
        insert_tree(T->left,e);
    else
        insert_tree(T->right,e);
    }
}
