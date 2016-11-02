#include <stdio.h>



int partition(int *, int, int);

void quickSort(int *, int, int);



int main(void) {

  int i;

  int ary[] = {-1, 11, 4, 5, 1, 41, 9, 19}; /* -1はダミー */

  int n = sizeof(ary)/sizeof(ary[0]) - 1;   /* 要素数 */



  quickSort(ary, 1, n);         /* クイックソート */



  for (i = 1; i <= n; i++) {

    printf("%d ", ary[i]);

  }

  putchar('\n');



  return 0;

}



int partition(int *A, int p, int r) {

  int j;

  int x = A[r];                 /* ピボットとして選択 */

  int i = p-1;

  for (j = p; j < r; j++) {

    if (A[j] <= x) {

      i++;

      /* A[i]とA[j]を交換する */

      int tmp = A[i];

      A[i] = A[j];

      A[j] = tmp;

    }

  }

  /* A[i+1]とA[r]を交換する */

  int tmp = A[i+1];

  A[i+1] = A[r];

  A[r] = tmp;



  return i+1;

}



void quickSort(int *A, int p, int r) {

  if (p < r) {

    int q = partition(A, p, r);

    quickSort(A, p, q-1);

    quickSort(A, q+1, r);

  }

}
