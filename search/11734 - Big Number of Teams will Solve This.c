#include <stdio.h>
#include <string.h>
#define MAX 100
 
void clone(char noSpace[],char input[]){
    int i=0;
    int k=0;
    while(input[i]!='\0'){
        if(input[i]!=' '){
            noSpace[k]=input[i];
            k++;
        }
        i++;
    }
    noSpace[k]='\0';
}
int main(){
    char input[MAX];
    char output[MAX];
    char noSpace[MAX];
    int t=0;
    int i;
    char space;
    scanf("%d%c",&t,&space);
    for(i=1;i<=t;i++){
        gets(input);
        gets(output);
        clone(noSpace,input);
        if((strlen(input)==strlen(output)) && strcmp(input,output)==0)
            printf("Case %d: Yes\n",i);
        else if(strcmp(noSpace,output)==0)
            printf("Case %d: Output Format Error\n",i);
        else
            printf("Case %d: Wrong Answer\n",i);
    }
 
    return 0;
}
