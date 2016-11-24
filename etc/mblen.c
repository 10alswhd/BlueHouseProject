#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    int  i;
    int len;
    char *str = "기억나abc나비야";
    wchar_t wc;
 
    setlocale(LC_ALL, "Korean");//로케일 설정
    for (i = 0; i < strlen(str);i++)
    {
        len = mblen(str+i, MB_CUR_MAX);//유니코드로 변환할 때 차지하는 바이트 수
        if (len == 1)
        {
            printf("<%c:%d> ", str[i], len);
        }
        if (len == 2)
        {
            mbtowc(&wc, str + i, 2);//유니코드 문자로 변환
            printf("<%lc:%d> ", wc, len);
            i++;
        }
    }   
    printf("\n");
    return 0;
}
