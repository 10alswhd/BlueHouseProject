/*
#!/bin/sh
gcc kata02-1.c -g -O0 -Werror -Wall -Wextra --pedantic --pedantic-errors --std=c99 -Wstrict-aliasing -o kata0201
*/
/*
See:
  http://codekata.com/kata/kata02-karate-chop/
*/ 
#include <stdlib.h>
#include <assert.h>

typedef struct test_case {
  int expect;
  int key;
  size_t sz;
  int *arr;
} test_case;

int search(test_case *test) {

  size_t lo = 0, hi = test->sz;
  int *A = test->arr;
  int key = test->key;
  int ret = -1;
  
  while(A) {
    if((long long)hi < (long long)lo) break;
    
    size_t mid = lo + ((hi - lo) / 2);

    if(A[mid] < key) { 
      lo = mid + 1;  
    } else if(A[mid] > key) {
      hi = mid - 1;
    } else if(A[mid] == key) {
      ret = mid;
      break;
    }
  }

  return ret;
}

int main(int argc, char **argv) {
  int *t0   = NULL;
  int  t1[1] = { 1 };
  int  t2[3] = { 1, 3, 5 };
  int  t3[4] = { 1, 3, 5, 7 };
  size_t t0_sz = (sizeof(t0) / sizeof(*t0)) - 1;
  size_t t1_sz = (sizeof(t1) / sizeof(*t1)) - 1;
  size_t t2_sz = (sizeof(t2) / sizeof(*t2)) - 1;
  size_t t3_sz = (sizeof(t3) / sizeof(*t3)) - 1; 
  size_t i = 0;
  
  argc = argc; /* make compiler happy */
  argv = argv; /* make compiler happy */
 
  test_case cases[19] = {
    /* 0 */
    { -1, 3, t0_sz, t0 },
    /* 1 */
    { -1, 3, t1_sz, t1 },
    {  0, 1, t1_sz, t1 },
    /* 2 */
    {  0, 1, t2_sz, t2 },
    {  1, 3, t2_sz, t2 },
    {  2, 5, t2_sz, t2 }, 
    { -1, 0, t2_sz, t2 },
    { -1, 2, t2_sz, t2 },
    { -1, 4, t2_sz, t2 },
    { -1, 6, t2_sz, t2 },
    /* 3 */
    {  0, 1, t3_sz, t3 },
    {  1, 3, t3_sz, t3 },
    {  2, 5, t3_sz, t3 },
    {  3, 7, t3_sz, t3 },
    { -1, 0, t3_sz, t3 },
    { -1, 2, t3_sz, t3 },
    { -1, 4, t3_sz, t3 },
    { -1, 6, t3_sz, t3 },
    { -1, 8, t3_sz, t3 }
  };

  for(i = 0; i < (sizeof(cases) / sizeof(test_case)); i++) {
    test_case c = cases[i];
    int ret = search(&c);
    assert(c.expect == ret); 
  } 

  return EXIT_SUCCESS;
}
