#pragma warning(disable:4996)
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    char *str = "기억나abc나비야";
    wchar_t warr[100] = L"";
 
    setlocale(LC_ALL, "Korean");//로케일 설정
    mbstowcs(warr, str, 100);
    wprintf(L"%s\n", warr);//유니코드 문자열 출력
    return 0;
}
 
