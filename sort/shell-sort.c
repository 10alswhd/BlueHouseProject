void shell_sort(int a[], int n) {
  for (int interval = n/2; interval > 0; interval /= 2) {
    for (int start = 0; start < interval; start++) {
      select_sort(a, n, start, interval);
    }
  }
}
 
// 시작위치(start)와 Interval을 지정하여 select sort 수행하는 함수
void select_sort(int a[], int n, int start, int interval) {
  for (int i = start; i < n - 1; i += interval) {
    int min_index = i;
    for (int j = i + interval; j < n; j += interval) {
      if (a[j] < a[min_index]) min_index = j;
    }
    int temp = a[i];
    a[i] = a[min_index];
    a[min_index] = temp;
  } 
}
