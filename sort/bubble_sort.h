#ifndef BUBBLE_SORT_H_

#define BUBBLE_SORT_H_ 



template <typename T>

void swap(T &a, T &b) 

{

    T tmp = a;

    a = b;

    b = tmp;

}



template <typename T>

void bubble_sort(T *A, int low, int high)

{

    int last;

    while(low + 1 < high)

    {   

        last = -1; 

        for (int i = low + 1; i < high; ++i)                                                                                                                                                                     

        {   

            if (A[i] < A[i-1])

            {   

                swap(A[i], A[i-1]);

                last = i;  

            }   

        }   

        high = last;

    }   

}



#endif
