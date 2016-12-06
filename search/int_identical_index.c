#include <stdio.h>
#include <stdbool.h>

// array has been already sorted. 
// So we can use binary search to reduece timecost
int getValueSameWithIndex(int * array, int length) {
  if (array == NULL || length == 0)
    return -1;

  int left = 0;
  int right = length - 1;

  while (left <= right) {
    int middle = (left + right) / 2;
    if (array[middle] == middle)
      return middle;
    else if (array[middle] > middle)
      right = middle - 1;
    else
      left = middle + 1;
  }

  return -1;
}

bool testTargetCheck(int * array, int length, int target) {
  if (target == getValueSameWithIndex(array, length)) {
    printf("OK\n");
    return true;
  }

  printf("FAILE\n");
  return false;
}

int main (void) {
  printf("test start\n");

  int array1[] = {-2, 0, 2, 4, 6, 8, 10, 11};
  testTargetCheck(array1, sizeof(array1)/sizeof(int), 2);

  int array2[] = {-6, -3, 0, 3, 6, 9};
  testTargetCheck(array2, sizeof(array2)/sizeof(int), 3);

  int array3[] = {-4, -1, 2, 5, 8, 11};
  testTargetCheck(array3, sizeof(array3)/sizeof(int), 2);

  int array4[] = {-2, 0, 2, 4, 6, 8};
  testTargetCheck(array4, sizeof(array4)/sizeof(int), 4);

  return 0;
}
