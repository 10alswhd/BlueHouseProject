#define BLACK 0
#define RED   1

typedef struct tree_el{
  int value;
  struct tree_el *left;
  struct tree_el *right;
  int color;
} node;

node *root=NULL;

node *insert(node **tree, int value) {
  node *temp;
  temp = (node *)malloc(sizeof(node));
  temp->value = value;
  temp->left = NULL;
  temp->right = NULL;
  temp->color = RED;
	if (*tree == NULL){
    temp->color = BLACK;
		*tree = temp;
    return *tree;
	}
  
  if (temp->value <= (*tree)->value)
    insert(&(*tree)->left,value);
  else if (temp->value >= (*tree)->value)
    insert(&(*tree)->right,value);
}

void delete(node** wezel) {
    node *stary = *wezel;
    if ((*wezel)->left == NULL) {
        *wezel = (*wezel)->right;
        free(stary);
    } else if ((*wezel)->right == NULL) {
        *wezel = (*wezel)->left;
        free(stary);
    } else {
        node** parent = &(*wezel)->left;
        while ((*parent)->right != NULL) {
          parent = &(*parent)->right;
        }
        int temp = (*parent)->value;
        (*parent)->value = (*wezel)->value;
        (*wezel)->value = temp;

        delete(parent);
    }
}

node** search(node** root, int value) {
    node** wezel = root;
    while (*wezel != NULL) {
        if (value < (*wezel)->value)
            wezel = &(*wezel)->left;
        else if (value > (*wezel)->value)
            wezel = &(*wezel)->right;
        else
            break;
    }
    return wezel;
}
