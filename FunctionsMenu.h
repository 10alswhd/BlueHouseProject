#define MAX 128
#include <string.h>

void dispsched(){
     int i,haves[MAX];
    printf("\n\n\t\tDE LA SALLE UNIVERSITY MANILA\n");
            printf("\t\tTerm 2 A.Y. 2014 - 2015\n");
            printf("NAME: Amiel Lumbuan\tMAJOR: Mechanical Engineering\n");
            printf("SUBJECT\t\tSECTION\tUNITS\tDAY\tTIME\t\tROOM\n");
            printf("---------------------------------------------------------------------\n"); 
           
            for(i=0;i<=3;i++){                                   
               printf("%s\t\t%s\t%s\t%s\t%s\t%s\n",ar[i].name,ar[i].section,ar[i].units,ar[i].days,ar[i].time,ar[i].room);                            
            }
            system("PAUSE");
     }
       
void addclass(){
     
     char search[MAX];
     int i,j,ka,n,m, haves[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, counter=0;
     for(;;){
     printf("Search Class to Add: ");
     scanf("%s",&search);  
       for(i=0;i< 10;i++){
         if(strcmp(search,ar[i].name)==0){
         printf("\nFound: \n");
         printf("%s\t\t%s\t%s\t%s\t%s\t%s\n",ar[i].name,ar[i].section,ar[i].units,ar[i].days,ar[i].time,ar[i].room);
         haves[counter]=i;
         counter++;
         printf("Would you like to Add (1. Yes or 2. No): ");
         scanf("%d",&n);
         
            if(n==1){
            printf("\n\n\t\tDE LA SALLE UNIVERSITY MANILA\n");
            printf("\t\tTerm 2 A.Y. 2014 - 2015\n");
            printf("NAME: Amiel Lumbuan\tMAJOR: Mechanical Engineering\n");
            printf("SUBJECT\t\tSECTION\tUNITS\tDAY\tTIME\t\tROOM\n");
            printf("---------------------------------------------------------------------\n"); 
           
            for(j=0;j<10;j++){                     
               if(haves[j]!= -1)
               {
                
               printf("%s\t\t%s\t%s\t%s\t%s\t%s\n",ar[j].name,ar[j].section,ar[j].units,ar[j].days,ar[j].time,ar[j].room); 
               
               }  
               
            }
            system("PAUSE");
            }  
            else if(n==2){
            break;
            }
            else{
         printf("No Results Found\n");
         system("cls");
         }
         }
         
       }
     printf("Would you like to add another class?(1.Yes or 2.No): ");
     scanf("%d",&m);
      if(m==1){
      system("cls");
      }
      else if(m==2){
      break;     
      }
     }     
}

void removeclass(){
     int i;
     char removeclass[MAX];
     printf("Which Class to Remove?: ");
     scanf("%s",&removeclass);
     for(i=0;i<=10;i++){
     if(strcmp(removeclass,ar[i].name)==0){
     ar[i].name[MAX]='\0';
     ar[i].section[MAX]='\0';
     ar[i].units[MAX]='\0';
     ar[i].days[MAX]='\0';
     ar[i].time[MAX]='\0';
     ar[i].room[MAX]='\0';
     dispsched();
     }
     //else{
          //printf("No Result");
          //}
     }
     system("PAUSE");
     }
     
void viewclass(){
     int j,haves[MAX];
     printf("AVAILABLE CLASSES:\n");
     printf("SUBJECT\t\tSECTION\tUNITS\tDAY\tTIME\t\tROOM\n");
     printf("---------------------------------------------------------------------\n"); 
           
            for(j=0;j<=10;j++){                     
               printf("%s\t\t%s\t%s\t%s\t%s\t%s\n",ar[j].name,ar[j].section,ar[j].units,ar[j].days,ar[j].time,ar[j].room);         
               }   
            
     }
