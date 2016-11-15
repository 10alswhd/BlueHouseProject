 
#include <string.h>
#include <stdio.h>
 
int main(void)
{
    int arr[10];
    int i;
 
    printf("== 설정 전 ==\n");
    for(i=0;i<10;i++)
    {
        printf("%d ",arr[i]);//쓰레기 값 출력
    }
    printf("\n");
 
    memset(arr,0,sizeof(arr));//arr의 메모리를 0으로 설정
    printf("== 설정 후 ==\n");
    for(i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");  
 
    return 0;
}
