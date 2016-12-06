#include <stdlib.h>
#include <stdio.h>
#include "arv.h"


void initialize(Arvore **arv) {
  *arv = NULL;
}

int empty(Arvore *arv) {
  return (arv == NULL);
}

// Buscando nó,
// Interessante que retornamos o Nó achado,
// essa função é priomordial para adição de outros nós
Arvore* search_node(Arvore *arv, int valor) {

  Arvore *found;
  if (arv == NULL) return NULL; //Verifica se a arvore está vazia
  if (arv->dado == valor) return arv;

  found = search_node(arv->esquerda, valor);
  if (found == NULL) {
    found = search_node(arv->direita, valor);
  }

  return found;
}

//Inserir um nó raiz
int insert_root(Arvore **arv, int valor) {
  Arvore *new_node;

  //A arvore já tem uma raiz
  if (*arv != NULL) return 0;

  new_node = (Arvore*)malloc(sizeof(Arvore));
  if (new_node == NULL) return 0; //Sem memoria para alocar a estrutura
  new_node->dado = valor;
  new_node->esquerda = new_node->direita = NULL;
  *arv = new_node;
  return 1; 
}

//Inserir nós!
int insert_right(Arvore *arv, int ascendente, int valor) {

  Arvore *new_node, *child, *dad;

  child = search_node(arv, valor);
  if (child != NULL) return 0; //Já existe um nó com esse valor

  dad = search_node(arv, ascendente);
  if (dad == NULL) return 0; //Não tem o pai procurado
  if (dad->direita != NULL) return 0; //Já temos um filho a direita

  new_node = (Arvore*)malloc(sizeof(Arvore));
  new_node->dado = valor;
  new_node->esquerda = new_node->direita = NULL;
  dad->direita = new_node;


  return 1;
}

int insert_left(Arvore *arv, int ascendente, int valor) {
  Arvore *new_node, *child, *dad;

  child = search_node(arv, valor);
  if (child != NULL) return 0;

  dad = search_node(arv, ascendente);
  if (dad == NULL) return 0;
  if (dad->esquerda != NULL) return 0; //Já existe nós a esquerda

  new_node = (Arvore*)malloc(sizeof(Arvore));
  new_node->dado = valor;
  new_node->esquerda = new_node->direita = NULL;
  dad->esquerda = new_node;

  return 1;
}


int clear_tree(Arvore **arv) {
  if (*arv == NULL) return 1;

  clear_tree(&(*arv)->esquerda);
  clear_tree(&(*arv)->direita);
  free(*arv);
  *arv = NULL;
  return 1;

}


//Obtento o filho esquerdo de um nó (exercício)
Arvore* left_child(Arvore *arv, int valor) {

  Arvore *found;

  found = search_node(arv, valor);
  if (found == NULL) return NULL;
  if (found->esquerda == NULL) return NULL;

  return found->esquerda;

}

//Obtento o filho da direita
Arvore* right_child(Arvore *arv, int valor) {

  Arvore *found;

  found = search_node(arv, valor);
  if (found == NULL) return NULL;
  if (found->direita == NULL) return NULL;

  return found->direita;
}

//Buscando um elemento na Arvore
int search_value(Arvore *arv, int valor) {

  Arvore *found = search_node(arv, valor);

  if (found == NULL) return -1;
  return found->dado;
}

//Obtendo O pai de um elemento

Arvore* pai(Arvore *anterior, Arvore *root, int valor) {

  //Passamos dois argumentos para função (o anterior e o proximo)
  //primeiro procuramos pelo valor, se o valor existir, continuamos, se não
  //retornamos nullo
  //Depois verificamos se a raiz que temos agora tem o dado que procuramos
  //Se tiver, retornamos o ANTERIOR (quem estamos buscando);
  //O anterior sempre vai ser o root na proxima
  //OU seja, quando chamamos o pai(), colocamos o anterior com o atual
  //e vamos buscando os filhos dele tanto na esquerda, quanto na direita
  //quando encontrarmos, retornamos o encontrado;
  Arvore *found;

  found = search_node(root, valor);
  if (found == NULL) return NULL;
  if (root->dado == valor) return anterior;

  found = pai(root, root->esquerda, valor);
  if (found == NULL) {
    found = pai(root, root->direita, valor);
  }

  return found;

}

// int clear_tree(Arvore **arv) {
//   if (*arv == NULL) return 1;

//   clear_tree(&(*arv)->esquerda);
//   clear_tree(&(*arv)->direita);
//   free(*arv);
//   *arv = NULL;
//   return 1;

// }

//Excluir um nó
int delet_node(Arvore *arv, int valor) {

  Arvore *found, *dad;
  found = search_node(arv, valor);
  dad = pai(NULL, arv, valor);

  if (found == NULL) return 0;
  if (dad == NULL) return 0;

  //Removendo
  if (dad->esquerda == found) {
    clear_tree(&found);
    if (found == NULL) {
      dad->esquerda = NULL;
    }
  } 

  if (dad->direita == found) {
    clear_tree(&found);
    if (found == NULL) {
      dad->direita = NULL;
    }
  } 

  return 1;
}
