#include <stdio.h>

int main(){

    int edad;
    char no[]="No puedes entrar";
    char si_1[]="Dirigete al area 1";
    char si_2[]="Dirigete al area 2";
    char si_3[]="Dirigete al area 3 Adultos mayores";

    printf("Registro de Usuarios Bar\n");
    printf("Ingresa tu edad: ");
    scanf("%d", &edad);

    if(edad >= 18){
        if(edad >=18 && edad <=30){
            printf("%s\n",si_1);
        }
        if(edad > 30 && edad <= 60){
            printf("%s\n",si_2);
        }
        if(edad > 60){
            printf("%s\n",si_3);
        }
    }
    else{
        printf("%s\n",no);
    }

    return 0;
}
