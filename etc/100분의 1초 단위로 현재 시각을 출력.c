//100분의 1초 단위로 시각을 출력
#pragma warning(disable:4996)//4996경고 메시지 출력 해제
#include <time.h>//clock,time,localtime
#include <stdio.h> //printf
#include <conio.h>//kbhit
#include <Windows.h>//SetConsoleCursorPostion
 
void print_time(struct tm *now, int tail)
{
    COORD CursorPosition = { 0,1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
 
    //현재 시각을 출력
    printf("%2d시 %2d분 %2d초 %2d\n",
        now->tm_hour, now->tm_min, now->tm_sec, tail);
}
int main(void)
{
    clock_t sclock, nclock;//sclock:시작, nclock:현재(1/1000초 시간)
    time_t seconds; //초단위 시각
    struct tm *now; //date time 시각   
    int tail = 0;
    printf("종료를 원하시면 아무키나 누르세요.\n");
    sclock = clock();//시작 clock을 구합니다.
    time(&seconds);//초단위 시각을 구합니다.
    now = localtime(&seconds);//date time 시각을 구합니다.
    print_time(now, tail); //현재 시간을 출력
    while (1)
    {
        if (kbhit())//키를 누르면
        {
            break;//반복문 탈출
        }
        nclock = clock();
        if (nclock - sclock >= (CLOCKS_PER_SEC / 100))//clock/100초와 크거나 같으면
        {
            tail++;
            if (tail == 100)//1초가 지나면
            {
                tail = 0;
                sclock = clock();
                time(&seconds);//초단위 시각을 구합니다.
                now = localtime(&seconds);//date time 시각을 구합니다.
            }
            print_time(now, tail); //현재 시간을 출력
        }
    }
    printf("프로그램을 종료합니다.\n");
    return 0;
}
