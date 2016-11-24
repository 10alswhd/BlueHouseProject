//C언어 표준 라이브러리 함수 사용법 가이드
//system 함수 테스트 용 타겟
//프로그램 이름 : target.exe
 
#include <stdio.h>
 
int main(void)
{
    printf("타겟\n");
    return 3;
}
 
사용 예
//C언어 표준 라이브러리 함수 사용법 가이드
//int system(const char *cmd); 시스템 명령 수행
//메모장을 수행 후에 타겟 응용을 수행
 
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    int re;
    re = system("notepad");
    printf("notepad return: %d\n",re);
    re = system("target");
    printf("target return: %d\n",re);
 
    return 0;
}
