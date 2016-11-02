#include <stdio.h>

#include <stdlib.h>



void * malloc_s(size_t size) {

    void * p = NULL;

    if ((p = (void*) malloc(size)) == NULL) {

        perror("Exception: alloc failed\n");

        exit(EXIT_FAILURE);

    }

    return p;

}



void merge(int** dest, int* L1, size_t L1_size, int* L2, size_t L2_size) {



    int i = 0;

    int j = 0;

    int count = 0;



    size_t size = L1_size + L2_size;



    for (count = 0; count < size; count++) {

        if (i == L1_size) {

            for (; j < L2_size; j++, count++) { (*dest)[count] = L2[j]; }

        }

        else if (j == L2_size) {

            for (; i < L1_size; i++, count++) { (*dest)[count] = L1[i]; }

        }

        else {

            (*dest)[count] = (L1[i] <= L2[j]) ? L1[i++] : L2[j++];

        }

    }

}



void merge_sort(int** array, size_t size) {



    int * L1 = NULL;

    int * L2 = NULL;

    size_t L1_size;

    size_t L2_size;

    int i, j;



    if (size == 1) { return; }



    L1_size = (size_t) (size/2+0.5);

    L2_size = (size_t) (size-L1_size);

    L1 = (int*) malloc_s(sizeof(int) * L1_size);

    L2 = (int*) malloc_s(sizeof(int) * L2_size);



    for (i = 0; i < L1_size; i++)      { L1[i] = (*array)[i]; }

    for (j = 0; j < L2_size; i++, j++) { L2[j] = (*array)[i]; }



    merge_sort(&L1, L1_size);

    merge_sort(&L2, L2_size);



    merge(array, L1, L1_size, L2, L2_size);

    free(L1); free(L2);

}
