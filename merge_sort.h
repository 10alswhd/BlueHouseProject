#ifndef MERGE_SORT_H_

#define MERGE_SORT_H_                                                                                                                                                                                            



template <typename T>

void merge(T *a, int low, int mid, int high, T *tmpbuf)

{

    int i = low;

    int j = mid;

    int k = 0;

    while( i < mid && j < high)

    {

        if (a[i] <= a[j])

            tmpbuf[k++] = a[i++];

        else

            tmpbuf[k++] = a[j++];

    }



    while (i < mid) tmpbuf[k++] = a[i++];

    while (j < high) tmpbuf[k++] = a[j++];



    for (int i = low; i < high; ++i)

    {

        a[i] = tmpbuf[i - low];

    }

}



template <typename T>

void merge_sort(T *A, int low, int high, T* tmpbuf)

{

    if (high - low < 2) return;



    int mid = (low + high) / 2;

    merge_sort(A, low, mid, tmpbuf);

    merge_sort(A, mid, high, tmpbuf);

    merge(A, low, mid, high, tmpbuf);

}



template <typename T>

void merge_sort(T *A, int low, int high)

{

    if (high - low < 0)  return;



    T *tmpbuf = new T[high - low];



    merge_sort(A, low, high, tmpbuf);



    delete []tmpbuf;

}



#endif
