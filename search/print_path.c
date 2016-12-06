void printPath2(Node * node, int path[], int pathLen){

        int i;
        if(!node)
            return;

        path[pathLen]  = node->value;

        int isLeaf = node->left == NULL && node->right == NULL;
        if(isLeaf ){
                 for(i=0; i<=pathLen; i++)
                         printf("%d, ", path[i]);

                 printf("\n");
         }

        printPath2(node->left, path, pathLen+1);
        printPath2(node->right, path, pathLen+1);
        return ;
}
