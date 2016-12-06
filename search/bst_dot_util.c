void
bst_print_dot_null(char *name, int nullcount, FILE* stream)
{
    fprintf(stream, "\tnull%d [shape=point];\n", nullcount);
    fprintf(stream, "\t\"%s\" -> null%d;\n", name, nullcount);
}

void
bst_print_dot_aux(struct BSTnode *node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "\t\"%s\" -> \"%s\";\n",
        	node->name,
        	node->left->name);
        bst_print_dot_aux(node->left, stream);
    } else {
        bst_print_dot_null(node->name, nullcount++, stream);
    }
    if (node->right) {
        fprintf(stream, "\t\"%s\" -> \"%s\";\n",
        	node->name,
        	node->right->name);
        bst_print_dot_aux(node->right, stream);
    } else {
        bst_print_dot_null(node->name, nullcount++, stream);
	}
}

void
bst_print_dot(struct BSTnode *tree, FILE *stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "\tnode [fontname=\"Arial\"];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "\t\"%s\";\n", tree->name);
    else
        bst_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

/* Usage */
bst_print_dot(treeroot, stdout);
