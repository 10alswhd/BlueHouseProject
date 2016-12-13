#include <stdio.h>

int blocknum(int num)
{
  int n = 0;
  for ( n = 0; n < 16; n++)
  {
    if ((num >> 30))
    {
      printf("Stop%d\n", n);
      break;
    }
    num = num << 2;
  }
  return n;
}
int main()
{
  int i=1;
  printf("%d block\n", blocknum(1));
  printf("%d block\n", blocknum(1000));
}
