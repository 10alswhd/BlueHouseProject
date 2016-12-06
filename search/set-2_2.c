#include <stdio.h>

// main(){
//    char myArray[80], search, *ptr;
//    int cnt=0;
//    printf(" Type a phrase... ");
//    gets(myArray);
//    printf(" enter a special character to be searched and counted:\n");
//    scanf(" %c", &search);
//    ptr = myArray;
//    while( *ptr != '\0'){
//       if( *ptr == search){
//          cnt++;
//       }
//       ptr++;
//    }
//    printf(" There were %d special characters found", cnt);
// }

int occ(char *ptr[80], char *searchChar){
   //ptr = myArray;
   int count=0;
   printf("\n Search char: %c Array: %c\n", *searchChar, *ptr[0] );
   
   while( *ptr != '\0'){
      if( *ptr == searchChar){
         count++;
      }
      ptr++;
      printf("\n the counts are ptr: %c cnt: %d\n", *ptr, count );
      
   }
   printf(" \nThere were %d special characters found\n\n", count);
}

main(){
   char myArray[80], search, *ptr_0, *ptr_1;
   int cnt=0;
   printf("\n Type a phrase... ");
   gets(myArray);
   //ptr_0 = myArray;
   printf("\n enter a special character to be searched and counted:\n");
   search = getchar();
   //scanf(" %c", &search);
   ptr_0 = myArray[0];
   ptr_1 = search;
   occ(ptr_0, ptr_1);
}
