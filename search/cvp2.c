#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int toplam;
void DizindeAra(char * adds, int inod)
{
struct dirent *dizin_y;
struct stat statim;
char adres[100];
char yeniadres[100];
char *adr;
DIR *dzn;
adr = adds;
if((dzn= opendir(adr))==NULL)
exit(0);

while((dizin_y = readdir(dzn))!=NULL)
{
if(strcmp(dizin_y->d_name,".")==0||strcmp(dizin_y->d_name,"..")==0)
continue;

strcpy(adres,adr);
strcat(adres,dizin_y->d_name);
//printf("%s",adr);
printf("\n%s, %6d\n", dizin_y->d_name,(int)dizin_y->d_ino);

if(-1!=stat(adres,&statim))
{
  if(S_ISDIR(statim.st_mode)){
  //printf("\nDirectory\n");
   strcpy(yeniadres,adres);
   strcat(yeniadres,"/");
  printf("\n searching subdirectory ***%s*** \n",yeniadres);
  DizindeAra(yeniadres,inod);
  }
  else{
  //printf("File\n");
	if(inod==(int)statim.st_ino){
	toplam++;
	printf(" ----hardlink found =%2d / %2d---- \n", toplam, (int)statim.st_nlink);}
      }
}
else
printf("---->");
}
}


int 
main(int argc, char *argv[])
{
toplam=0;
char *baslangic = "/home/mhakan/Masaüstü/"; /*Should be change*/
char *adrs;
int aynod;
char *wd;
struct stat statm;
adrs = argv[1];
if(-1!=stat(adrs,&statm))
aynod = (int)statm.st_ino;
printf("==================INODE : %d===================",aynod);
DizindeAra(baslangic,aynod);
return 0;
}
