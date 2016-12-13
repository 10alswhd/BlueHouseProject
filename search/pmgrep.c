#include <stdio.h>
#define MAXLINE 1000 // maximum input line length

int getlinea(char line[], int max);
int strindex(char source[], char searchfor[]);
char patron[] = "apple"; // patron to search for

// find all lines matching patron
main() {
  char line[MAXLINE]; // usado para la linea actual
  int found = 0; // cantidad de concidiencias

  while (getlinea(line, MAXLINE) > 0) { // mientras el usuario siga tecleando
    if (strindex(line, patron) >= 0) { // buscamos el patron en la linea ingresada
      printf("%s", line); // si patron esta en linea, la imprimimos
      found++; // y se aumenta el contador en uno
    }
  }

  return found;
}

// retorna el largo de line[] mientras que sea menor a max
int getlinea(char line[], int max) {
  int c, // almacenamos el caracter actual en c
      i; // el largo de linea se almacena en i

  i = 0; // iniciamos el largo en 0

  // mientras que el caracter siguiente no sea EOF o una linea nueva, reducimos
  // el maximo en uno
  while (--max > 0 && (c = getchar()) != EOF && c != '\n') {
    // avanzamos hacia el proximo caracter de line y aumentamos el largo en 1
    line[i++] = c;
  }

  // cuando llegamos al final de la linea
  if (c == '\n') {
    // aumentamos i una ultima vez y almacenamos el fin de linea 
    line[i++] = c;
  }

  line[i] = '\0'; // agregamos null al final

  return i; // retornamos el largo
}

// retorna la cantidad de veces que searchfor[] se encuentra en source[],
// retorna la posicion donde se encuentra y -1 si no se encontro
int strindex(char source[], char searchfor[]) {
  int i, // almacena la posicion dentro de source donde hay un match 
      j, // contador para source
      k; // contador para searchfor

  // recorremos source, mientras que el proximo caracter no sea null
  for (i = 0; source[i] != '\0'; i++) {
    // al encontrar un match parcial seteamos k en 0 y barremos source contra
    // searchfor hasta encontrar un match de 100%
    for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++)
      printf("j = %d | i = %d | k = %d | source: %c | searchfor: %c \n",
              j, i, k, source[j], searchfor[k]);
    // si hay coincidencias y llegamos al final del patron a buscar, salimos 
    if (k > 0 && searchfor[k] == '\0') {
      return i;
    }
  }

  // catch-all, si llegamos aca es porque no hay coincidencias
  return -1;
}
