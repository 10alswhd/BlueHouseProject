#define type int
#define less(a, b) a < b
#define swap(a, b) type t = a; a = b; b = t;

void sift(type *array, int start, int end) {
    while(start * 2 + 1 < end) {
        int child = 2 * start + 1;
        if (child + 1 < end && less(array[child], array[child + 1])) {
            child += 1;
        }
        if (less(array[start], array[child])) {
            swap(array[child], array[start]);
            start = child;
        }
        else return;
    }
}

void heapsort(type* array, int n) {
    int start, end;
    for (start = (n - 2)/2; start >= 0; start--) {
        sift(array, start, n);
    }
    for (end = n - 1; end > 0; end--) {
        swap(array[end], array[0]);
        sift(array, 0, end);
    }
}
