#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
int main(void )
{
    wchar_t wstr[]=L"abc가나다123";
    char str[100];
    int last;
       
    setlocale(LC_ALL, "Korean");//로케일 설정
    last = wcstombs(str,wstr, 100);//유니코드 스트링을 멀티바이트 스트링으로 변환
    str[last]=0;//종료 문자열 설정
    printf("%s\n",str);
    return 0;
}
