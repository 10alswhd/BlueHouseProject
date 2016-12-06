#include <stdio.h>
#include <float.h>

// A utility function to get sum of array elements freq[i] to freq[j]
float sum(float freq[], int i, int j);

// A recursive function to calculate cost of optimal binary search tree
float optCost(float freq[], int i, int j)
{
   // Base cases
   if (j < i)      // If there are no elements in this subarray
     return 0;
   if (j == i)     // If there is one element in this subarray
     return freq[i];

   // Get sum of freq[i], freq[i+1], ... freq[j]
   float fsum = sum(freq, i, j);

   // Initialize minimum value
   float min = FLT_MAX;


   // One by one consider all elements as root and recursively find cost
   // of the BST, compare the cost with min and update min if needed
   int r;
   for (r = i; r <= j; ++r)
   {
       float cost = optCost(freq, i, r-1) + optCost(freq, r+1, j);
       if (cost < min)
          min = cost;
   }

   // Return minimum value
   return min + fsum;
}

// The main function that calculates minimum cost of a Binary Search Tree.
// It mainly uses optCost() to find the optimal cost.
float optimalSearchTree(int keys[], float freq[], int n)
{
     // Here array keys[] is assumed to be sorted in increasing order.
     // If keys[] is not sorted, then add code to sort keys, and rearrange
     // freq[] accordingly.
     return optCost(freq, 0, n-1);
}

// A utility function to get sum of array elements freq[i] to freq[j]
float sum(float freq[], int i, int j)
{
    float s = 0.0;
    int k;
    for (k = i; k <=j; k++)
       s += freq[k];
    return s;
}

// Driver program to test above functions
int main()
{
    int keys[] = {1, 2, 3};
    float freq[] = {0.7, 0.2, 0.1};
    int n = sizeof(keys)/sizeof(keys[0]);
    printf("Cost of Optimal BST is %f ", optimalSearchTree(keys, freq, n));
    return 0;
}
