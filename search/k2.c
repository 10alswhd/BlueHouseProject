#include <stdio.h>

int main(int argc, char *argv[]) {
  int i,j;
  int param;
  
  param = atoi(argv[1]);

  for(i=0; i<param; i++) {
    for(j=0; j<param-(1+i); j++) {
      printf(" ");
    }   
    for(j=0; j<i+1; j++) {
      printf("x");
    }   
    printf("\n");
  }

  return 0;
}
