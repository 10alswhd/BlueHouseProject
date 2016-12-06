#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 * 
 * Re-write search in such a way that it uses linear search, 
 * returning true if value is in values and false if value is not in values.
 * Take care to return false right away if n isn’t even positive.
 */
bool search(int value, int values[], int n)
{
    // linear search algorithm
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
            return true;
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    return;
}
