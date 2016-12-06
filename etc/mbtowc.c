#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
int main(void)
{
    int  i,j;
    int len;
    int slen;
    char *str = "기억나abc나비야";
    wchar_t warr[100]=L"";
    wchar_t wc;
 
    setlocale(LC_ALL, "Korean");//로케일 설정
    slen = strlen(str);//문자열 길이 계산
    for (i = 0,j=0; i < slen; i++)
    {
        len = mblen(str + i, MB_CUR_MAX);//유니코드로 변환할 때 차지하는 바이트 수       
        mbtowc(&wc, str + i, len);//유니코드 문자로 변환
        warr[j] = wc;//유니코드 배열에 설정
        if (len == 2)//유니코드로 변환할 때 차지하는 바이트가 2일 때
        {
            i++;//i를 1 더 증가
        }               
        j++;
    }   
    wprintf(L"%s\n",warr);//유니코드 문자열 출력
    return 0;
}
