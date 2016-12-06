#include <stdio.h>
#include <stdlib.h>

typedef int data;

typedef struct arv {
  struct arv *left;
  struct arv *right;
  data value;
} Arvore;

//Inicializando
void initialize(Arvore **arv) {
  *arv = NULL;
}

//Verificando se ela está vazia
int empty(Arvore *arv) {
  return (arv == NULL);
}

//Funcao de busca
Arvore* search(Arvore *arv, data d) {
  if (arv == NULL) return NULL;
  if (arv->value == d) return arv;

  if (arv->value > d) {
    return search(arv->left, d);
  } else {
    return search(arv->right, d);
  }
}

//Funcao para inserir
int insert(Arvore **arv, data d) {

  if (*arv == NULL) {
    *arv = (Arvore*)malloc(sizeof(Arvore));
    (*arv)->left = (*arv)->right = NULL;
    (*arv)->value = d;
    return 1;
  }

  if ((*arv)->value < d) {
    return insert(&((*arv)->right), d);
  } else {
    if ((*arv)->value > d) {
      return insert(&((*arv)->left), d);
    } else {
      return 0;
    }
  }
}

void show(Arvore *arv) {
  if (arv != NULL) {
    show(arv->left);
    printf("%d-", arv->value);
    show(arv->right);
  }
}

//Removendo um nó especifico
Arvore* remove_node(Arvore *arv, data d) {

  if (arv == NULL) return NULL;
  if (arv->value > d) {
    arv->left = remove_node(arv->left, d);
  } else if (arv->value < d) {
    arv->right = remove_node(arv->right, d);
  } else {
    if (arv->left == NULL && arv->right == NULL) {
      free(arv);
      arv = NULL;
    } else if (arv->left == NULL) {
      // printf("Filho a direita\n");
      Arvore *aux = arv;
      arv = arv->right;
      free(aux);
    } else if (arv->right == NULL) {
      Arvore *aux = arv;
      arv = arv->left;
      free(aux);
    } else {
      Arvore *aux = arv->left;

      while(aux->right != NULL) {
        aux = aux->right;
      }

      // printf("[%d]\n", aux->value);
      arv->value = aux->value;
      aux->value = d;
      arv->left = remove_node(arv->left, d);
    }
  } 

  return arv;
}

//clear
void clear(Arvore **arv) {
  if (*arv == NULL) return;
    clear(&(*arv)->left);
    clear(&(*arv)->right);
    free(*arv);
    *arv = NULL;
}

int main(void) {

  Arvore *Inicio;
  int option, value;
  Arvore *aux;

  initialize(&Inicio);

  do {

    printf("1 - Inserir.\n");
    printf("2 - Remover.\n");
    printf("3 - Pesquisar.\n");
    printf("4 - Exibir a árvore.\n");
    printf("5 - Esvaziar a árvore.\n");
    printf("0 - Sair.\n");
    printf("Digite a opção: ");
    scanf("%d", &option);

    // Inserindo
    if (option == 1) {
      printf("Digite o valor para inserir: ");
      scanf("%d", &value);
      insert(&Inicio, value); 
      printf("\n\n");
      
    // Removendo
    } else if (option == 2) {
      printf("\n\n");
      printf("Digite o valor a ser removido: ");
      scanf("%d", &value);
      remove_node(Inicio, value);
      printf("\n\n");

    // Procurando algum número na árvore
    } else if (option == 3) {
      printf("\n\n");
      printf("Digite um valor para pesquisar: ");
      scanf("%d", &value);

      aux = search(Inicio, value);
      if (aux == NULL) {
        printf("Valor não encontrado.\n");
      } else {
        printf("Valor encontrado [%d].\n", aux->value);
      }
      printf("\n\n");

    // Exibindo
    } else if (option == 4) {
      printf("\n\n");
      printf("Exibindo arvore!\n");
      show(Inicio);
      printf("\n\n");

    } else if (option == 5) {
      printf("\n\n");
      printf("Linpando a árvore...\n");
      clear(&Inicio);
      printf("\n\n");

    }


  } while (option >= 1);




  return 0;
}
