#include <stdio.h>

void main(){
  
  char theArray[80], searchChar;                //Step 1
  int wordSize=0; //Step 2
  int repitions=0; //Step 4
  int index=0;     //Step 5
  int palindromeCounter; //Step 6
  
  printf("\n Enter the word: ");                //Step 1
  gets(theArray);                               //Step 1
  printf("\n The word is: %s \n", theArray);    //Check 1

  while( theArray[wordSize] != '\0'){           //Step 2
    wordSize++;                                 //Step 2
  }
  printf("\n Length = %d\n", wordSize);         //Check 2
  
  //Even Vs Odd
  if (wordSize % 2){                            //Step 3
    repitions = ((wordSize-1)/2);               //Step 4
    printf("\n %d is odd\n", wordSize);         //Check 3
    printf("\n repitions = %d \n", repitions);  //Check 4
  }
  else{
    repitions = ((wordSize)/2);                 //Check 3
    printf("\n %d is even\n", wordSize);        //Check 3
    printf("\n repitions = %d \n", repitions);  //Check 4
  }
  
  for (index = 0; index < repitions; index++){  //Step 5
    printf("\n repition %d: %d vs %d\n", index+1, index, repitions-1-index); //Check 5
    
    if(theArray[index] != theArray[wordSize-1-index]){ //Step 6
      palindromeCounter++; 
    } 
  }

  if (palindromeCounter){               //Step 7
    printf("\n Not a palindrome!\n");
  }
  else{
    printf("\n Yes a palindrome!\n");
  }
  
  printf("\n");

}
