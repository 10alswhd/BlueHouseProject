#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>



void print_array(int *array, int size)

{

    for (int i = 0; i < size; i++)

        printf("%d ", array[i]);

    printf("\n");

}



void swap(int *array, int i, int j)

{

    if (!array)

        return;



    int temp = array[i];

    array[i] = array[j];

    array[j] = temp;

}



void bubble_sort(int *array, int size)

{

    bool flag = true;



    // We only need "size - 1" passes.

    for (int pass = 0; pass < size - 1 && flag; pass++)

    {

        flag = false;

        // The last "pass" numbers already in place in the "pass" pass.

        for (int cursor = 0; cursor < size - 1 - pass; cursor++)

        {

            if (array[cursor] > array[cursor + 1])

            {

                swap(array, cursor, cursor + 1);

                flag = true;

            }

        }

        print_array(array, size);

    }

}



int main(void)

{

    int size;

    scanf("%d", &size);

    int array[size];



    for (int i = 0; i < size; i++)

        scanf("%d", &array[i]);

    bubble_sort(array, size);

    return EXIT_SUCCESS;

}





Input:

9

9 1 5 8 3 7 4 6 2

Output:

1 5 8 3 7 4 6 2 9

1 5 3 7 4 6 2 8 9

1 3 5 4 6 2 7 8 9

1 3 4 5 2 6 7 8 9

1 3 4 2 5 6 7 8 9

1 3 2 4 5 6 7 8 9

1 2 3 4 5 6 7 8 9

1 2 3 4 5 6 7 8 9
