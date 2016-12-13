#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int i,j,r;
  i = rand();
  i = i%2;
  int num = 50; 
  int x[num];
  int b[10] = {0};
  srand((unsigned int) time(NULL));

  for(i=0; i<num; i++) {
    r = rand() % 10; 
    x[i] = r;
    b[r]++;
    printf(" %d,",r);
    if(i%10 == 9) {
      printf("\n");
    }   
  }

  for(i=0; i<10; i++) {
    printf("%d:",i);
    for(j=0; j<b[i]; j++) {
      printf("X");
    }   
    printf("\n");
  }

  return 0;
}
