#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 100
int base26(char L1,char L2,char L3,char alphabet[]){
    int i=0;
    int k=3;
    int sum=0;
    while(k--){
        i=0;
        while(alphabet[i]!='\0'){
            if(alphabet[i]==L1 && k==2){
                sum += i*pow(26,2);
                break;
            }
            else if(alphabet[i]==L2 && k==1){
                sum += i*pow(26,1);
                break;
            }
            else if(alphabet[i]==L3 && k==0){
                sum += i*pow(26,0);
                break;
            }
            i++;
        }
    }
    return sum;
 
}
int main(){
    char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char L1,L2,L3;
    int D,temp,ans;
    int N=0;
    char space;
    scanf("%d%c",&N,&space);
    while(N--){
        scanf("%c%c%c-%d%c",&L1,&L2,&L3,&D,&space);
        temp = base26(L1,L2,L3,alphabet);
        if(temp>=D)
            ans = temp-D;
        else
            ans = D-temp;
        if(ans<=100)
            printf("nice\n");
        else
            printf("not nice\n");
    }
 
}
