/*
Solution : 
Same As:
10222 - Decode the Mad man
*/

#include <iostream>
#define MAX 500
using namespace std;
void Search(char input,char keyboard[]){
    int i = 0;
    if(input == ' ')
        cout<<" ";
    else{
        while(keyboard[i]!=input)
            i++;
        cout<<keyboard[i-1];
    } 
}
int main(){
    char keyboard[]="`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
    char input[MAX];
    while(cin.getline(input,MAX)){
        int i = 0;
        while(input[i]){
            Search(input[i],keyboard);
            i++;
        }
        cout<<endl;
    }
}
