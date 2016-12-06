#include <stdio.h>
#include <stdlib.h>

/* O(m + n) space complexity. */
void rotate_matrix1(int *matrix, int row, int column)
{
    if (!matrix || row <= 0 | column <= 0)
        return;

    int i, j;
    char *rows_with_zeros, *columns_with_zeros;

    rows_with_zeros = calloc(row, sizeof (*rows_with_zeros));
    if (!rows_with_zeros)
    {
        printf("Error: out of memory.\n");
        return;
    }

    columns_with_zeros = calloc(column, sizeof (*columns_with_zeros));
    if (!columns_with_zeros)
    {
        free(rows_with_zeros);
        printf("Error: out of memory.\n");
        return;
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (*(matrix + i * column + j) == 0)
            {
                rows_with_zeros[i] = 1;
                columns_with_zeros[j] = 1;
            }
        }
    }
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (rows_with_zeros[i] || columns_with_zeros[j])
            {
                *(matrix + i * column + j) = 0;
            }
        }
    }
    free(rows_with_zeros);
    free(columns_with_zeros);
}

/* O(1) space complexity. */
void rotate_matrix2(int *matrix, int row, int column)
{
    if (!matrix || row <= 0 || column <= 0)
        return;

    int i, j;
    char first_row_with_zero, first_column_with_zero;

    /* First row and first column are using for storage,
     * search zero in those positions to determine their status */
    for (i = 0; i < row; i++)
    {
        if (*(matrix + i * column + 0) == 0)
        {
            first_column_with_zero = 1;
            break;
        }
    }
    for (j = 0; j < column; j++)
    {
        if (*(matrix + 0 * column + j) == 0)
        {
            first_row_with_zero = 1;
            break;
        }
    }

    /* Search zero elements in other positions, 
     * then mark it in the first row or first column. */
    for (i = 1; i < row; i++)
    {
        for (j = 1; j < column; j++)
        {
            if (*(matrix + i * column + j) == 0)
            {
                *(matrix + i * column + 0) = 0;
                *(matrix + 0 * column + j) = 0;
            }
        }
    }

    /* Set zeroes in other positions according to the first row and first column. */
    for (i = 1; i < row; i++)
    {
        for (j = 1; j < column; j++)
        {
            if (*(matrix + i * column + 0) == 0 || *(matrix + 0 * column + j) == 0)
            {
                *(matrix + i * column + j) = 0;
            }
        }
    }

    /* Set zeroes for first row and first column. */
    if (first_row_with_zero)
    {
        for (i = 0; i < column; i++)
        {
            *(matrix + 0 * column + j) = 0;
        }
    }
    if (first_column_with_zero)
    {
        for (j = 0; j < row; j++)
        {
            *(matrix + j * column + 0) = 0;
        }
    }
}

void display_matrix(int *matrix, int row, int column)
{
    int i, j;

    if (!matrix || row <= 0 || column <= 0)
        return;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            printf("%3d", *(matrix + i * column + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    int matrix[5][5] = {
        {1, 2, 3, 4, 5},
        {6, 0, 8, 0, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 0, 20},
        {21, 22, 23, 24, 25}
        //        {1, 2, 3,},
        //        {6, 0, 8,},
        //        {11, 12, 13},
        //        {16, 17, 18},
        //        {16, 0, 19}
    };

    display_matrix(&matrix[0][0], 5, 5);
    rotate_matrix2(&matrix[0][0], 5, 5);
    display_matrix(&matrix[0][0], 5, 5);

    return 0;
}
