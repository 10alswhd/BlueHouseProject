#include <stdio.h>
#define MAX 50

int merge[MAX],n;
int x[20],size,i;
int heap[10], no, j, c, root, temp;

void mergeSort(int arr[],int low,int mid,int high);
void partition(int arr[],int low,int high);

void partition(int arr[],int low,int high){

        int mid;

        if(low<high) {
                mid=(low+high)/2;
                partition(arr,low,mid);
                partition(arr,mid+1,high);
                mergeSort(arr,low,mid,high);
        }
}

void mergeSort(int arr[],int low,int mid,int high){

        int i,m,k,l,temp[MAX];

        l=low;
        i=low;
        m=mid+1;

        while((l<=mid)&&(m<=high)) {

                if(arr[l]<=arr[m]) {
                        temp[i]=arr[l];
                        l++;
                }
                else{
                        temp[i]=arr[m];
                        m++;
                }
                i++;
        }

        if(l>mid) {
                for(k=m; k<=high; k++) {
                        temp[i]=arr[k];
                        i++;
                }
        }
        else{
                for(k=l; k<=mid; k++) {
                        temp[i]=arr[k];
                        i++;
                }
        }

        for(k=low; k<=high; k++) {
                arr[k]=temp[k];
        }
}



void quicksort(int x[10],int first,int last){
        int pivot,j,temp,i;

        if(first<last) {
                pivot=first;
                i=first;
                j=last;

                while(i<j) {
                        while(x[i]<=x[pivot]&&i<last)
                                i++;
                        while(x[j]>x[pivot])
                                j--;
                        if(i<j) {
                                temp=x[i];
                                x[i]=x[j];
                                x[j]=temp;
                        }
                }

                temp=x[pivot];
                x[pivot]=x[j];
                x[j]=temp;
                quicksort(x,first,j-1);
                quicksort(x,j+1,last);

        }
}


int main() {
        int choice;
        do {
                printf("\n 1. Quick sort: \n 2. Merge sort: \n 3. Heap sort: \n 4. Exit: \n");
                scanf("%d", &choice);

                switch (choice) {
                case 1: printf("Enter size of the array: ");
                        scanf("%d",&size);

                        printf("Enter %d elements: ",size);
                        for(i=0; i<size; i++)
                                scanf("%d",&x[i]);

                        quicksort(x,0,size-1);

                        printf("Sorted elements: ");
                        for(i=0; i<size; i++)
                                printf(" %d",x[i]);
                        break;

                case 2: printf("Enter the total number of elements: ");
                        scanf("%d",&n);

                        printf("Enter the elements which to be sort: ");
                        for(i=0; i<n; i++) {
                                scanf("%d",&merge[i]);
                        }

                        partition(merge,0,n-1);

                        printf("After merge sorting elements are: ");
                        for(i=0; i<n; i++)
                                printf("%d ",merge[i]);

                        break;

                case 3:  printf("\n Enter no of elements :");
                        scanf("%d", &no);

                        printf("\n Enter the nos : ");
                        for (i = 0; i < no; i++)
                                scanf("%d", &heap[i]);

                        for (i = 1; i < no; i++) {
                                c = i;
                                do
                                {
                                        root = (c - 1) / 2;
                                        if (heap[root] < heap[c])
                                        {
                                                temp = heap[root];
                                                heap[root] = heap[c];
                                                heap[c] = temp;
                                        }
                                        c = root;
                                } while (c != 0);
                        }

                        printf("Heap array : ");
                        for (i = 0; i < no; i++)
                                printf("%d ", heap[i]);
                        for (j = no - 1; j >= 0; j--) {
                                temp = heap[0];
                                heap[0] = heap[j];
                                heap[j] = temp;
                                root = 0;
                                do {
                                        c = 2 * root + 1;
                                        if ((heap[c] < heap[c + 1]) && c < j-1)
                                                c++;
                                        if (heap[root]<heap[c] && c<j) {
                                                temp = heap[root];
                                                heap[root] = heap[c];
                                                heap[c] = temp;
                                        }
                                        root = c;
                                } while (c < j);
                        }

                        printf("\n The sorted array is : ");
                        for (i = 0; i < no; i++)
                                printf("%d ", heap[i]);
                        break;
                case 4: return 0;
                default: printf("Enter correct choice: ");


                }


        } while(choice != 4);

        return 0;
}


/*
   1. Quick sort:
   2. Merge sort:
   3. Heap sort:
   4. Exit:
   1
   Enter size of the array: 5
   Enter 5 elements: 5 4 3 2 1
   Sorted elements:  1 2 3 4 5
   1. Quick sort:
   2. Merge sort:
   3. Heap sort:
   4. Exit:
   2
   Enter the total number of elements: 5
   Enter the elements which to be sort: 5 4 3 2 1
   After merge sorting elements are: 1 2 3 4 5
   1. Quick sort:
   2. Merge sort:
   3. Heap sort:
   4. Exit:
   3
   Enter no of elements :5
   Enter the nos : 5 4 3 2 1
   Heap array : 5 4 3 2 1
   The sorted array is : 1 2 3 4 5
   1. Quick sort:
   2. Merge sort:
   3. Heap sort:
   4. Exit:
   4
 */
