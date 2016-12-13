#include <stdio.h>
#include <string.h>
#define MAX 300
#define line 15000
 
int main(){
    int N,K,M;
    char space;
    int j;
    int value;
    unsigned char word;
    unsigned char text[line];
    unsigned long long int sum;
 
    scanf("%d%c",&N,&space);
    while(N--){
        sum = 0;
        int charValue[MAX]={0};
        scanf("%d%c",&K,&space);
 
        while(K--){
            scanf("%c %d%c",&word,&value,&space);
            charValue[word] = value;
        }
 
        scanf("%d%c",&M,&space);
        while(M--){
            gets(text);
            j=0;
 
            while(text[j]!='\0'){
                if(charValue[text[j]])
                    sum+=charValue[text[j]];
                j++;
            }
        }
        printf("%.2f$\n",sum/100.00);
    }
    return 0;
}
