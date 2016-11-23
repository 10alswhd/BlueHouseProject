 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef int (*compare)(const void*,const void*); //비교 알고리즘의 함수 포인터 형식을 compare로 타입명 정의
int compare_int (const void * a, const void * b) //두 개의 정수를 비교하는 알고리즘(입력 인자로 정수가 있는 메모리 주소를 전달해야 함)
{
    const int *p1 = (const int *)a;
    const int *p2 = (const int *)b;
    return *p1 -*p2;
}
 
int compare_str(const void *a,const void *b) //두 개의 문자열을 비교하는 알고리즘(입력 인자로 문자열 주소를 전달해야 함)
{
    const char *p1 = (const char *)a;
    const char *p2 = (const char *)b;
    return strcmp(p1,p2);
}
typedef char strelem[20];//원소 형식이 char이고 크기가 20인 배열 형식을 strelem 으로 타입명 정의
 
int main (void)
{
    int arr[10]= {1, 10 , 15, 20, 29, 30, 31, 33, 35, 50 };//정렬 상태
    strelem arr2[5]= {"강감찬","김구","을지문덕","이순신","홍길동"};//정렬 상태
    int *pos;
    strelem *pos2;
    int key =29;
 
    pos = (int*)bsearch (&key, arr, 10, sizeof(int), compare_int);//이진 탐색
    if(pos!=NULL)
    {
        printf ("%d is in the array %d index.\n",*pos, pos-arr);//탐색 키와 인덱스 출력
    }
    else
    {
        printf ("%d is not in the array.\n",key);
    }
    pos2 = (strelem *) bsearch ("이순신", arr2, 5, sizeof(strelem),compare_str);//이진 탐색
    if(pos2!=NULL)
    {
        printf ("%s is in the array %d index.\n",pos2, pos2-arr2);//탐색 키와 인덱스 출력
    }
    else
    {
        printf ("%d is not in the array.\n","이순신");
    }
    return 0;
}
