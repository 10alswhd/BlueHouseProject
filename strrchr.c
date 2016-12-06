#include <string.h>
#include <stdio.h>
 
const char *ehstrrchr(const char *str, int ch)
{
    int i;
    int len = strlen(str);//문자열 길이 계산
 
    for (i = len - 1; i >= 0; i--)//문자열의 뒤쪽에서 앞쪽으로 이동하면서 반복
    {
        if (str[i] == ch)//같은 문자를 찾았을 때(i>=0)
        {
            break;//반복문 탈출
        }
    }
 
    if (i>=0)//찾았을 때
    {
        return str+i;//찾은 위치 반환
    }
    return NULL;
}
 
int main (void)
{
    char str[100] = "12345abcde54321";   
    const char *cp;
 
    //strrchr 함수 이용
    printf("%s 뒤에서부터 %c을(를) 처음 발견한 위치\n",str,'5');
    cp = strrchr(str,'5');
  
    if(cp)
    {
        printf("%d번째 %s\n", cp - str + 1, cp);       
    }
    else
    {
        printf("없음\n");
    }
 
    //ehstrrchr 함수 이용
    printf("%s 뒤에서부터 %c을(를) 처음 발견한 위치\n", str, '3');
    cp = ehstrrchr(str, '3');
    if (cp)
    {
        printf("%d번째 %s\n", cp - str + 1,cp);       
    }
    else
    {
        printf("없음\n");
    }
    return 0;
}
