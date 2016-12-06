#include <stdio.h>

/**
 * 有一个数组，它的元素先上升后下降，请用二分法找出拐点元素的下标。
 *
 * There is an array whose elements first ascend and then 
 * descend. Please find the index of the inflection point 
 * element using binary search.
 */ 

int findInflectionPoint(const int arr[], int size)
{
    int inflectionPointIndex = -1;
    int low = 0;
    int high = size - 1;
    while (low < high) 
    {
        int middle = (low + high) / 2;
        
        if (arr[middle - 1] < arr[middle] && arr[middle] < arr[middle + 1]) 
        {
            low = middle;
        }
        else if (arr[middle - 1] > arr[middle] && arr[middle] > arr[middle + 1]) 
        {
            high = middle;
        }
        else 
        {
            inflectionPointIndex = middle;
            break;
        }
    }
    
    return inflectionPointIndex;
}

int main(int argc, char *argv[]) 
{
    int arr[] = {1, 3, 5, 6, 8, 9, 11, 23, 37, 30, 25, 22, 13};
    
    int inflectionPointIndex = findInflectionPoint(arr, sizeof(arr) / sizeof(int));
    printf("arr[%d] = %d\n", inflectionPointIndex, arr[inflectionPointIndex]);
    
    return 0;
}
