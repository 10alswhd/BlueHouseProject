#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#define MAX 10000
 
void TestCase(int *base, int n);//TestCase
int main(void)
{
    int arr1[3] = { 1, 2, 3 };
    int arr2[4] = { 1,2,3,3 };
 
    TestCase(arr1, 3);
    TestCase(arr2, 4);
 
    return 0;
}
int FindBalance(int *base, int n);//균형 원소 찾는 함수
void TestCase(int *base, int n)
{
    int i = 0;
    int balance;
    for (i = 0; i<n; i++)
    {
        printf("%d ", base[i]);
    }
    printf("\n");
 
    balance = FindBalance(base, n);
    if (balance == -1)
    {
        printf("균형 원소 없음\n");
    }
    else
    {
        printf("균형 원소: 인덱스 %d \n", balance);
    }
}
int FindBalance(int *base, int n)
{
    int *f_sum;//자신보다 앞쪽 요소들의합
    int *t_sum;//자신보다 뒤쪽 요소들의합
    int i;
 
    f_sum = (int *)malloc(sizeof(int)*n);
    memset(f_sum, 0, sizeof(int)*n);
    t_sum = (int *)malloc(sizeof(int)*n);
    memset(t_sum, 0, sizeof(int)*n);
 
    f_sum[0] = 0; //0번째 앞쪽의 합은 0으로 설정
    for (i = 1; i<n; ++i)//i를 n-1 개수만큼 반복
    {
        f_sum[i] = f_sum[i - 1] + base[i - 1];//j 앞쪽의 합은 i-1 앞쪽의 합에 i-1요소 값
    }
    i = n - 1;//i를 마지막 요소의인덱스로 설정
    t_sum[i] = 0; //마지막 요소 뒤쪽의합을 0으로 설정
    for (i--; i >= 0; --i)//i가 0보다 클 때 1씩 감소
    {
        t_sum[i] = t_sum[i + 1] + base[i + 1];//j 뒤쪽의 합은 i+1 뒤쪽의 합에 i+1 요소 값
        if (t_sum[i] == f_sum[i]) //i 뒤쪽의 합과  앞쪽이 합이 같으면
        {
            return i;
        }
    }
    return -1;
}
