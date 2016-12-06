#pragma warning(disable:4996)
#include <string.h>
#include <stdio.h>
 
char *ehstrcat(char *dest, const char *source)
{
    int len = strlen(dest);//dest 문자열 길이 계산
    strcpy(dest + len, source);//dest+len 위치에 source 문자열 복사
    return dest;//dest 반환
}
void main (void)
{
    char stra[100] = "1234";
    char strb[10]= "56789";
    char strc[100] = "1234";
    char strd[10] = "abcd";
   
    //strcat 함수 이용
    printf("%s + %s =", stra, strb);
    printf("%s\n", strcat(stra,strb));
 
    //ehstrcat 함수 이용
    printf("%s + %s =", strc, strd);
    printf("%s\n", ehstrcat(strc, strd));
}
