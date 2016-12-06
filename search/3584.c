#include <stdio.h>

int search(int *a, int, int);

int main(void)
{
  int a[10], i, x;

  int j = 0;

  while(1) {
    for (i = 0; i < 10; ++i)
    {
     scanf("%d", a + i);
    }

    scanf("%d", &x);

    i = search(a, 10, x);

    if (-1 == i)
    {
      printf("Not found\n");
    }
    else
    {
      printf("%d\n", i);
    }
  }

  return 0;
}

int search(int list[], int n, int x)
{
  int i, j, flag;

  for (i = 0, flag = 0; i < n; ++i)
  {
    if (x == list[i])
    {
      flag = 1;
      return i;
      break;
    }
  }

  if (0 == flag)
  {
    return -1;
  }
}
