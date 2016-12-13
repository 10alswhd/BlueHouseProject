/*
 * Author: NagaChaitanya Vellanki
 *
 *
 * search for a key in an array,
 * if key is found return pointer to key
 * else return NULL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *lfind(void *key, void *base, size_t num_elements, size_t element_size, int (*compare)(void *, void *, size_t)) {
  int index = 0;
  for(index = 0; index < num_elements; index++) {
    void *element_addr = (char *)base + (index * element_size);
    if(compare(key, element_addr, element_size) == 0) {
      return element_addr;
    }
  }

  return NULL;
}

int compare(void *element1, void *element2, size_t element_size) {
  return memcmp(element1, element2, element_size);
}

int main(int argc, char *argv[]) {
  int arr_ints[] = {1,2,3,4,5};
  double arr_doubles[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  int key_int = 5;
  double key_double = 3.0;
  double *dptr = NULL;
  int  *iptr = NULL;

  iptr = (int *)lfind(&key_int, arr_ints, sizeof(arr_ints)/sizeof(arr_ints[0]), sizeof(arr_ints[0]), compare);
  if(iptr == NULL) {
    printf("Key not found in the array\n");
  } else {
    printf("Key %d found at index %ld\n", *iptr, (long int)(iptr - arr_ints));
  }


  dptr = (double *)lfind(&key_double, arr_doubles, sizeof(arr_doubles)/sizeof(arr_doubles[0]), sizeof(arr_doubles[0]), compare);
  if(dptr == NULL) {
    printf("Key not found in the array\n");
  } else {
    printf("Key %f found at index %ld\n", *dptr, (long int)(dptr - arr_doubles));
  }

  exit(EXIT_SUCCESS);
}
