//  srv_aux.h
//  servidor
#ifndef INCLUDE_SRV_AUX_H
#define INCLUDE_SRV_AUX_H

#define NAME_BUFFER_SIZE 80

#include <stdio.h>

typedef struct
{
	char matricula[6];
	char proprietario[NAME_BUFFER_SIZE];
	char apagado; // 0: record not deleted
} veiculo_t;

void srv_adicionarRegisto(FILE *the_fp);
void srv_listarRegistos(FILE *the_fp);
void srv_eliminarRegisto (FILE *the_fp);
void imprimir_registo(veiculo_t *v);

#endif
