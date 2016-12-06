/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 * 
 * Re-write search in such a way that it uses linear search, 
 * returning true if value is in values and false if value is not in values.
 * Take care to return false right away if n isn’t even positive.
 * 
 * Implement sort so that the function actually sorts, from smallest to largest,
 * the array of numbers that it’s passed, in such a way that its running time is
 * in O(n2), where n is the array’s size.
 */

// linear search algorithm
// bool search(int value, int values[], int n)
// {
//    for (int i = 0; i < n; i++)
//    {
//        if (values[i] == value)
//            return true;
//    }
//    
//    return false;
// }

bool binarySearch(int value, int values[], int min, int max)
{
    int midpoint = 0;
    
    if (max < min)
        return false;
    else
        midpoint = (max + min)/2;
    
    if (values[midpoint] < value)
        return binarySearch(value, values, midpoint + 1, max);
    else if (values[midpoint] > value)
        return binarySearch(value, values, min, midpoint - 1);
    else if (value == values[midpoint])
        return true;
    else
        return false;
}


// binary search algorithm
bool search(int value, int values[], int n)
{
    return binarySearch(value, values, 0, n-1);
}

/**
 * Sorts array of n values.
 * 
 *  Holds current value in a temporary block and compares that to the left of
 *  it in the array. If j-1 is less than the temp then move j-1 to one to the right.
 *  Do that until you find a value that is less than the temp. Insert temp right
 *  where you stopped.
 * 
 */
void sort(int values[], int n)
{
    // insertion sort algorithm
    
    for (int i = 1; i < n; i++)
    {
     
        int temp = values[i];
        int j = i;
        
        while (j > 0 && (values[j-1] > temp))
        {
            values[j] = values[j-1];
            j--;
        }
        values[j] = temp;
    }
    return;
}
