int BinarySearch(int *array, int n, int key)
{
    register int low = 0, high = n-1, mid;
    while(low <= high)
    {
        mid = low + ((high-low)/2);
        if(array[mid] < key)
            low = mid + 1; 
        else if(array[mid] > key)
            high = mid-1;
        else
            return mid;
    }
    return -1;
}
