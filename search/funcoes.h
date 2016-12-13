//  funcoes.h
//  cliente
#ifndef HEADER
#define HEADER

#define NAME_BUFFER_SIZE 80

typedef struct
{
	char matricula[6];
	char proprietario[NAME_BUFFER_SIZE];
	char apagado; // 0: record not deleted
} veiculo_t;

void ler_registo(veiculo_t *v);
void imprimir_registo(veiculo_t *v);

#endif //HEADER
