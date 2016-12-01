#include <stdio.h>
#include <time.h>
 
#define SECONDS_PER_DAY    (24*60*60)
#define SECONDS_PER_HOUR  (60*60)
#define SECONDS_PER_MIN     (60)
 
 
int main(void)
{
 
    struct tm now_date, birth_date = { 0 };
    time_t birth_time, now_time;
    long long gap_time;
    int year, month, day, hour, min, second;
    char buf[100];
 
    //생년 월 일 입력
    printf("생년 월 일 : ");
    scanf_s("%d %d %d", &year, &month, &day);
 
    birth_date.tm_year = year - 1900;//tm_year는 1900년을 기준
    birth_date.tm_mon = month - 1; //tm_mon은 0이 1월
    birth_date.tm_mday = day;
 
    time(&now_time);//현재 초 단위 시간을 구한다.
    birth_time = mktime(&birth_date);//분할 시각을 초 단위 시간으로 변환
    gap_time = now_time - birth_time; //시간 차이를 구함(초)
 
    //살아온 일 계산
    day = (int)gap_time / SECONDS_PER_DAY;
    gap_time = gap_time%SECONDS_PER_DAY;
    //살아온 시 계산
    hour = (int)gap_time / SECONDS_PER_HOUR;
    gap_time = gap_time%SECONDS_PER_HOUR;
    //살아온 분 계산
    min = (int)gap_time / SECONDS_PER_MIN;
    //살아온 초 계산
    second = (int)gap_time%SECONDS_PER_MIN;
 
    localtime_s(&now_date, &now_time);//초 단위 값을 지역 시각(DateTime)을 구한다.     
    asctime_s(buf, sizeof(buf), &now_date);//현재 시각을 버퍼에 출력
    printf("오늘은 %s", buf);//현재 시각 출력
    //살아온 일, 시, 분, 초 출력
    printf("오늘까지 살아온 시간은 %d일 %d시 %d분 %d초\n", day, hour, min, second);
 
    return 0;
}
