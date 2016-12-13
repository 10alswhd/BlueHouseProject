#include <stdio.h>

int main (void) {
  int i;
  int input[5] = {0};

  for(i=0; i<5; i++) {
    printf("Input : ");
    scanf("%d",&input[i]);
  }

  for(i=0; i<5; i++) {
    printf("%d ",input[(5-1)-i]);
  }
  return 0;
}
