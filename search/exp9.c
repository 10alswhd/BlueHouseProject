#include <stdio.h>
#include <stdlib.h>

int bubble_sort(){
        int array[100], n, c, d, swap;

        printf("Enter number of elements\n");
        scanf("%d", &n);

        printf("Enter %d integers\n", n);

        for (c = 0; c < n; c++)
                scanf("%d", &array[c]);

        for (c = 0; c < ( n - 1 ); c++)
        {
                for (d = 0; d < n - c - 1; d++)
                {
                        if (array[d] > array[d+1]) /* For decreasing order use < */
                        {
                                swap       = array[d];
                                array[d]   = array[d+1];
                                array[d+1] = swap;
                        }
                }
        }

        printf("Sorted list in ascending order:\n");

        for ( c = 0; c < n; c++ )
                printf("%d\n", array[c]);

        return 0;
}

int insertion_sort() {
        int n, array[1000], c, d, t;

        printf("Enter number of elements\n");
        scanf("%d", &n);

        printf("Enter %d integers\n", n);

        for (c = 0; c < n; c++) {
                scanf("%d", &array[c]);
        }

        for (c = 1; c <= n - 1; c++) {
                d = c;

                while ( d > 0 && array[d] < array[d-1]) {
                        t          = array[d];
                        array[d]   = array[d-1];
                        array[d-1] = t;

                        d--;
                }
        }

        printf("Sorted list in ascending order:\n");

        for (c = 0; c <= n - 1; c++) {
                printf("%d\n", array[c]);
        }

        return 0;
}

int selection_sort() {
        int array[100], n, c, d, position, swap;

        printf("Enter number of elements\n");
        scanf("%d", &n);

        printf("Enter %d integers\n", n);

        for ( c = 0; c < n; c++ )
                scanf("%d", &array[c]);

        for ( c = 0; c < ( n - 1 ); c++ )
        {
                position = c;

                for ( d = c + 1; d < n; d++ )
                {
                        if ( array[position] > array[d] )
                                position = d;
                }
                if ( position != c )
                {
                        swap = array[c];
                        array[c] = array[position];
                        array[position] = swap;
                }
        }

        printf("Sorted list in ascending order:\n");

        for ( c = 0; c < n; c++ )
                printf("%d\n", array[c]);

        return 0;
}

int main() {
        int choice;
        do {
                printf(" 1. Bubble sort: \n 2. Insertion sort: \n 3. Selection sort: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1: bubble_sort(); break;
                case 2: insertion_sort(); break;
                case 3: selection_sort(); break;
                case 4: return 0;
                default: printf("Enter correct choice: ");
                }
        } while(choice != 4);

        return 0;
}


/*
   1. Bubble sort:
   2. Insertion sort:
   3. Selection sort: 1
   Enter number of elements
   5
   Enter 5 integers
   1 2 3 4 5
   Sorted list in ascending order:
   1
   2
   3
   4
   5
   1. Bubble sort:
   2. Insertion sort:
   3. Selection sort: 2
   Enter number of elements
   6
   Enter 6 integers
   9 2 38 23 11 23
   Sorted list in ascending order:
   2
   9
   11
   23
   23
   38
   1. Bubble sort:
   2. Insertion sort:
   3. Selection sort: 3
   Enter number of elements
   4
   Enter 4 integers
   1 5 7 9
   Sorted list in ascending order:
   1
   5
   7
   9
   1. Bubble sort:
   2. Insertion sort:
   3. Selection sort: 4
 */
