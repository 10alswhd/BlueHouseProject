#include<stdlib.h>
#include<stdio.h>


struct bin_tree {
    long key, value;
    struct bin_tree *right, *left;
};
typedef struct bin_tree node;


void insert_at(node **place, long key, long value)
{
    //insert the key
    node *temp;

    if (!(*place))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = 0;
        temp->key = key;
    }
    temp->value = value;
    *place = temp;
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node** search(node ** tree, long key)
{
    node** p = tree;
    node* n = *p;
    while (n)
    {
        if (key == n->key)
            return p;

        p = key < n->key ? &(n->left) : &(n->right);
        n = *p;
    }

    return p;
}


node *collatz;


long Collatz(long j){
    node **tmp;
    tmp = search(&collatz, j);
    if (!(*tmp))
    {
        long nr = (j % 2) ? ((3 * j) + 1) : (j /2);
        long value = Collatz(nr) + 1;
        insert_at(tmp, j, value);
    }
    return (*tmp)->value;
}

long biggest = 0;
long chain = 0;

void find_biggest(node * tree){

    if (tree)
    {
        if(tree->value > chain){
            chain = tree->value;
            biggest = tree->key;
        }
        find_biggest(tree->left);
        find_biggest(tree->right);
    }
}


long main(){
    collatz = NULL;
    insert_at(&collatz, 1, 1);
    long j;
    for (j = 1000000; j > 0; j--){
        Collatz(j);
    }
    //find_biggest(collatz);
    fprintf(stdout, "Result: Nr: %li Chain: %li\n", biggest, chain);
    return 0;
}
