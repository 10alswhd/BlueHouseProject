#include <stdlib.h>
#include <stdio.h>
#define MAX 100000

int main (){
   char str[MAX];
   int word,flat,i;
   while(gets(str)){
        word = 0;
        flat = 1;
        i=0;
        while(str[i]!='\0'){
            if( (str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') ){
                if(flat)
                    word++;
                flat=0;
            }
            else
                flat=1;
            i++;
        }
        printf("%d\n",word);
   }
   return 0;
}
