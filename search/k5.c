#include <stdio.h>

int main(void) {
  int i;
  int a[5] = {0};
  int query = 0;
  int count = 0;

  for(i=0; i<5; i++) {
    printf("Input : ");
    scanf("%d",&a[i]);
  }

  printf("Search number : ");
  scanf("%d",&query);

  for(i=0; i<5; i++) {
    if(query == a[i]) {
      count++;
      printf("a[%d]=%d\n",i,query);
    }   
  }

  printf("Number of match = %d\n",count);

  return 0;
}
