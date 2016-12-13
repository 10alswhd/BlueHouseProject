#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"


bintree_t *newBT(int i)
{
    bintree_t *t =  (bintree_t *)malloc(sizeof(bintree_t));
    t->left = t->right = NULL;
    t->node = i;
    return t;
}


int Bsearch(bintree_t *t, int i)
{
    if (t->node==i) {
        return 1;
    }else if (t->node>i) {
        /* left */
        if (t->left==NULL) {
            return 0;
        }else {
            return search(t->left, i);
        }
    }else {
        /* right */
        if (t->right==NULL) {
            return 0;
        }else {
            return search(t->right, i);
        }
    }
}


void Binsert(bintree_t *t, int i)
{
    if (t->node>i) {
        if (t->left==NULL)
            t->left = newBT(i);
        else
            Binsert(t->left, i);
    }else if (t->node<i) {
        if (t->right==NULL)
            t->right = newBT(i);
        else
            Binsert(t->right, i);
    }
}


void Bdelete(bintree_t *t)
{
    if (t!=NULL) {
        bintree_t *right = t->right;
        bintree_t *left = t->left;
        free(t);
        delete(left);
        delete(right);
    }
}
