void print_k_nodes(Node * node, int *K){

        if(node == NULL || (*K) == 0) return;

        print_k_nodes(node->right, K);
        printf("\n");
        printf("%d", node->value);
        (*K)--;
        print_k_nodes(node->left, K);
}
