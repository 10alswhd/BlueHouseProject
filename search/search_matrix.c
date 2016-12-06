#include <stdio.h>

void search(int a[5][5], int start_row, int start_col, int end_row, int end_col, int elem){

    int i = start_row + (end_row - start_row)/2;
    int j = start_col + (end_col - start_col )/2;

    if(a[i][j] == elem){
        printf("Element found at (%d, %d)", i,j);
    }
    else{
        if(i != end_row || j != start_col)
            search(a,start_row, j, i, end_col, elem);

        if(start_row == end_row && start_col + 1 == end_col){
            if(a[start_row][end_col] == elem){
            printf("Element found at (%d, %d)", i,j);
            }
        }
        if(elem < a[i][j]){
            if(j-1 >start_col)
                search(a,start_row, start_col, end_row, j-1, elem);
        }
        else{
            if (i+1<end_row)
                search(a,i+1, start_col, end_row, end_col, elem);
        }
    }
}

int main(void) {
        // your code goes here
    int b[5][5] = {{1,2,3,4,5},
                    { 6,7,8,9,10 },
                    { 11,12,13,14,15 },
                    { 16,17,18,19,20 },
                    { 21,22,23,24,25}};

    search(b,0,0,5,5, 19);
    return 0;
}
