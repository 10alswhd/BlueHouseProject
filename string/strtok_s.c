#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
 
char * ehstrtok_s(char * str, const char * delimeters,char **context)
{
    static char *pos = NULL;
    static char buffer[256];
    int len, len2;
    int i, j;
 
    if (str)//입력 인자가 NULL이 아니면
    {
        pos = str;//pos에 설정
        *context = str;
    }
    *context = pos;
    len = strlen(pos);//pos으l 문자열 길이 계산
    len2 = strlen(delimeters);//delimeters 문자열 길이 계산
 
    //delimeters와 다른 문자가 나올 때까지 반복
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len2; j++)
        {
            if (pos[i] == delimeters[j])//pos[i]와 delimeters[j]가 같으면
            {
                break;//반복문 탈출(j<len2)
            }
        }
        if (j == len2)//같은 것이 없으면
        {
            break;//반복문 탈출
        }
    }
    if (str && i)//str이 참이고 i가 참(앞부분에 delimeters에 속한 문자가 있을 때
    {
        memcpy(str, str + i,strlen(str+i)+1);//delimeters와 다른 문자로 시작하게 복사
    }
    else
    {
        pos += i;//delimeters와 다른 문자 위치로 이동
        *context += i;//delimeters와 다른 문자 위치로 이동
    }
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len2; j++)
        {
            if (pos[i] == delimeters[j])//pos[i]와 delimeters[j]가 같으면
            {
                break;//반복문 탈출(j<len2)
            }
        }
        if (j < len2)//delimeters에 같은 문자가 있으면
        {
            if (str)
            {
                str[i] = 0;
                *context += (i+1);
            }
            strncpy(buffer, pos, i);//부분 문자열 복사
            buffer[i] = 0;//종료 문자 대입
            pos = pos + i + 1;//pos 위치는 다음으로 이동
           
            return buffer;//복사한 문자열 반환
        }
    }
    return NULL;
}
int main(void)
{
    char str[200] = "나는 집에  간다. 그리고, C언어로 프로그램을 작성한다. 화이팅! 언제나 휴일";
    char str2[200] = "다시 한 번 테스트! 이번에는 ehstrtok 함수 사용.";
    char *delimeters = " ,.!";
    char * pos;
    char *context;
 
    printf("원본: %s\n", str);
    //strtok_s 함수 이용
    printf("== 공백이나 콤마, 느낌표, 마침표를 기준으로 분할 ==\n");
    pos = strtok_s(str, delimeters,&context);  //처음 호출 시에 대상 문자열 전달
    while (pos != NULL)
    {
        printf("%s\n", pos);
        pos = strtok_s(context, delimeters,&context);//이 후 NULL 혹은 context 전달
    }
    printf("원본: %s\n", str2);
    //ehstrtok_s 함수 이용
    printf("== 공백이나 콤마, 느낌표, 마침표를 기준으로 분할 ==\n");
    pos = ehstrtok_s(str2, delimeters,&context);//처음 호출 시에 대상 문자열 전달
    while (pos != NULL)
    {
        printf("%s\n", pos);
        pos = ehstrtok_s(context, delimeters, &context);//이 후 NULL 혹은 context 전달
    }
    return 0;
}
 
