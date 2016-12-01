#pragma warning(disable:4996)
#include <time.h>
#include <stdio.h>
int main(void)
{
    struct tm *gmt, localt;
    time_t now_time;
    char buf[256];
    time(&now_time); //현재 초 단위 시간을 측정
    localtime_s(&localt, &now_time);//지역 시각을 구함
    asctime_s(buf, sizeof(buf), &localt);//지역 시각을 버퍼에 출력
    printf("지역 시각: %s", buf);//지역 시각을 출력
    gmt = gmtime(&now_time);//GMT 시각을 구함
    asctime_s(buf, sizeof(buf), gmt);//GMT 시각을 버퍼에 출력
    printf("GMT 시각: %s", buf);//GMT 시각을 출력
    return 0;
}
