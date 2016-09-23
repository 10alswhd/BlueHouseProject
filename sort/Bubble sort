#include <stdio.h>
#include <stdlib.h>
void InsertionSort(int * Array,int Length);
void bubbleSort(int * Array,int Length);
void main()
{
    int N,i;
    printf("Enter the number of elements for the sorting : ");
    scanf("%d",&N);
    int * Array = malloc(N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&Array[i]);
    }
    bubbleSort(Array,N);
    printArray(Array,N);
}

//function to perform the bubble sort
void bubbleSort(int * Array,int Length)
{
    int i,j,k,swapped = 0;
    for(i=Length;i>0;i--)
    {
        for(j=1;j<i;j++)
        {
            if(Array[j] < Array[j-1])
            {
                k = Array[j];
                Array[j] = Array[j-1];
                Array[j-1] = k;
                swapped = 1;
            }
        }
        if(swapped = 0)
            break;
        swapped = 0;
    }
}
//function to print the array
void printArray(int * Array,int Length)
{
    int i=0;
    for(i=0;i<Length;i++)
    {
        printf("%d ",Array[i]);
    }
    printf("\n");
}
