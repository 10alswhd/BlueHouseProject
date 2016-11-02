#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

void Merge(int numArray[], int startingElement, int midElement, int endingElement) {
    int lastOfFirstArray = midElement - startingElement ;
    int lastOfSecondArray = endingElement - midElement - 1;
    int *firstArray;
    int *secondArray;
    
    firstArray = malloc((lastOfFirstArray + 1)*sizeof(int));
    secondArray = malloc((lastOfSecondArray +1)*sizeof(int));
    
    
    for (int i = 0; i <= lastOfFirstArray;i++ ) {
        firstArray[i] = numArray[startingElement + i];
    }
    for (int  i = 0; i <= lastOfSecondArray; i++) {
        secondArray[i] = numArray[midElement + i + 1];
        
    }
    firstArray[lastOfFirstArray + 1] = INT32_MAX;
    secondArray[lastOfSecondArray + 1] = INT32_MAX;
    int i = 0, j = 0;
    for (int k = startingElement; k < endingElement+1; k++) {
        if ( firstArray[i] < secondArray[j]) {
            numArray[k] = firstArray[i];
            i++;
        } else {
            numArray[k] = secondArray[j];
            j++;
        }
        
    }
    free(firstArray);
    free(secondArray);
    
}




void mergeSort(int numArray[], int startingElement, int endingElement) {
    
    if (startingElement < endingElement) {
        int midElement  = (startingElement + endingElement)/2;
        mergeSort(numArray, startingElement, midElement);
        mergeSort(numArray, midElement + 1, endingElement);
        Merge(numArray, startingElement, midElement, endingElement);
    }
}


int main(int argc, char const *argv[])
{
    int *number;
    int lenght;
    
    
   
    scanf("%d", &lenght);
    number = malloc(lenght*sizeof(int));
        for(int i = 0; i < lenght; i++)
    {
        scanf("%d", &number[i]);
        
        
    }
    
    mergeSort(number, 0 , lenght - 1);
    
    
    for(int i = 0; i < lenght; ++i) {
        printf("%d\n", number[i]);
    }
    
    
    return 0;
}
