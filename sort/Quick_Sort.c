#include <stdio.h>
 
#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환
 
 
int *origin;
int on;
 
void QuickSort(int *base, int n);
void ViewArr(int *arr, int n);
int main(void)
{
    int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
    origin = arr;
    on = 10;
    ViewArr(arr, 10);
    QuickSort(arr, 10);
    ViewArr(arr, 10);
    return 0;
}
 
void PrintSpace(int n);
void QuickSort(int *base, int n)
{
    int pivot = 0; // 피벗의 위치 기억하는 변수
    int left = 0, right = 0; // 피벗보다 큰 값과 작은 값의 위치를 찾기위한 변수
 
    if (n <= 1)
    {
        return;
    }
 
    left = 0;
    right = n;
 
    //퀵 소트는 피벗보다 작은 값들은 앞쪽으로 이동시키고 피벗보다 큰 값들은 뒤쪽으로 이동시켜서
    //작은 값들과 큰 값들 사이에 피벗을 보내는 것이 기본 동작입니다.
    //그리고 난 후에 작은 값들이 있는 배열을 재귀적으로 다시 정렬하고
    //큰 값들이 있는 배열을 재귀적으로 다시 정렬하는 알고리즘입니다.
    while (1)
    {
        //앞쪽에 피벗(인덱스 0에 있는 원소)보다 큰 값을 만날 때까지 left를 이동합니다.
        //for문 맨 앞의 left를 1 증가하면서 출발하는 이유는 이전에 끝난 다음 위치부터 시작하기 위해서입니다.
        for (left++; (left<n) && (base[0] >= base[left]); left++);
        //뒤쪽에 피벗(인덱스 0에 있는 원소)보다 작은 값을 만날 때까지 right를 이동합니다.
        for (right--; (right>0) && (base[0]<base[right]); right--);
 
        //만약 left가 right보다 작다면 피벗과 비교했을 때 작은 값이 큰 값보다 뒤에 있으니 교환합니다.
        if (left<right)
        {
            SWAP(base[left], base[right]);
            PrintSpace(base - origin);
            ViewArr(base, n);
        }
        //그렇지 않다면 피벗을 중심으로 작은 값들과 큰 값들이 분리 작업이 끝난 것입니다.
        else
        {
            break;
        }
    }
    //이제 피벗을 작은 값들과 큰 값들 사이로 보냅니다.
    SWAP(base[0], base[right]);
    PrintSpace(base - origin);
    ViewArr(base, n);
 
    //피벗보다 작은 값들이 있는 앞쪽을 재귀 호출로 정렬합니다.
    QuickSort(base, right);
    //피벗보다 큰 값들이 있는 뒤쪽을 재귀 호출로 정렬합니다.
    QuickSort(base + left, n - left);
}
void PrintSpace(int n)
{
    int i = 0;
    for (i = 0; i<n; i++)
    {
        printf("   ");
    }
}
void ViewArr(int *arr, int n)
{
    int i = 0;
    for (i = 0; i<n; i++)
    {
        printf("%2d ", arr[i]);
    }
    printf("\n");
}
