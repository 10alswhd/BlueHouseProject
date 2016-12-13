/*
* @Author: reinaldo
* @Date:   2014-10-01 19:37:25
* @Last Modified by:   reinaldo
* @Last Modified time: 2014-10-01 20:05:33
*/

#include <stdio.h>

#define TAM 10

#define EMPTY -1

/**
 * Array global
 */
int array[TAM];

/**
 * Reseta o vetor
 */
void reset() {
    int i;

    for (i = 0; i < TAM; i++)
        array[i] = EMPTY;
}

/**
 * Gera o valor hash de um valor
 * @param  val Valor a ser inserido/buscado
 * @return     chave no vetor
 */
int hash(int val) {

    return val % TAM;

}

/**
 * Gera o rehash para caso de colisão
 * @param  oldKey chave anterior
 * @return        nova chave
 */
int reHash(int oldKey) {

    return (oldKey + 1) % TAM;

}

/**
 * Função para inserir na tabela hash
 * @param val valor a ser inserido
 */
void insert(int val) {

    int hash = hash(val), count = 0;

    if(array[hash] == EMPTY) {
        while(array[hash = reHash(hash)] != EMPTY && count++ < TAM);

        if(count == TAM - 1) {
            puts("Erro de implementação, tabela hash estourou");
            return;
        }

        array[hash] = val;
    } else
        array[hash] = val;

}

/**
 * Função de busca na tabela hash
 * @param  val Valor para buscar na tabela hash
 * @return     índice no vetor
 */
int search(int val) {

    int hash = hash(val), count = 0;

    if(array[hash] == val)
        return hash;
    else {
        while(array[hash = reHash(hash)] != val && (count++ < TAM || array[hash] != EMPTY));

        if(count == TAM - 1 || array[hash] == TAM) {
            puts("Achou");
            return hash;
        }

    }

}

/**
 * main function
 * @return SUCCESS
 */
int main() {

    int i;

    reset();

    srand(time());

    for(i = 0; i < 5; i++)
        insert(rand());




    return 0;
}
