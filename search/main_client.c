// apple xcode
// paulogp
// cliente envia uma série de comandos para o servidor
// main.c
// cliente
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

// stream read/write
FILE *ligar_ao_servidor(struct hostent *the_host_info, int the_port)
{
	struct sockaddr_in the_client_addr;
	int the_socket_ref;
	FILE *the_fp;

	// create an endpoint for communication
	the_socket_ref = socket(PF_INET, SOCK_STREAM, 0);

	if (the_socket_ref == -1)
	{
		perror("erro no socket");
		return NULL;
	}

	// fill a byte string with a byte value
	memset(&the_client_addr, 0, sizeof(the_client_addr));
	the_client_addr.sin_family = AF_INET;
	the_client_addr.sin_addr = *((struct in_addr *) the_host_info->h_addr);
	the_client_addr.sin_port = htons(the_port);

	if (connect(the_socket_ref, (struct sockaddr *) &the_client_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("erro na ligacao");
		return NULL;
	}

	// stream open function
	the_fp = fdopen(the_socket_ref, "r+");
	if (the_fp == NULL)
	{
		close(the_socket_ref);
	}

	// return stream
	return the_fp;
}

int main(int argc, const char * argv[])
{
	veiculo_t v1;

	int the_port;
	struct hostent* the_host_info;
	char the_user_option;
	char the_buffer[100];
	char *the_flag;
	FILE *the_fp;

	// input arguments
	if (argc != 3)
	{
		printf("utilizacao do programa: %s ip_servidor numero_porta\n", argv[0]);
		exit(1);
	}

	// do it only once
	// get network host entry
	the_host_info = gethostbyname(argv[1]);
	// convert ASCII string to integer
	the_port = atoi(argv[2]);

	do
	{
		printf("1: inserir registo\n");
		printf("2: imprimir registos\n");
		printf("3: apagar registo\n\n");
		printf("4: sair\n");

		// user option
		// get a line from a stream
		fgets(the_buffer, sizeof(the_buffer), stdin);
		// input format conversion
		sscanf(the_buffer, "%c", &the_user_option);

		switch (the_user_option)
		{
			case '1':
				// insert record
				ler_registo(&v1);

				// output record
				imprimir_registo(&v1);

				// connect to server
				the_fp = ligar_ao_servidor(the_host_info, the_port);

				if (the_fp == NULL)
				{
					printf("erro na ligacao.");
					return -1;
				}

				// send user option
				fputc('1', the_fp);

				// send proprietario
				// binary stream input/output
				fwrite(v1.proprietario, sizeof(char), strlen(v1.proprietario), the_fp);

				// send delimeter
				fputc('\n', the_fp);

				// send matricula
				fwrite(v1.matricula, sizeof(char), 6, the_fp);

				// close a stream
				fclose(the_fp);
			break;

			case '2':
				// output all records
				the_fp = ligar_ao_servidor(the_host_info, the_port);

				if (the_fp == NULL)
				{
					printf("erro na ligacao.");
					return -1;
				}

				// send user option
				fputc('2', the_fp);

				// read data
				while (fgets(the_buffer, sizeof(the_buffer), the_fp) != NULL)
				{
					// read proprietario
					strcpy(v1.proprietario, the_buffer);
					the_flag = strchr(v1.proprietario, '\n');

					*the_flag = '\0';

					// read matricula
					fread (v1.matricula, sizeof(char), 6, the_fp);

					v1.apagado = '\0';

					imprimir_registo(&v1);
				}

				// close a stream
				fclose (the_fp);
			break;

			case '3':
				// delete record
				printf("matricula a eliminar: ");
				fgets(the_buffer, sizeof(the_buffer), stdin);

				the_fp = ligar_ao_servidor(the_host_info, the_port);

				if (the_fp == NULL)
				{
					printf("erro na ligacao.");
					return -1;
				}

				// send user option
				fputc('3', the_fp);

				// send matricula
				fwrite(the_buffer, sizeof(char), 6, the_fp);

				// close a stream
				fclose(the_fp);
			break;
		}
	// do it until user press 4
	} while (the_user_option != '4');

	return 0;
}
