#define type int
#define less(a, b) a < b

unsigned int binary_search(type *a, unsigned int n, type value) {
    int index = 0;
    while(n > 0) {
        unsigned int mid = n >> 1;
        if(a[mid] == value) {
            return index + mid;
        } else if(less(a[mid], value)) {
            mid += 1;
            index += mid;
            a += mid;
            n -= mid;
        } else {
            n = mid;
        }
    }
    return -1;
}
