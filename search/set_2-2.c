#include <stdio.h>

int sOcc(char *ptr, char *specialChar);

main(){
   char myArray[80], search, *ptr;
   int cnt=0;
   printf("\n Please enter a phrase... ");
   gets(myArray);
   printf(" Please enter a search char ...");
   scanf(" %c", &search);
   printf(" I found %d search characters\n\n",sOcc(myArray,search));
}


int sOcc(char *ptr, char *specialChar){
   int cnt=0;
   char specialChar_0 = &specialChar;
   while( *ptr != '\0'){
      if( (*ptr) == specialChar_0){
         cnt++;
      }
      ptr++;
   }
   return(cnt);
}
