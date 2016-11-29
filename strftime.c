#include <locale.h>
#include <time.h>
#include <stdio.h>
int main(void)
{
    time_t now;
    struct tm now_tm;
    char buf[256];
 
    setlocale(LC_ALL, "Korean");//지역을 한국으로 설정
    time(&now);
    localtime_s(&now_tm, &now);
 
    strftime(buf, sizeof(buf), "%Y년 %m월 %d일 %p %I:%M:%S", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%x %X", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%Y년 %m월 %d일 %H:%M:%S", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%y년 %m월 %d일 %H:%M:%S", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%y년 %m월 %d일 %a %H:%M:%S", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%y년 %m월 %d일 %A %H:%M:%S", &now_tm);
    puts(buf);
 
    setlocale(LC_ALL, "US");   
    strftime(buf, sizeof(buf), "%x %X", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%x %X %a", &now_tm);
    puts(buf);
    strftime(buf, sizeof(buf), "%x %X %A", &now_tm);
    puts(buf);
    return 0;
}
