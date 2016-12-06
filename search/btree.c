#include <stdio.h>
#include <stdlib.h>
// #include "Tree.h"

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin( SearchTree T);
Position FindMax( SearchTree T);

SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve( Position P);
void PrintTree();


struct TreeNode
{
        ElementType Element;
        SearchTree Left;
        SearchTree Right;
};

int main()
{
   struct TreeNode node;
   node.Element = 10;
   node.Left=NULL;
   node.Right=NULL;
   SearchTree st = &node;
   Insert(2,st);
   Insert(1,st);
   Insert(3,st);

   PrintTree(st);

    return 0;
}


SearchTree MakeEmpty(SearchTree T){
    if (T != NULL)
    {
            MakeEmpty(T->Right);
            MakeEmpty(T->Left);
    };
    return NULL;
}
Position Find(ElementType X, SearchTree T){
    if (T == NULL)
            return NULL;
    else
    if (X < T->Element)
            return Find(X, T->Left);
    else
    if (X > T->Element)
            return Find(X, T->Right);
    else
        return T;
}
Position FindMin( SearchTree T){
    if (T == NULL)
            return NULL;
    else
    if (T->Left != NULL)
        return FindMin(T->Left);
    else
        return T;
}
Position FindMax( SearchTree T){
/*
    if (T == NULL)
            return NULL;
    else
    if (T->Right != NULL)
        return FindMax(T->Right);
    else
        return T;
*/
    if (T != NULL)
            while (T->Right != NULL)
                    T = T->Right;
    return T;
}

SearchTree Insert(ElementType X, SearchTree T){

    if (T == NULL)
    {
        T  = malloc(sizeof(struct TreeNode));

        if (T  == NULL)
            printf("Data Error!");
        T->Element = X;
        T->Left = NULL;
        T->Right = NULL;
    }
    else
    if (X < T->Element)
            T->Left = Insert(X, T->Left);
    else
    if (X > T->Element)
            T->Right = Insert(X, T->Right);

    return T;
}

SearchTree Delete(ElementType X, SearchTree T){
        if (T == NULL)
                printf("NO DATA FOUND!");
        else
        if (X < T->Element)
                T->Left = Delete(X, T->Left);
        else
        if (X > T->Element)
                T->Right = Delete(X, T->Right);
        else
        {   //have two children
            if (T->Right&&T->Left){
                Position tmpCell = FindMin(T->Right);
                T->Element = tmpCell->Element;
                T->Right = Delete(T->Element, T->Right);
                }
            else{
                Position tmpCell = T;
                if (T->Right == NULL){
                    T = tmpCell->Left;
                }
                else
                {
                    T = tmpCell->Right;
                };
                free(tmpCell);
            }
        }
        return T;
}


ElementType Retrieve( Position P);
void PrintTree(SearchTree T){
    if(T == NULL)
        printf("NO DATA!!!");
    else{
        //printf("%d\t", T->Element);
        if(T->Left != NULL){
            printf("Left-> %d", T->Left->Element);
            PrintTree(T->Left);
            };
        if(T->Right != NULL){
            printf("Right-> %d", T->Right->Element);
            PrintTree(T->Right);
            };
    }
    // printf("\n");
}
