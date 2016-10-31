#include <stdio.h>



//Prototypes

void insertionSort(int arr[], int n );

void swap(int *a, int *b);



void main()

{

        int test_array[] = {8,3,1,0,7,4,2,5,9,6};

        insertionSort(test_array,sizeof(test_array));

}

void insertionSort(int arr[], int n)

{

        int i,j;

        //Main loop

        for(i=1; i<n; i++)

        {

                j =i;

                while((j>0) && (arr[j] < arr[j-1] ) )

                swap(&arr[j], &arr[j-1]);

                j-=1;

        }

        printf("Sorted Values:");

        int k = 0;

        for(k = 0; k < sizeof(arr); k++)

        {

                printf("%i",arr[k]);

        }



}

void swap(int *a, int *b)

{

        int temp = *a;

        *a = *b;

        *b = temp;

}
