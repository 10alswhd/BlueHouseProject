//  srv_aux.c
//  servidor
#include "srv_aux.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "dados.dat"

void srv_adicionarRegisto(FILE *the_fp)
{
	char the_buffer[100];
	char *the_search;

	// binary stream input
	fread(the_buffer, sizeof(char), sizeof(the_buffer), the_fp);

	// search for delimiter
	// locate character in string
	the_search = strchr(the_buffer, '\n');
	*the_search = '\0';

	veiculo_t registo;

	// copy memory area
	memcpy(registo.proprietario, the_buffer, the_search + 1 - the_buffer);

	the_search++;
	// copy memory area
	memcpy(registo.matricula, the_search, 6);

	// insert record into file
	// stream open function: file
	FILE *the_file = fopen(FILE_NAME, "a");

	if (the_file != NULL)
	{
		// binary stream input/output: file
		fwrite(&registo, sizeof(veiculo_t), 1, the_file);

		imprimir_registo(&registo);

		// close a stream: file
		fclose (the_file);
	}
}

// output records
void srv_listarRegistos(FILE *the_fp)
{
	// stream open function: file
	FILE *the_file = fopen(FILE_NAME, "r");

	if (the_file == NULL)
	{
		printf("erro na abertura do ficheiro\n");
		return;
	}

	veiculo_t v1;

	// fread: binary stream input
	while (fread(&v1, sizeof(veiculo_t), 1, the_file) != 0)
	{
		// if record not deleted
		if (v1.apagado == 0)
		{
			// write proprietario to file
			fwrite(v1.proprietario, sizeof (char), strlen(v1.proprietario), the_fp);

			// displays proprietario
			puts(v1.proprietario);

			// write delimeter to file
			fputc('\n', the_fp);

			// write matricula to file
			fwrite(v1.matricula, sizeof (char), 6, the_fp);
		}
	}

	// close a stream: file
	fclose (the_file);
}

void srv_eliminarRegisto(FILE *the_fp)
{
	// stream open function: file
	FILE *the_file = fopen(FILE_NAME, "r+");

	if (the_file == NULL)
	{
		printf("erro na abertura do ficheiro\n");
		return;
	}

	veiculo_t veiculo;
	char the_file_value[7];
	char the_comp_value[20];
	int the_num_of_elements = 0;

	// from socket
	// binary stream input
	fread(the_comp_value, sizeof(char), sizeof(the_comp_value), the_fp);
	the_comp_value[6] = '\0';

	while (fread(&veiculo, sizeof(veiculo_t), 1, the_file) != 0)
	{
		// get right position
		the_num_of_elements++;

		// matricula to string
		// copy memory area
		memcpy(the_file_value, veiculo.matricula, 6);
		the_file_value[6] = '\0';

		// if matricula exits, set record matricula to apagado = 1
		// compare strings
		if (strcmp(the_comp_value, the_file_value) == 0)
		{
			// delete record
			veiculo.apagado = '1';

			// point to right position
			// reposition a stream
			fseek(the_file, (the_num_of_elements - 1) * sizeof(veiculo_t), SEEK_SET);

			// write it back
			fwrite(&veiculo, sizeof(veiculo_t), 1, the_file);

			break;
		}
	}

	// close a stream: file
	fclose(the_file);
}

// print record
void imprimir_registo(veiculo_t *v)
{
	// 0: if record deleted: ignored
	if (v->apagado == '\0')
	{
		int i;
		char the_aux[7];

		// copy matricula to the_temp[] as string
		for (i = 0; i < 6; i++)
		{
			the_aux[i] = v->matricula[i];
		}

		the_aux[i] = '\0';
		printf("proprietario: %-10s com matricula: %s apagada: %d\n", v->proprietario, the_aux, v->apagado);
	}
}
