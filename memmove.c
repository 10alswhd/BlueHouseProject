
#include <string.h>
#include <stdio.h>
 
int main(void)
{
    int i;
    int arr[10]={1,2,3,4,5,6,7,8,9,10};  
 
    printf("== 이동 전 ==\n");//이동 전 arr의 원소들 출력
    for(i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
 
    memmove(arr+1,arr,sizeof(int)*9);//arr에 있는 int 형식 원소 9개를 arr+1로 이동
    arr[0] = 0; //arr[0]을 0으로 설정
    printf("== 이동 후(빈자리는 0으로 채움) ==\n");//이동 전 arr의 원소들 출력
    for(i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");   
 
    return 0;
}
