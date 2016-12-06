#include <stdio.h>
#include <stdlib.h>

int binary_search(int a[], int min, int max, int value)
{
  if (max < min) {
    return -1;
  }
  int mid = (max + min) / 2;
  if (value == a[mid]) {
    return mid;
  } else if (a[mid] > value) {
    return binary_search(a, min, mid-1, value);
  } else if (a[mid] < value) {
    return binary_search(a, mid+1, max, value);
  }
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("You need to input the value that you need to search.\n");
    return -1;
  }

  int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  int result = binary_search(a, 0, 11, atoi(argv[1]));
  printf("result: %d\n", result);

  return 0;
}
