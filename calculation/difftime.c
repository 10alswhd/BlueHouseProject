#include <time.h>
#include <stdio.h>
 
int main(void)
{
    struct tm gmt, localt;
    time_t now_time,gm_time;
    char buf[256];
 
    time(&now_time); //현재 초 단위 시간을 측정
    localtime_s(&localt, &now_time);//지역 시각을 구함   
    gmtime_s(&gmt, &now_time);//GMT 시각을 구함
    gm_time = mktime(&gmt);//GMT 시각을 초 단위 시간을 구함
   
    printf("표준시와 지역 시간의 차이: %.f 초\n", difftime(now_time, gm_time));
    return 0;
}
 
