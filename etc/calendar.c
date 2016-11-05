 
#include <stdio.h>
 
int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
const char *wname[7] = { "일","월","화","수","목","금","토" };
const char *bars[2] = //데코레이션 바
{
    "=====================================================\n",
    "-----------------------------------------------------\n"
};
int DrawMonth(int month, int start);//달 출력(달(0~11), 시작요일:0~6), 반환값은 다음 달 시작요일
 
int main(void)
{
    int year, start;
    int i = 0;
    printf("몇 년: ");
    scanf_s("%d", &year);//년도 입력
 
    printf("1월 1일은 몇 번째 요일(일요일은 0): ");
    scanf_s("%d", &start);//1월 1일의 요일 입력
 
    if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))//윤년 판단
    {
        days[1] = 29;//2월달의 날 수를 29로 설정
    }
 
    printf("[ %d년 ]\n", year);
 
    for (i = 0; i<12; i++)
    {
        start = DrawMonth(i, start);
    }
    return 0;
}
 
int DrawMonth(int month, int start)
{
    int i = 0;
    printf(" << %d 월>>\n", month + 1);//달 출력
    printf(bars[0]);//데코레이션 바 출력
    for (i = 0; i<7; i++)//요일 출력
    {
        printf("%7s", wname[i]);//폭을 7로 설정
    }
    printf("\n");
    printf(bars[1]);//데코레이션 바 출력
    for (i = 0; i<start; i++)//첫 주 시작일까지 공백 출력
    {
        printf("%7s", " ");//폭을 7로 설정
    }
    for (i = 0; i<days[month]; i++)//일 출력
    {
        printf("%7d", i + 1);//폭을 7로 설정
        start++;
        if (start == 7)//요일이 7이면
        {
            start = 0;//0으로 변경
            printf("\n");//개행 출력
        }
    }
    printf("\n");//개행 출력
    printf(bars[0]);//데코레이션
    return start;//다음 달 시작 요일 반환
}
