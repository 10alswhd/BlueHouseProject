#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int int_cmp(const void *,const void *);
static void print_arr(const int *arr,int size);
int binary_search(int arr[],int key,int low,int high);
void find_all_pairs(int arr[],int sum,int size);

int binary_search(int arr[],int key,int low,int high) 
{
  int mid = 0;
  while (low <= high) {
     mid = (high + low)/2;
     if (arr[mid] > key) {
         high = mid - 1;
     } else if (arr[mid] < key) {
         low = mid + 1;
     } else {
         return mid;
     }
  }
  return -1;
}

void find_all_pairs(int arr[],int sum,int size) 
{
 int i = 0;
 int key = 0,residual = 0,pos = -1;
 for (i = 0; i < size; i++) {
     key = arr[i];
     residual = sum - key;
     if (residual > key) {
        pos = binary_search(arr,residual,0,size);
        if (pos >= 0) printf("(%d, %d)\n",arr[i],arr[pos]);
     }
  }
}

static int int_cmp(const void *a,const void *b) 
{
 int ia = *(const int *) a;
 int ib = *(const int *) b;
 return ia - ib;
}

static void print_arr(const int *arr,int size)
{
 int i = 0;
 for (i = 0; i < size; i++) printf("%d ",arr[i]);
 printf("\n");
}

int main()
{
 int arr[] = {2,10,8,3,4,6,9,15,20,5};
 int size = (int) (sizeof arr/sizeof *arr);
 print_arr(&arr[0],size);
 qsort((void *) arr,size,sizeof(int),int_cmp);
 print_arr(&arr[0],size);
 find_all_pairs(arr,11,size);
 return 0;
}
