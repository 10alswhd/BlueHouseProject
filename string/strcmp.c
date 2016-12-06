#include <string.h>
#include <stdio.h>
 
int ehstrcmp(const char *str1, const char *str2)
{
    //*str1이 참이면서 *str1과 *str2가 같으면 str1과 str2를 다음 위치로 이동하는 것을 반복
    for (; *str1 && (*str1 == *str2); ++str1, ++str2);
    return *str1 - *str2;//*str1과 *str2의 차이를 반환
}
 
int main (void)
{
    char names[5][20]={"홍길동","강감찬","을지문덕","이순신","유관순"};
    char query[20] = "";
    int i=0,ecount=0;
 
    printf("검색할 이름 : ");
    scanf_s("%s",query,sizeof(query));//검색할 이름 입력
    ecount = sizeof(names)/sizeof(names[0]);//원소의 개수 계산
 
    printf("== strcmp 함수 이용 ==\n");
    for(i=0; i< ecount;i++)
    {
        if(strcmp(names[i],query)==0)//같은 문자열을 찾을 때
        {
            break;//반복문 탈출(i가 ecount보다 작음)
        }
    }
 
    if(i<ecount)//i가 ecount보다 작으면
    {
        printf("인덱스 %d 에 %s 이(가) 있습니다.\n",i, query);//찾은 결과 출력
    }
    else
    {
        printf("%s 는(은) 없습니다.\n",query);
    }
 
    printf("== ehstrcmp 함수 이용 ==\n");
    for (i = 0; i< ecount; i++)
    {
        if (ehstrcmp(names[i], query) == 0)
        {
            break;
        }
    }
    if (i<ecount)
    {
        printf("인덱스 %d 에 %s 이(가) 있습니다.\n", i, query);
    }
    else
    {
        printf("%s 는(은) 없습니다.\n", query);
    }
    return 0;
}
