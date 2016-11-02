int search(trie *t, char key[]){
        int len = strlen(key);
        int i;
        if(t->root == NULL){
                printf("\n Trie is not initialized\n");
        }

        Node * current = t->root;
        for(i=0; i<len; i++){
                int index  =  GET_CHAR_INDEX(key[i]);

                /* If characters are left in key and we have reached at       
                NULL, there is no key present */
                if(current->children[index] == NULL) return false;
                 
                /* Else traverse down the trie */
                current = current->children[index];
        }

        /* If we have reached the lead=f node, key is present */
        if(current && current->value == LEAF_NODE )
                return true;

        return false;
}
