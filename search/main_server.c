//  main.c
//  servidor
#include "srv_aux.h"

#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

int criar_socket_servidor_inet_sock_stream(int the_port);
void atende_pedido(int);

void sigalrm_handler(int signum)
{
	printf("timeout!\n");
}

int main(int argc, const char * argv[])
{
	int ns, s;
	unsigned int the_client_length;
	struct sockaddr_in the_client_addr;

	// input arguments
	if (argc != 2)
	{
		printf("utilizacao do programa: %s numero_porta\n", argv[0]);
		exit(1);
	}

	// simplified software signal facilities
	signal(SIGPIPE, SIG_IGN);

	// needed to accept SIGALRM from func alarm
	struct sigaction act;
	act.sa_handler = sigalrm_handler;
	act.sa_flags = 0;
	sigemptyset(&(act.sa_mask));
	sigaction(SIGALRM, &act, NULL);

	s = criar_socket_servidor_inet_sock_stream(atoi(argv[1]));

	while(1)
	{
		printf("a aguardar ligacao:\n");
		the_client_length = sizeof(the_client_addr);

		// accept connection
		ns = accept(s, (struct sockaddr *) &the_client_addr, &the_client_length);

		if (ns == -1)
		{
			perror("erro accept");
			sleep(1);
			continue;
		}

		// ip and port
		printf("ligacao, ip: %s, porta: %d\n", inet_ntoa(*((struct in_addr *) &(the_client_addr.sin_addr))), ntohs(the_client_addr.sin_port));

		atende_pedido(ns);
	}

	return 0;
}

void atende_pedido(int ns)
{
	// stream open function
	FILE *the_fp = fdopen(ns, "r+");

	if (the_fp == NULL)
	{
		perror("erro na abertura");
		close(ns);

		return;
	}

	// get next character or word from input stream
	char the_user_option = fgetc(the_fp);

	printf("operacao: %c\n", the_user_option);

	switch(the_user_option)
	{
		case '1':
			// server add record requested by the client
			srv_adicionarRegisto(the_fp);
		break;

		case '2':
			// server outputs records requested by client
			srv_listarRegistos(the_fp);
		break;

		case '3':
			// server delete record requested by the client
			srv_eliminarRegisto(the_fp);
		break;

		default:
			// invalid option
			printf("opcao invalida\n");
		break;
	}

	// close a stream
	fclose(the_fp);
}

int criar_socket_servidor_inet_sock_stream(int the_port)
{
	int the_socket_ref;
	struct sockaddr_in the_serv_addr;

	// create an endpoint for communication
	the_socket_ref = socket(PF_INET, SOCK_STREAM, 0);

	if (the_socket_ref == -1)
	{
		perror("erro no socket");
		exit(1);
	}

	// fill a byte string with a byte value
	memset(&the_serv_addr, 0, sizeof(the_serv_addr));
	the_serv_addr.sin_family = AF_INET;
	the_serv_addr.sin_addr.s_addr = INADDR_ANY;
	the_serv_addr.sin_port = htons(the_port);

	if (bind(the_socket_ref, (struct sockaddr *)&the_serv_addr, sizeof(the_serv_addr)) < 0)
	{
		perror("erro na atrib");
		exit(1);
	}

	// listen for connections on a socket
	listen(the_socket_ref, 5);

	// the return value is a descriptor referencing the socket
	return(the_socket_ref);
}
