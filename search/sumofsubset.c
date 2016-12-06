#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int sumofsubset(int *array, int cur, int size, int search){
    int i,sum=0;

    if(search == 0) return 1;
    for(i=cur; i<size ;i++){
        sum += sumofsubset(array, i + 1, size, search - array[i]);
    }
    return sum;
}

int main(int argc, char *argv[])
{
    //int array[5] = {1, 2, 3, 4, 5};
    int array[5] = {5, 5, 10, 2, 3};
    //int array[4] = {10, 2, 3, 5};
    printf("num of pattern=%d\n", sumofsubset(array, 0, 5, 15));
    return 0;
}
