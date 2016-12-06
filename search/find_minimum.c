int find_minimum(int a[], int low, int high){

    // always restrict the search to the unsorted 
    // sub-array. The min is always there.
    while (arr[low] > arr[high]) {
        // find mid of array.
        mid = (low + high)/2
        // decide which sub-array to continue with.
        if (arr[mid] > arr[high]) {
            low = mid + 1
        } else {
            high = mid
        }
    }
    return arr[low];
}
