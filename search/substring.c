#include <stdio.h>
#include <stdlib.h>

#define BUFFER 128

void getSubString(char *);
void findSubString(char *subString, char *source);
char *readStdin();

int main(int argc, char *argv[]) {
    char *source;
    
    if(argc != 2) {
       printf("No se encontro al sub-string por buscar.\n"
       "Agregue el sub-string como parametro al programa.\n");
       return 0;
    }

    //get our main text
    source = readStdin();

    //search for subString
    findSubString(argv[1],source);

    if(source) {
        free(source);
    }

    return 0;
}

/*
* Read input from stdin using dynamic memory allocation.
*/
char *readStdin() {
    char *string = NULL;
    int bufferSize = 0;

    for(int i=0;;i++) {
        if(i == bufferSize) {
            char *buffer;
            buffer = realloc(string,BUFFER*(i / BUFFER));
            if(buffer) {
                string = buffer;
                if(string) {
                    free(string);
                }
            } else {
                exit(1);
            }
        }

        string[i] = fgetc(stdin);
       
        if(string[i] == EOF) {
            string[i] = '\0';
            break;
        }
    }

    return string;
}

void findSubString(char *subString, char *source) {
    char *rootSubString = &subString[0];
    int loops = 0;

    //search whole text
    for(int i=1;*source;i++,source++) {
        
        if(!*subString) {
            loops++;
            subString = rootSubString;
        }

        //if two chars are the same
        if(*source == *subString) {
            printf("%c encontrado, pos #%d en el texto.\n",*subString,i);
            subString++;
        }
    }

    if(!loops) 
        printf("No se encontro al substring completo!\n");
    else
        printf("Busqueda finalizado. Se encontro al SubString %d veces.\n", loops);

}
