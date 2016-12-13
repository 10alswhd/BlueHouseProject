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
  int max = 0;
  srand((unsigned int) time(NULL));

  for(i=0; i<num; i++) {
    r = rand() % 10;
    x[i] = r;
    b[r]++;
  }

  for(i=0; i<10; i++) {
    max = (max < b[i]) ? b[i] : max;
    printf("%3d",b[i]);
  }

  printf("\n\n");

  for(i=0; i<max; i++) {
    for(j=0; j<10; j++) {
      if((0 < b[j] && b[j] <= max) && ((max-i) <= b[j])) {
        printf("  X");
      } else {
        printf("   ");
      }
    }
    printf("\n");
  }

  printf("------------------------------\n");
  printf("  0  1  2  3  4  5  6  7  8  9\n");

  return 0;
}
