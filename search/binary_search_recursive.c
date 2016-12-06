int binary_search(int array[], int value, int low, int high)
{
    if (low >= high) {
        return -1;
    }
    
    int mid = low + (high - low) / 2;
    
    if (array[mid] < value) {
        return binary_search(array, value, mid + 1, high);
    }
    else if (array[mid] > value) {
        return binary_search(array, value, low, mid - 1);
    }
    else {
        return mid;
    }
}
