void Remove(int key, Tree *MyTree) {
    if (*MyTree == NULL) {
        printf("Not found.\n");
    } else if ((*MyTree)->REG.number > key) {
        Remove(key, &(*MyTree)->left);
    } else if ((*MyTree)->REG.number < key) {
        Remove(key, &(*MyTree)->right);
    } else {
        if ((*MyTree)->right == NULL && (*MyTree)->left == NULL) {
            printf("%d deleted.\n", (*MyTree)->REG.number);
            Pnodo pAux = *MyTree;
            free(pAux);
            *MyTree = NULL;
        } else if ((*MyTree)->left == NULL) {
            printf("%d deleted.\n", (*MyTree)->REG.number);
            Pnodo pAux = *MyTree;
            free(pAux);
            *MyTree = (*MyTree)->right;
        } else if ((*MyTree)->right == NULL) {
            printf("%d deleted.\n", (*MyTree)->REG.number);
            Pnodo pAux = *MyTree;
            free(pAux);
            *MyTree = (*MyTree)->left;
        } else {

            while ((*MyTree)->right != NULL) {
                (*MyTree) = (*MyTree)->right;
            }

            Pnodo pAux = (*MyTree);
            Remove(key, &(*MyTree)->left);
        }
    }
}
