#pragma warning(disable:4996)
#include <string.h>
#include <stdio.h>
 
char *ehstrncat(char *dest, const char *source,size_t n)
{
    int len = strlen(dest);//dest 문자열 길이 계산
    strncpy(dest + len, source,n);//dest+len 위치에 source 문자열 복사
    dest[len + n] = 0;//합한 문자열 끝에 종료 문자 대입
    return dest;//dest 반환
}
 
void main (void)
{
    char stra[100] = "1234";
    char strb[10]="56789";
    char strc[100] = "1234";
    char strd[10] = "56789";
 
    //strncat 함수 이용
    printf("%s에 %s의 %d개 문자를 합하면 ", stra, strb, 2);
    printf("%s\n", strncat(stra, strb, 2));
    //ehstrncat 함수 이용
    printf("%s에 %s의 %d개 문자를 합하면 ", strc, strd, 2);
    printf("%s\n", ehstrncat(strc, strd, 2));
}
 
