#include <stdio.h>
#include <stdlib.h>

struct node {
        int data;
        struct node *left;
        struct node *right;
};

struct node *tree = NULL;

void create_tree(struct node *tree) {
        tree = NULL;
}
struct node *insert(struct node *tree, int val) {
        struct node *temp, *nodeptr, *parent;
        temp = (struct node*)malloc(sizeof(struct node));
        temp->data = val;
        temp->left = NULL;
        temp->right = NULL;
        if(tree==NULL) {
                tree = temp;
                tree->left=NULL;
                tree->right=NULL;
        }
        else {
                parent=NULL;
                nodeptr=tree;
                while(nodeptr!=NULL) {
                        parent=nodeptr;
                        if(val<nodeptr->data)
                                nodeptr=nodeptr->left;
                        else
                                nodeptr = nodeptr->right;
                }
                if(val<parent->data)
                        parent->left = temp;
                else
                        parent->right = temp;
        }
        return tree;
}


int totalNodes(struct node *tree) {
        if(tree == NULL)
                return 0;
        else
                return(totalNodes(tree->left) + totalNodes(tree->right) + 1);
}
int totalExternalNodes(struct node *tree) {
        if(tree==NULL)
                return 0;
        else if((tree->left==NULL) && (tree->right==NULL))
                return 1;
        else
                return (totalExternalNodes(tree->left) + totalExternalNodes(tree->right));
}
int totalInternalNodes(struct node *tree) {
        if( (tree==NULL) || ((tree->left==NULL) && (tree->right==NULL)))
                return 0;
        else
                return (totalInternalNodes(tree->left) + totalInternalNodes(tree->right) + 1);
}
struct node *mirror(struct node *tree) {
        struct node *ptr;
        if(tree!=NULL) {
                mirror(tree->left);
                mirror(tree->right);
                ptr=tree->left;
                tree->left = tree->right;
                tree->right = ptr;
        }
        return tree;
}
struct node *clone(struct node *tree) {
        if(tree == NULL) return tree;
        struct node *temp=(struct node*)malloc(sizeof(struct node));
        temp->data=tree->data;
        temp->left=clone(tree->left);
        temp->right=clone(tree->right);
        return temp;
}
int main() {
        int choice, val;
        struct node *ptr;
        create_tree(tree);
        do {
                printf("\n 1. Insert: ");
                printf("\n 2. Total number of nodes: ");
                printf("\n 3. Total number of external nodes: ");
                printf("\n 4. Total number of internal nodes: ");
                printf("\n 5. Mirror image of the tree: ");
                printf("\n 6. Clone the tree: ");
                printf("\n 7. Exit. ");
                printf("\n\n Enter your choice : ");
                scanf("%d", &choice);
                switch(choice) {
                case 1: printf("\n Enter the value of the new node : ");
                        scanf("%d", &val);
                        tree = insert(tree, val);
                        break;
                case 2: printf("\n Total no. of nodes = %d", totalNodes(tree));
                        break;
                case 3: printf("\n Total no. of external nodes = %d",
                               totalExternalNodes(tree));
                        break;
                case 4: printf("\n Total no. of internal nodes = %d",
                               totalInternalNodes(tree));
                        break;
                case 5: tree = mirror(tree);
                        break;
                case 6: tree=clone(tree);
                        break;
                }
        } while(choice!=7);
        return 0;
}

/*
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 1
   Enter the value of the new node : 5
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 1
   Enter the value of the new node : 6
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 1
   Enter the value of the new node : 7
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 1
   Enter the value of the new node : 8
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 1
   Enter the value of the new node : 9
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 2
   Total no. of nodes = 5
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 3
   Total no. of external nodes = 1
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 4
   Total no. of internal nodes = 4
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 5
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 6
   1. Insert:
   2. Total number of nodes:
   3. Total number of external nodes:
   4. Total number of internal nodes:
   5. Mirror image of the tree:
   6. Clone the tree:
   7. Exit.
   Enter your choice : 7
 */
