#include <string.h>
#include <stdio.h>
 
int ehstrncmp(const char *str1, const char *str2,size_t n)
{
    n--;//반환하기 전에 ++str1, ++str2 하기 때문에 1을 미리 빼 주어야 합니다.
    //*str1이 참이면서 *str1과 *str2가 같으면 str1과 str2를 다음 위치로 이동하는 것을 반복
    for (; *str1 && (*str1 == *str2) && n; ++str1, ++str2,n--);
    return *str1 - *str2;//*str1과 *str2의 차이를 반환
}
 
int main (void)
{
    char *src="I am a boy. You are a girl.";
    char query[20] = "";
    int i=0,len=0;
 
    printf("검색할 단어 : ");
    scanf_s("%s",query,sizeof(query));
    len = strlen(query);
 
    printf("== strncmp 함수 이용 ==\n");
    for(i=0; i< src[i];i++)
    {
        if(strncmp(src+i,query,len)==0)//같은 위치를 찾았을 때
        {
            break;//반복문 탈출(str[i]는 참)
        }
    }
    if(src[i])//str[i]가 참인 문자일 때
    {
        printf("인덱스 %d 에서 %s 을(를) 발견하였습니다.\n",i, query);
    }
    else
    {
        printf("%s 는(은) 없습니다.\n",query);
    }
 
    printf("== ehstrncmp 함수 이용 ==\n");
    for (i = 0; i< src[i]; i++)
    {
        if (ehstrncmp(src + i, query, len) == 0)//같은 위치를 찾았을 때
        {
            break;//반복문 탈출(str[i]는 참)
        }
    }
    if (src[i])//str[i]가 참인 문자일 때
    {
        printf("인덱스 %d 에서 %s 을(를) 발견하였습니다.\n", i, query);
    }
    else
    {
        printf("%s 는(은) 없습니다.\n", query);
    }
    return 0;
}
