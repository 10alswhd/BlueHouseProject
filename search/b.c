#include <stdio.h>


int bsearch(int left, int right, int find, int *a) {
  if (left > right)
    return -1;

  int mid = (left + right) / 2;

  if (find == a[mid])
    return mid;
  else if(find < a[mid])
    return bsearch(left, (mid - 1), find, a);
  else if(find > a[mid])
    return bsearch((mid + 1), right, find, a);

}

int main() {
  int a[] = { 0, 2, 4, 6, 8, 10, 12 };

  int f = bsearch(0, 7, 10, a);

  printf("position of %d is: %d\n", 10, f);
}
