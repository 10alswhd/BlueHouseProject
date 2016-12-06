#include <stdio.h>

typedef struct node {
  struct node * prev;
  struct node * next;
  int val;
} node_t;

typedef struct head {
  node_t *first;
} head_t;

void start_list(head_t *linked_list);
int show_list(head_t *linked_list);
void add_node(head_t *linked_list, int value);
void search_node(head_t *linked_list, int value);
int remove_last_node(head_t *linked_list);

int main(void) {

  head_t *linked_list = malloc(sizeof(head_t));
  start_list(linked_list);
  printf("Iniciando lista: %d\n", linked_list->first);
  add_node(linked_list, 50);
  add_node(linked_list, 1);
  add_node(linked_list, 3);
  add_node(linked_list, 5);
  show_list(linked_list);
  remove_last_node(linked_list);
  remove_last_node(linked_list);
  remove_last_node(linked_list);
  remove_last_node(linked_list);

  show_list(linked_list);
  //search_node(linked_list, 3);



  return 0;
}

//Iniciando a lista
void start_list(head_t *linked_list) {
  printf("Inicializando a lista\n");
  linked_list->first = NULL;
}

//Adicionando um nó
void add_node(head_t *linked_list, int value) {
  node_t *node = malloc(sizeof(node_t));
  node_t *new_node = malloc(sizeof(node_t));

  int node_address = 0;

  if (node == NULL) {
    printf("Out of memory, exiting.\n");
  }

  //A adição de mais nós irá adicionar sempre no final
  //prev<-[NO]->next, iremos até o ultimo nó,
  //guardaremos o valor do endereço dele e colocaremos
  //no prev do próximo nó.

  //A lista está vazia? Se sim, adicionamos o primeiro nó.
  if (linked_list->first == NULL) {
    linked_list->first = node;
    node->prev = NULL;
    node->next = NULL;
    node->val = value;
  } else {
    //Se a lista não estiver vazia, o nó será o primeiro da lista.
    node = linked_list->first;

    while(node->next != NULL) {
      node = node->next;
    }
    node->next = new_node;
    new_node->prev = node;
    new_node->next = NULL;
    new_node->val = value;
  }

}

int show_list(head_t *linked_list) {
  if (linked_list->first == NULL) {
    printf("Lista vazia!\n");
    return 0;
  }

  node_t *current = malloc(sizeof(node_t));
  current = linked_list->first;
  int i = 0;

  while(current->next != NULL) {
    printf("Valor do nó [%d] = [%d]\n", i, current->val);
    current = current->next;
    i++;
    //printf("Meu endereço[%d], endereço anterior[%d], proximo:[%d].\n", current, current->prev, current->next);
  }
  if (current->next == NULL) {
    printf("Valor do nó [%d] = [%d]\n", i, current->val);
    //printf("Meu endereço[%d], endereço anterior[%d], proximo:[%d].\n", current, current->prev, current->next);
  }

  return 0;
}

void search_node(head_t *linked_list, int value) {
  node_t *current = malloc(sizeof(node_t));
  current = linked_list->first;
  int i = 0;

  while(current->next != NULL) {
    if (current->val == value) {
      printf("Achei o valor pedido = [%d] no indice: [%d].\n", value, i);
    }
    current = current->next;
    i++;

  }

  if (current->next == NULL) {
    if (current->val == value) {
      printf("Achei o valor pedido = [%d] no indice: [%d].\n", value, i);
    }
  }

}

int remove_last_node(head_t *linked_list) {

  if (linked_list->first == NULL) {
    printf("A lista está vazia!\n");
    return 1;
  }
  node_t *current = malloc(sizeof(node_t));
  node_t *previous = malloc(sizeof(node_t));
  current = linked_list->first;

  //Se a lista não está vazia e só tem um elemento;
  if (current->next == NULL && linked_list->first != NULL) {
    free(current);
    linked_list->first = NULL;
  }

  //Entrando na lista e movendo-se até o ultimo elemento.
  while(current->next != NULL) {
    current = current->next;
  }

  // Removendo o ultimo elemento da lista, quando a lista tem
  // mais de um elemento.
  if (current->next == NULL && linked_list->first != NULL) {
    previous = current->prev;
    previous->next = NULL;
    free(current);
  }

  return 0;
}
