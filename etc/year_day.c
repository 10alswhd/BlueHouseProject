#include <stdio.h>
void date(int year, int day);//년도와 일수를 입력하면 년월일 출력
 
int main(void)
{
    int year, day;
    printf("년도와 일수 입력(예:2016 102): ");
    scanf_s("%d %d", &year, &day);
    date(year, day); //year와 day를 입력인자로 전달하여 일 수를 출력
    return 0;
}
 
void date(int year, int day)
{
    int mdays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int month;
    int mday = day;//mday를 day로 설정
    if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))//윤년 판단
    {
        mdays[1] = 29;//2월달의 날 수를 29로 설정
    }
    for (month = 0; mday>mdays[month]; month++)//mday가 mdays[month]보다 크면
    {
        mday -= mdays[month];//mday에 mdays[month]를 빼줍니다.
    }
    //month는 mdays의 인덱스로 사용해서 실제 출력할 때는 1을더해서 출력합니다.
    printf("%d년도의 %d번째 날은 %d월 %d일입니다.\n", year, day, month + 1, mday);
}
