#include <stdio.h>

typedef struct head {
  int * first;
  int * last;
  int count;
} head_t;

typedef struct node {
  struct node *prev;
  struct node *next;
  int val;
} node_t;

///////////////////////////////
void start_list(head_t *head);
void add_node(head_t *head, int val);
void print_list(head_t *head);
void search_list(head_t *head, int value);

int main(void) {

  head_t *head_list = malloc(sizeof(head_t));
  if (head_list == NULL) {
    return 1; //para o programa
  }

  start_list(head_list);
  printf("Iniciando a Lista, contagem: [%d].\n", head_list->count);
  add_node(head_list, 1);
  add_node(head_list, 5);
  add_node(head_list, 3);
  add_node(head_list, 2);
  printf("Adicionados todos os nós, a contagem agora é de: [%d].\n", head_list->count);
  search_list(head_list, 1);

  // print_list(head_list);

  return 0;
}

// Inicia a lista
void start_list(head_t *head) {
  head->first = NULL;
  head->last = NULL;
  head->count = 0;
}

// Adiciona um nó a lista.
void add_node(head_t *head, int value) {
  node_t *node = malloc(sizeof(node_t));
  if (head->first == NULL && head->last == NULL) {
    head->first = head->last = node;
    head->count++;
    node->val = value;
  } else {
    node->next = head->first;
    node->prev = NULL;
    head->first = node;
    head->count++;
    node->val = value;
  }

}

// Imprimindo toda a lista
void print_list(head_t *head) {
  printf("Imprimindo a LISTA.\n");
  node_t *current = malloc(sizeof(node_t));

  current = head->first;

  while(current->next != NULL) {
    printf("Valor = [%d].\n", current->val);
    current = current->next;
  }
  if (head->count > 1) {
    printf("Valor = [%d] (ultimo).\n", current->val);
  }

}

// Procurando na lista um elemento.
void search_list(head_t *head, int value) {
  // printf("Consultando o valor: [%d] na lista.\n", value);

  node_t *current = malloc(sizeof(node_t));
  current = head->first;
  int i = 1;

  // while(current->next != NULL) {
  //   if (current->val == value) {
  //     printf("Encontrado o elemento [%d] na posição [%d].\n", current->val, i);
  //   }
  //   current = current->next;
  //   i++;
  // }

  for (i = 0; i < head->count;i++) {
    if (current->val == value) {
      printf("Encontrado o elemento [%d] na posição [%d].\n", current->val, i+1);
    }
    current = current->next;
  }
}
