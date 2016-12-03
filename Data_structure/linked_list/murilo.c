#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Arv {
    int index;
    int number_of_sons;

    struct Arv** sons;
    struct Arv* next;
} node;

typedef node* p_node;

void printer(p_node root){
    if(root == NULL)
        return;

    printf("(%d", root->index);

    int i;
    for(i=0; i < root->number_of_sons; i++){
        printer(root->sons[i]);
    }

    printf(")");
}

p_node alocator(){
    /* Alocate an empy node */

    p_node new_node = malloc(sizeof(node));

    new_node->sons = NULL;
    new_node->next = NULL;

    new_node->index = -1;
    new_node->number_of_sons = 0;

    return new_node;
}

p_node search(p_node root, int index){
    p_node search_result = NULL;

    if(root == NULL)
        return NULL;

    if(root->index == index)
        return root;

    int i;
    for(i=0; i < root->number_of_sons; i++){
        search_result = search(root->sons[i], index);

        if(search_result != NULL)
            return search_result;
    }

    return NULL;
}

void insert_in_array(int index, p_node root){
    /* like vector.push_back, but way slower */
    
    p_node new_node = alocator();
    new_node->index = index;

    root->sons = realloc(root->sons, sizeof(p_node) * root->number_of_sons + 1);
    root->number_of_sons++;
    root->sons[root->number_of_sons - 1] = new_node;
}

p_node insert(p_node* root, int index, bool flag){
    p_node new_node = NULL;
    p_node search_result = NULL;

    if(root == NULL || (*root) == NULL){
        new_node = alocator();
        new_node->index = index;
        *root = new_node;
        return new_node;
    }

    if(index == (*root)->index){
        return (*root);
    }    

    if(flag){
        insert_in_array(index, *root);
        return (*root);
    }

    int i;
    for(i=0; i < (*root)->number_of_sons; i++){
        search_result = search((*root)->sons[i], index);

        if(search_result != NULL)
            return insert(&search_result, index, false);
    }
}

int main(){
    int kings;
    int relations;

    int current_father;
    int current_son;

    p_node root = NULL;
    p_node search_result = NULL;

    scanf("%d %d", &kings, &relations);

    int i;
    for(i=0; i < relations; i++){
        scanf("%d %d", &current_father, &current_son);
        
        search_result = search(root, current_father);
        if(search_result == NULL){
            search_result = insert(&root, current_father, false);
        }
        insert(&search_result, current_son, true);
    }

    printer(root);

    return 0;
}
