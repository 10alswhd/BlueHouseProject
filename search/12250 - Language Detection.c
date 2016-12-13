#include <stdio.h>
#include <string.h>
#define MAX 1000
 
int main(){
    char S[MAX];
    int i=0;
    while(gets(S) && strcmp(S,"#")!=0){
        i++;
        if(!strcmp(S,"HELLO"))
            printf("Case %d: ENGLISH\n",i);
        else if(!strcmp(S,"HOLA"))
            printf("Case %d: SPANISH\n",i);
        else if(!strcmp(S,"HALLO"))
            printf("Case %d: GERMAN\n",i);
        else if(!strcmp(S,"BONJOUR"))
            printf("Case %d: FRENCH\n",i);
        else if(!strcmp(S,"CIAO"))
            printf("Case %d: ITALIAN\n",i);
        else if(!strcmp(S,"ZDRAVSTVUJTE"))
            printf("Case %d: RUSSIAN\n",i);
        else
            printf("Case %d: UNKNOWN\n",i);
    }
    return 0;
}
