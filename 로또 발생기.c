//로또 발생기
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
 
#define CNT 6
#define MAX_NUM 45
#define MAX_TRY   1000
 
#define SWAP(x,y)  {int tmp=x; x=y; y = tmp;}
 
void make_randoms(int *base, int n)
{
    int i = 0;//반복문 수행 횟수
    int value = 0;//랜덤 발생한 수
    int checks[MAX_NUM] = { 0 };//발생한 수는 1, 발생하지 않은 수는 0
 
    for (i = 0; i<n; i++)//n개를 발생
    {
        do
        {
            value = rand() % 45; //0~44의 랜덤한 수를 발생(발생한수가 h일 때 실제 값은 h+1로 처리할 것임)
 
        } while (checks[value]);//만약 checks[value]가 참이면이미 발생한 수이므로 다시 반복해야 함
        checks[value] = 1; //value 값은 이미 발생하였음을 마킹
 
        base[i] = value; //중복 체크를 하여 새로 발생한 값을 버퍼에 보관
    }
}
 
void sort(int *base, int n)
{
    int i = 0;
    int j = 0;
    int temp = 0;
 
    for (i = 0; i<(n - 1); i++)//마지막 원소 한 개가 남을 때까지(하나만있을 때 정렬이 필요없음)
    {
        for (j = i + 1; j<n; j++)//j를 마지막 원소까지 순차적 증가
        {
            if (base[j - 1]> base[j])//앞에 값이 더 크면
            {
 
                SWAP(base[j - 1], base[j]);   //교환
            }
        }
    }
}
 
int main(void)
{
    int base[CNT] = { 0 };//랜덤한 수를 보관
    int i = 0;//반복문에서 반복 횟수를 기억할 변수
    int j = 0;//반복문에서 반복 횟수를 기억할 변수
    int value = 0; //반복문 내부에서 발생하게 랜덤한 값을 기억할 변수
    int scores[MAX_NUM] = { 0 };//특정 값이 몇 번발생했는지 기억할 변수
    int mi = 0;//최대 빈도수가 있는 인덱스
 
    srand((unsigned int)time(0));//랜덤의 씨앗값 설정(프로그램 동작할 때마다 다르게 발생하게 씨앗값 설정)
    for (i = 0; i<MAX_TRY; i++)//1000회 시도
    {
        printf("%04dth try ", i + 1);//시도 횟수 출력
        make_randoms(base, CNT); //랜덤한 수를 n개 제비뽑기
        sort(base, CNT); //정렬
        for (j = 0; j<CNT; j++)//제비뽑기한 CNT개의 수만큼출력
        {
            value = base[j]; //제비뽑기한 수
            printf("%02d ", value + 1);//제비뽑기에서 0~44사이에 수를 발생하였기에 1을 더함(1~45)
            scores[value]++;//제비뽑기한 수의 발생 빈도를 1 증가
        }
        printf("\n");
    }
 
    for (i = 0; i<CNT; i++)
    {
        mi = i;
        for (j = i + 1; j<MAX_NUM; j++)
        {
            if (scores[mi]<scores[j])
            {
                mi = j;
            }
        }
        base[i] = mi + 1;
        scores[mi] = 0;
    }
 
    printf("추천 번호:");
    for (i = 0; i<CNT; i++)
    {
        printf("%d ", base[i]);
    }
    printf("\n");
}
 
