#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
 
#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환
#define VALUE(val,seat)        ((val&(1<<seat))!=0)
 
void RadixSort(int *base,int n);
void ViewArr(int *arr,int n);
int main(void)
{
    int arr[10]={9,4,3,10,5,8,7,6,2,1};
    RadixSort(arr,10);   
    return 0;
}
 
int CounterSort(int *base, int size, int seat);
void RadixSort(int *base,int n)
{
    int i;   
    ViewArr(base,n);//현재 상태 출력
    for(i=0;i<31;i++)
    {
        if(CounterSort(base,n,i)==0)//카운터 정렬을 하지 않았을 때(정렬 완료)
        {
            break;
        }       
        ViewArr(base,n);
    }
}
int CounterSort(int *base, int size,int seat)
{
    int carr[2]={-1,0};
   
    int value;
    int i = 0;
    int *temp;
    temp = (int *)malloc(sizeof(int)*size);
   
    for(i=0;i<size;i++)
    {
        value = VALUE(base[i],seat);
        carr[value]++;       
    }
 
    if((carr[0] == -1)||(carr[0] == size-1))
    {
        return 0;
    }
   
    carr[1]+=carr[0];   
 
    for(i=size-1; i>=0; i--)
    {
        value = VALUE(base[i],seat);
        temp[carr[value]] = base[i];
        carr[value]--;
    }
    memcpy(base,temp,sizeof(int)*size);
    free(temp);
    return 1;
}
void ViewArr(int *arr,int n)
{
    int i = 0;
    for(i=0;i<n;i++)
    {
        printf("%2d ",arr[i]);
    }
    printf("\n");
}
