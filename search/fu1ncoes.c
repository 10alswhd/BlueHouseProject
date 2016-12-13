//  funcoes.c
//  cliente
#include "funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read record
void ler_registo(veiculo_t *v)
{
	char the_buffer[81];
	char *the_temp;

	// ini
	v->apagado = '\0';

	// read proprietario
	printf("proprietario: ");
	// get a line from a stream
	fgets(the_buffer, sizeof(the_buffer), stdin);

	// remove char '\n'
	// locate character in string
	the_temp = strchr(the_buffer, '\n');

	if (the_temp != NULL)
	{
		*the_temp = '\0';
	}

	// copy strings
	strcpy(v->proprietario, the_buffer);

	// read matricula
	printf("matricula: ");
	// get a line from a stream
	fgets(the_buffer, sizeof(the_buffer), stdin);

	// copy only 6 chars
	// copy memory area
	memcpy(v->matricula, the_buffer, sizeof(v->matricula));
}

// print record
void imprimir_registo(veiculo_t *v)
{
	// 0: if record deleted: ignored
	if (v->apagado == '\0')
	{
		int i;
		char the_aux[7];

		// copy matricula to the_aux[] as string
		for (i = 0; i < 6; i++)
			the_aux[i] = v->matricula[i];

		the_aux[i] = '\0';

		printf("proprietario: %-10s com matricula: %s apagada: %d\n", v->proprietario, the_aux, v->apagado);
	}
}
