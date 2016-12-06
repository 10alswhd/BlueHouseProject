#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _tree_node
{
    int value;
    struct _tree_node *left;
    struct _tree_node *right;
} tree_node;

bool check_bst(tree_node *tree, int min, int max);

bool is_bst(tree_node *tree)
{
    return check_bst(tree, INT_MIN, INT_MAX);
}

bool check_bst(tree_node *tree, int min, int max)
{
    if (!tree)
        return true;

    if (tree->value < min || tree->value > max)
        return false;

    return check_bst(tree->left, min, tree->value) &&
            check_bst(tree->right, tree->value, max);
}

void tree_pre_traverse(tree_node *node)
{
    if (!node)
        return;
    printf("%d ", node->value);
    tree_pre_traverse(node->left);
    tree_pre_traverse(node->right);
}

void tree_in_traverse(tree_node *node)
{
    if (!node)
        return;
    tree_in_traverse(node->left);
    printf("%d ", node->value);
    tree_in_traverse(node->right);
}

void tree_post_traverse(tree_node *node)
{
    if (!node)
        return;
    tree_post_traverse(node->left);
    tree_post_traverse(node->right);
    printf("%d ", node->value);
}

void tree_create(tree_node **node, const char *const values[], int *cursor, int length)
{
    int value;
    if (*cursor >= length)
    {
        *node = NULL;
        return;
    }

    if (values[*cursor] == "#")
    {
        *node = NULL;
        return;
    }

    value = atoi(values[*cursor]);
    *node = malloc(sizeof (**node));
    if (!*node)
    {
        printf("Error: out of memory!\n");
        exit(1);
    }
    (*node)->value = value;
    ++*cursor;
    tree_create(&(*node)->left, values, cursor, length);
    ++*cursor;
    tree_create(&(*node)->right, values, cursor, length);
}

void tree_free(tree_node *tree)
{
    if (!tree)
        return;
    tree_free(tree->left);
    tree_free(tree->right);
    free(tree);
}

int main(void)
{
    tree_node *tree, *pattern;
    int length, cursor;
    const char *const values[] = {"39", "18", "6", "27", "#", "#", "#", "24",
        "#", "#", "25", "23", "#", "#", "50", "#", "#"}; // not a bst.
   //const char *const values[] = {"18", "6", "#", "12", "#", "#", "24", "#", "#"}; // bst.

    cursor = 0;
    length = sizeof (values) / sizeof (values[0]);
    tree_create(&tree, values, &cursor, length);
    printf("Tree:\n");
    printf("Preorder: ");
    tree_pre_traverse(tree);
    printf("\n");
    printf("Inorder: ");
    tree_in_traverse(tree);
    printf("\n");
    printf("Postorder: ");
    tree_post_traverse(tree);
    printf("\n");
    printf("The tree %s a binary search tree.\n", is_bst(tree) ? "IS" : "is NOT");
    tree_free(tree);
    return 0;
}
