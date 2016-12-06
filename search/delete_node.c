void delete_node(Node *root, int K, Node *parent){
    if(!root)
        return ;

    if(root->value == K){
    //Case 1. If the node is leaf node
        if(!root->left && !root->right){
            if(parent && parent->left == root){
               parent->left = NULL;
            }
            if(parent && parent->right == root){
                parent->right = NULL;
            }
            free(root);
            return;
        }
     //Case 2. If there is right sub tree
        if(root->right){
            Node * temp = 
            inorder_success_mod(root, root->value);           
            if(temp){
                root->value = temp->value;
                free(temp);
            }
            return;
        }
        if(root->left){
            if(parent && parent->left == root){
               parent->left = root->left;                    
            }
            if(parent && parent->right == root){
                parent->right = root->left;
            }

            free(root);
            return;
        } 
    }
    if(root->value > K){
        delete_node(root->left, K, root);
    }
    else{
        delete_node(root->right, K, root);
    }
    return ;
}

Node *inorder_success_mod(Node *root, int K){

    Node * successor = NULL;
    Node *current  = root;
    Node *prev  = NULL;
    if(!root)
        return NULL;

    while(current->value != K){
        if(current->value >K){
            successor = current;
            prev = current;
            current= current->left;
    }
    else{
        prev = current;
        current = current->right;
        }
    }
    if(current && current->right){
        successor = find_minimum_mod(current->right, &prev);
    }
    if(prev && prev->right  == successor)
        prev->right = NULL;
    else if(prev && prev->left == successor)
        prev->left = NULL;

    return successor;
}

Node * find_minimum(Node *root){
    if(!root)
        return NULL;

    while(root->left){
        root = root->left;
    }
    return root;
}
