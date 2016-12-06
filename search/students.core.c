#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#ifdef __unix__
    #define OS_Windows 0
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)     
    #define OS_Windows 1
    #include <windows.h>
    #include <tchar.h>
    #define DIV 1048576
    #define WIDTH 7
#endif
 
#define MAX_STRING_SIZE 100
#define MAX_FIELDS 5
 
#define S_NAME "Students Core v 0.1 Alpha"
#define S_DEV_NAME "Marcelo Boeira - MarceloBoeira.com"

 
typedef struct student {
  int id;
  char name[MAX_STRING_SIZE];
  char ra[5];
  char cpf[11];
  char rg[10];
  
} student;
 
 int G_StudentsCount;
 student* G_Students;
 char *G_Message;
 
 
/* Core Procedures */ 
int isWindows(){
    return OS_Windows;  
}
 
#ifdef __unix__
void getch(){
  system("read a");
}
#endif

 
char *getMessage(){
  return G_Message;
}
void setMessage(char m[]){
  G_Message = m;
}
 

/** Screen Procedures **/
void screenHeader() {
     printf("_______________________________________ \n");
     printf("------ ");
     printf(S_NAME);
     printf(" ------ \n");
     printf("_______________________________________ \n\n");
}
 
void screenClear(){
  (isWindows()) ? system("cls") : system("clear");
}
 
void sort(){
    int i,j, c = 0;
    student tmp;
    // 23/04/2014 - Performance Upgrade ((A==B) == (B==A))
    for(i=0; i < G_StudentsCount; i++)
      for(j=0; j < i; j++) {
        if(strcmp(G_Students[j].name,G_Students[i].name) > 0) {
          tmp = G_Students[j];
          G_Students[j] = G_Students[i];
          G_Students[i] = tmp;
        }   
      }
}

void search(int mod){
     int i,k,j = 0;
     char buffer[50];     
 
     screenClear();
     screenHeader();
     
     if (mod != 0) {
        printf("Please type something to search:");
        scanf("%s",&buffer);
        fflush(stdin);
     }
     
     screenClear();
     screenHeader();
     printf("\n Search Results: \n");
     
     for (i=0; i < G_StudentsCount; i++){
         if (mod == 0){
            k = 1;
         } 
         else {
              k = 0;
              char *tp;
              if (mod == 1) tp = strstr(G_Students[i].name, buffer);
              else if (mod == 2) tp = strstr(G_Students[i].ra, buffer);
              else if (mod == 3) tp = strstr(G_Students[i].cpf, buffer);
              else if (mod == 4) tp = strstr(G_Students[i].rg, buffer);
              if (tp) k = 1;
         }
          
         if (k) {
            j++;
            printf("-----------\nID: %i\nName: %s\nRA: %s\nCPF: %s\nRG: %s\n", 
                   G_Students[i].id, 
                   G_Students[i].name, 
                   G_Students[i].ra, 
                   G_Students[i].cpf, 
                   G_Students[i].rg);
         }
     }
     (j == 0) ? setMessage("Sorry, nothing found !") : getch(); 
}


student new(int id){
     student std;
     screenClear();  
     screenHeader();    
     std.id = id;
     printf("\nType a Name:");
     scanf("%s",&std.name);
     fflush(stdin);
	 printf("\nType a RA:");
     scanf("%s",&std.ra);
     fflush(stdin);
	 printf("\nType a CPF:");
     scanf("%s",&std.cpf);
     fflush(stdin);
	 printf("\nType a RG:");
     scanf("%s",&std.rg);
     fflush(stdin);
     setMessage("Student added to the database!"); 
     return std;
}

void init() {
  int i = 0;
  screenClear(); 
  screenHeader();
  printf("\nType how many students:");
  scanf("%d",&G_StudentsCount);
  
  G_Students = malloc( G_StudentsCount * sizeof (student));
  for (i = 0; i < G_StudentsCount; i++){
    G_Students[i] = new(i);
  }  
  sort();
}
 
int main () {
    int _opt = 0;
    int _exit = 0;
	int i = 0;
    setMessage(" ");
    init();
    while(!_exit) {
       screenClear();
       screenHeader();           
       printf("\nMenu:       \n %s \n1) List Students\n2) Search by name\n3) Search by CPF\n4) Search by RA\n9) Exit\n\n Type you option:", getMessage());
       setMessage(" ");
       scanf("%d", &_opt);
       fflush(stdin);
       switch (_opt) { 
              case 1: search(0); break;
              case 2: search(1); break;
              case 3: search(2); break;
              case 4: search(3); break;
              case 5: search(4); break;
              case 9: exit(0); break;                   
              default: setMessage("Invalid Option!"); break;                   
       }
    }
    return 0;
}
