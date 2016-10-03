#include<stdio.h>
#include<conio.h>
void qsort(int arr[20], int fst, int last);
int main()
{
 int arr[30];
 int i,size;
 printf("Enter total no. of the elements : ");
 scanf("%d",&size);
 printf("Enter total %d elements : \n",size);
 for(i=0; i<size; i++)
    scanf("%d",&arr[i]);
 qsort(arr,0,size-1);
 printf("Quick sorted elements are as  : \n");
 for(i=0; i<size; i++)
    printf("%d\t",arr[i]);
 getch();
 return 0;
}
void qsort(int arr[20], int fst, int last)
{
 int i,j,pivot,tmp;
 if(fst<last)
 {
   pivot=fst;
   i=fst;
   j=last;
   while(i<j)
   {
     while(arr[i]<=arr[pivot] && i<last)
        i++;
     while(arr[j]>arr[pivot])
        j--;
     if(i<j)
     {
        tmp=arr[i];
        arr[i]=arr[j];
        arr[j]=tmp; 
     }
   }
   tmp=arr[pivot];
   arr[pivot]=arr[j];
   arr[j]=tmp;
   qsort(arr,fst,j-1);
   qsort(arr,j+1,last);
 }
}
