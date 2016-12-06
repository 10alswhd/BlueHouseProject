#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int arr[MAX];
int i, num;
int item, pos;

int linear_search() {
        int array[100], search, c, n;

        printf("Enter the number of elements in array\n");
        scanf("%d",&n);

        printf("Enter %d integer(s)\n", n);

        for (c = 0; c < n; c++)
                scanf("%d", &array[c]);

        printf("Enter the number to search\n");
        scanf("%d", &search);

        for (c = 0; c < n; c++)
        {
                if (array[c] == search) /* if required element found */
                {
                        printf("%d is present at location %d.\n", search, c+1);
                        break;
                }
        }
        if (c == n)
                printf("%d is not present in array.\n", search);

        return 0;
}

int interpolation_search(int a[], int bottom, int top, int item)
{
        int mid;
        while (bottom <= top) {
                mid = bottom + (top - bottom) * ((item - a[bottom]) / (a[top] - a[bottom]));
                if (item == a[mid])
                        return mid + 1;
                if (item < a[mid])
                        top = mid - 1;
                else
                        bottom = mid + 1;
        }
        return -1;
}

int main() {
        int choice;
        do {
                printf(" 1. Linear search: \n 2. Interpolation search: \n 3. Exit: \n");
                scanf("%d", &choice);

                switch (choice) {
                case 1: linear_search(); break;
                case 2: printf("\nEnter total elements: ");
                        scanf("%d", &num);
                        printf("Enter %d Elements in ascending order: ", num);
                        for (i = 0; i < num; i++)
                                scanf("%d", &arr[i]);
                        printf("\nSearch For : ");
                        scanf("%d", &item);
                        pos = interpolation_search(&arr[0], 0, num - 1, item);
                        if (pos == -1)
                                printf("\nElement %d not found\n", item);
                        else
                                printf("\nElement %d found at position %d\n", item, pos);
                        break;
                case 3: return 0;
                default: printf("Enter correct choice: \n" );
                }
        } while (choice != 3);

        return 0;
}

/*
   1. Linear search:
   2. Interpolation search:
   3. Exit:
   1
   Enter the number of elements in array
   5
   Enter 5 integer(s)
   4 5 6 7 8
   Enter the number to search
   3
   3 is not present in array.
   1. Linear search:
   2. Interpolation search:
   3. Exit:
   2
   Enter total elements: 5
   Enter 5 Elements in ascending order: 3 4 5 6 7
   Search For : 5
   Element 5 found at position 3
   1. Linear search:
   2. Interpolation search:
   3. Exit:
   3
 */
