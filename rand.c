#include <stdlib.h>
#include <time.h>
#include <stdio.h>
 
#define MAX_VALUE   45
#define MAX_TRY       6
 
int main(void)
{   
    int check[MAX_VALUE]={0};
    int cnt;
    int value;
 
    printf("RAND_MAX is %d \n",RAND_MAX);
 
    srand((unsigned)time(NULL));//랜덤 seed 값 설정
 
    for(cnt=0;cnt<MAX_TRY;cnt++)//MAX_TRY 번 반복
    {
        while(1)
        {
            value = rand()%MAX_VALUE; //0~MAX_VALUE 사이의 랜덤 값 발생
            if(check[value]==0)//발생한 적이 없으면
            {
                check[value] = 1;//발생하였음을 마킹
                printf("%d ",value+1);//발생한 값 +1 출력
                break;//while 반복문 탈출
            }
        }       
    }
    printf("\n");
 
    return 0;
}
 
