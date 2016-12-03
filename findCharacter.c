#include <stdio.h>

void main(){
  char theArray[80], searchChar;
  int index=0, count=0;
  
  printf("\n Enter the phrase.\n\n");
  gets(theArray);  
  printf("\n What character do you want to find: ");
  scanf(" %c", &searchChar);
  printf("\n You are looking for: %c \n", searchChar);
  
  //scanf(" %s", &theArray[0]);
  
  while( theArray[index] != '\0'){
    if (theArray[index] == searchChar){
      count++;
    } 
    index++;
  }
  printf("   Length = %d\n", index);
  printf("   count = %d\n", count);
  printf("\n   ECHO: %s\n\n", theArray);
}
