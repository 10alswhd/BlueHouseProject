#include "KDTree.h"
#include <iostream>
#include <math.h>
using namespace std;

node *KDTree = 0;

// Print the KD Tree
void printTree(node *Tree)
{
    if(Tree != 0)
    {
        printTree(Tree->left);
        cout << "(" << Tree->p.x << " , " << Tree->p.y << ")";
        printTree(Tree->right);
    }
}

void printTree()
{
    printTree(KDTree);
    cout << endl;
}


//inserts received points into the correct position of the Tree
void tree(point p, int & depth, node*& Tree)
{
    //If the receieved root is null insert the node
    if(Tree == 0)
    {
        Tree = new node; Tree->p = p; Tree->left = 0; Tree->right = 0;
    }
    else
    {
        //If the depth of the tree is an even number compare the X axis else compare Y
        //Then call self with the correct side "left" or "Right"
        if(depth % 2 == 0)
        {
            if(p.x < Tree->p.x){depth++; tree(p, depth, Tree->left);}
            else{depth++; tree(p, depth, Tree->right);}
        }
        else
        {
              if(p.y < Tree->p.y){depth++; tree(p, depth, Tree->left);}
            else{depth++; tree(p, depth, Tree->right);}
        }
    }
}

//build tree from a list of points
void tree(point pointList[], int depth)
{
    for(int i = 0; i < 6; i++)
    {
        tree(pointList[i], depth, KDTree);
    }
}

//Calculate distance between 2 points (Got an error while trying to use 2 points so had to change it to 4 ints)
double distance(int p1x, int p1y, int p2x, int p2y)
{
    int a, b;
    a = p1y - p2y;
    b = p1x - p2x;
    return sqrtf(a*a+b*b);
}

//Searches the existing KD tree for the nearest neighbour
void kdsearchnn(node *here, point p, point& best)
{
    if(here == 0){return;}
    //If there no best then set it to here
    if(best.x + best.y == 0 ){best.x = here->p.x; best.y = here->p.y;}

    //compare the distance of the 2 points, if a closer point is found set it to the new best
    if(distance(p.x, p.y, here->p.x, here->p.y) < distance(p.x, p.y, best.x, best.y))
    {
       best.x = here->p.x; best.y = here->p.y;
    }
    //call self to check rest of tree
    kdsearchnn(here->left, p, best);
    kdsearchnn(here->right, p, best);
}
//Intialize nearest neighbour search
void kdsearchnn(point p)
{
    point best;
    best.x = 0; best.y = 0;
    kdsearchnn(KDTree, p, best);
    cout << "(" << best.x << "," << best.y << ")" << endl;
}

//gives new point in tree to be inserted
void insert(point iP, int depth)
{
    tree(iP, depth, KDTree);
}
