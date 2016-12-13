#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "FunctionsMenu.h"
#define MAX 128


     


int main(){
    subjlist();
    int selection;
    char c[MAX]="lbyec72";
    struct student info;
    for(;;){
    printf("LOG IN\n");
    printf("ID. Number: ");
    scanf("%d",&info.id);
    printf("Password: "); 
    scanf("%s",&info.pass);
    if((strcmp(info.pass,c)==0)&&(info.id==11342781)){
    for(;;){
    
    printf("\nPlease select a task:\n");
    printf("1. Add Class\n");
    printf("2. Drop Class\n");
    printf("3. Display Schedule\n");
    printf("4. View Classes\n");
    printf("5. Log Out\n");
    printf("Selection>> ");
    scanf("%d",&selection);
    system("cls");
       if(selection==1){
       addclass();
       system("cls");
       }
       else if(selection==2){
       removeclass();
       system("cls");
       }
       else if(selection==3){
       dispsched();
       system("cls");
       }
       else if(selection==4){
       viewclass();
       system("PAUSE");
       system("cls");
       }
       else{
       printf("Invalid Input\n");
       }
    }
    
    
    }
    else{
    printf("Invalid ID Number and Password Combination\n");
    }
    }
 
    system("PAUSE");
    return 0;
    }
