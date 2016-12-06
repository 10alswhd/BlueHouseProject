#include <stdio.h>
#include <string.h>
 
char *ehstrstr(const char *str1, const char *str2)
{
    int len = strlen(str2);//str2 문자열 길이 계산
    while (*str1)//*str1 이 참인 문자일 때 반복
    {
        if (strncmp(str1, str2,len) == 0)//부분 문자열이 같으면
        {
            break;//반복문 탈출(*str1이 참)
        }
        str1++;//다음 위치로 이동
    }
    if (*str1)//*str1이 참일 때
    {
        return (char *)str1;//찾은 위치 반환
    }
    return NULL;
}
 
int main ()
{
    char str[100] ="안녕하세요. 오늘은 평일입니다.";
    char *pos;
    printf("원본 문자열: %s\n", str);
    pos = strstr (str,"평일");//"평일"이 있는 위치를 탐색
    memcpy(pos,"휴일",strlen("휴일"));//찾은 위치의 내용을 "휴일"로 변경
    puts (str);
 
    pos = ehstrstr(str, "오늘은");//"오늘은"이 있는 위치를 탐색
    memcpy(pos, "언제나", strlen("언제나"));//찾은 위치의  내용을 "언제나"로 변경
    puts(str);
    return 0;
}
