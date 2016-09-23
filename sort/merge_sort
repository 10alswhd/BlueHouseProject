// a, b, 두 배열을 정렬하며 merge하는 함수
void merge(int a[], int n, int b[], int m) {
  int *c = (int *)calloc(sizeof(int), (n + m));
  int i = 0, j = 0, k = 0;
 
  while (k < n + m) {
    // 두 배열중 1개가 종료되면 루프에서 벗어남.
    if (i >= n || j >= m) break;
 
    // 두 배열의 값을 비교하여 순서대로 합침.
    if (a[i] < b[j]) {
      c[k++] = a[i++];
    } 
    else if (b[j] < a[i]) {
      c[k++] = b[j++];
    } 
    else {
      c[k++] = a[i++];
      c[k++] = b[j++];
    }
  }
 
  // 둘 중 남은 배열의 내용을 저장
  if (i < n) {
    while (k < m + n) c[k++] = a[i++];
  } 
  else if (j < m) {
    while (k < m + n) c[k++] = b[j++];
  }
 
  // 원래 배열(a)로 복사
  for (int t=0; t < k; t++) {
    a[t] = c[t];
  }
  free(c);
}
 
 
void merge_sort(int a[], int n) {
  // 종료 조건
  if (n == 1) return;
 
  // 재귀 호출
  merge_sort(a, n/2);
  merge_sort(a + n/2, n - n/2);
 
  // 정렬 수행
  merge(a, n/2, a + n/2, n - n/2);
}
