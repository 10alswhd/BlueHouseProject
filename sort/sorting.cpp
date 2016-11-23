#include<iostream>
using namespace std;

class Sort{
public:

    static void swap(int& a, int &b){
        int temp = a;
        a = b;
        b = temp;
    }
    
    static void bubblesort(int* array,int size){
        for(int i=1;i<=size-1;++i){
            for(int j=0;j<=size-i-1;++j){
                if(array[j]>array[j+1])
                    swap(array[j],array[j+1]);
            } 
        }
    }

    static void selectionsort(int* array, int size){
        int imin;
        for(int i=0;i<=size-2;++i){
            imin = i;
            for(int j=i+1;j<=size-1;++j){
                if(array[j]<array[imin])
                    imin = j;
            }
            swap(array[imin],array[i]);
        }
    }

    static void insertionsort(int* array, int size){
        int hole,value;
        for(int i=1;i<=size-1;++i){
            hole = i;
            value = array[i];
            while(hole > 0 && array[hole-1]>value){
                array[hole] = array[hole-1];
                --hole;
            }
            array[hole] = value;
        }
    }

    static void merge(int* array,int n,int* leftarray,int leftcount,int* rightarray,int rightcount){
        int i=0,j=0,k=0;
        while(i<leftcount && j<rightcount){
            if(leftarray[i]<=rightarray[j])
                array[k++] = leftarray[i++];
            else
                array[k++] = rightarray[j++];
        }
        while(i<leftcount){ array[k++] = leftarray[i++];}
        while(j<rightcount){ array[k++] = rightarray[j++];}
    }

    static void mergesort(int *array, int n){
        if(n == 1) return;
        int mid = n/2;
        int* leftarray = new int[mid];
        int* rightarray = new int[n-mid];
        for(int i=0;i<mid;++i){ leftarray[i] = array[i];}
        for(int i=mid;i<n;++i){ rightarray[i-mid] = array[i];}
        mergesort(leftarray,mid);
        mergesort(rightarray,n-mid);
        merge(array,n,leftarray,mid,rightarray,n-mid);
    }

    static int partition(int* array,int start,int end){
        int pIndex = start;
        for(int i=start;i<=end-1;++i){
            if(array[i]<array[end])
                swap(array[pIndex++],array[i]);
        }
        swap(array[pIndex],array[end]);
        return pIndex;
    }

    static void quicksort(int* array,int start,int end){
        if(start>=end) return;
        int pIndex = partition(array,start,end);
        quicksort(array,start,pIndex-1);
        quicksort(array,pIndex+1,end);
    }

    static void maxHeapify(int* array,int n,int i){
        int leftchild = 2*i;
        int rightchild  = 2*i + 1;
        int max = i;
        if(array[leftchild] > array[max] && leftchild <= n)
            max = leftchild;
        if(array[rightchild] > array[max] && rightchild <= n)
            max = rightchild;
        if(max != i){
            swap(array[i],array[max]);
            maxHeapify(array,n,max);
        }
    }

    static void buildmaxheap(int* array,int n){
        for(int i=n/2;i>=1;--i){ maxHeapify(array,n,i);}
    }

    static void heapsort(int* array,int n){
        buildmaxheap(array,n);
        for(int i=n;i>=2;--i){
            swap(array[1],array[i]);
            maxHeapify(array,i-1,1);
        }
    }
};  

int main(){
    int array[] = {1,9,3,6,5,7,4,2,8};
    int size = sizeof(array)/sizeof(array[0]);
    //Sort::bubblesort(array,size);
    //Sort::selectionsort(array,size);
    //Sort::insertionsort(array,size);
    //Sort::mergesort(array,size);
    //Sort::quicksort(array,0,size-1);
    Sort::heapsort(array,size-1);
    for(int i=0;i<size;++i){ cout<<array[i]<<" | "; }
    cout<<endl;
    return 0;
}
