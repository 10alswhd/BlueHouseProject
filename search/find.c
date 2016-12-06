/**
 * find.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Prompts user for as many as MAX values until EOF is reached, 
 * then proceeds to search that "haystack" of values for given needle.
 *
 * Usage: ./find needle
 *
 * where needle is the value to find in a haystack of values
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// maximum amount of hay
const int MAX = 65536;

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./find needle\n");
        return -1;
    }

    // remember needle
    int needle = atoi(argv[1]);

    // fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // wait for hay until EOF
        printf("\nhaystack[%i] = ", size);
        int straw = GetInt();
        if (straw == INT_MAX)
        {
            break;
        }
     
        // add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // sort the haystack
    sort(haystack, size);

    /* Mine
        for (int i = 0; i < size; i++)
    {
        printf("%i ", haystack[i]);
    }
    printf("\n Numbers Sorted");
    //Mine
     */
    // try to find needle in haystack
    if (search(needle, haystack, size))
    {
        printf("\nFound needle in haystack!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find needle in haystack.\n\n");
        return 1;
    }
}
Raw
 helpers.c
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
 */


bool search(int value, int values[], int n)
{

    if (n < 0)
        return false;
  
	// Binary non recursive binary search
    // TODO: implement a searching algorithm
    int min = 0;
    int max = n;

    // while length of the list > 0
    while (min <= max)
    {
	    // Look at the middle of the list
		int middle = (min + max) / 2; 
	    
	    // if number found, return true
	    if (value == values[middle])
	    {
	    	return true;
	    }
	    // else if number higher, search right
	    else if (value > values[middle])
	    {
	    	min = middle + 1;
	    }	
	    
	    // else if number is lower, search left
	    else if (value < values[middle])
	    {
		    max = middle - 1;
	    }	

    }
	return false;  	

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    /**
    *TODO: implement an O(n^2) sorting algorithm
    * Bubble sort
   	* cycle through array
	*/
	for (int k = 0; k < n; k++)
	{
		/**
		 * Optmize,
		 * Check for no swaps
		* int swaps = 0;
		*/
		for(int i = 0; i < n - 1 - k; i++)
		{
			if ( values[i] > values[i + 1])
			{
				int temp = values[i + 1];
				values[i + 1] = values[i];
				values[i] = temp;
			}
		}
    }

    return;

}

/*
// Recursive binary search
bool binarySearch(int values[], int value, int min, int max)
{
    // while length of the list > 0
    while (max >= min)
    {
	    // Look at the middle of the list
		int middle = (min + max) / 2; 
	    
	    // if number found, return true
	    if (value == middle)
	    	return true;
	    
	    // else if number is lower, search left
	    else if (value < middle)
	    {
			binarySearch(values, value, min, middle - 1);
	    }	
	    // else if number higher, search right
	    else if (value > middle)
	    {
			binarySearch(values, value, middle + 1, max);
	    }	
	
    }
	return false;  	
	
	
}
*/
