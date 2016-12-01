#include <stdio.h>
 
void TestIssAnagram(const char *s1, const char *s2);
int main()
{
    TestIssAnagram("silent","listen");
    TestIssAnagram("gargen","ranged");
    TestIssAnagram("split","lisp");
}
int IsAnagram(const char *s1, const char *s2);
void TestIssAnagram(const char *s1, const char *s2)
{
    printf("=== Test %s %s ===\n",s1,s2);
    if(IsAnagram(s1,s2))
    {
        printf("Result: Anagram\n");
    }
    else
    {
        printf("Result: Is Not Anagram\n");
    }
   
}
int IsAnagram(const char *s1, const char *s2)
{
    int i ,j;
    for(i=0;s1[i];i++)//s1[i] 문자가 참이면(거짓은 종료 문자임) 반복
    {
        for(j=0;s2[j];j++)//s2[j] 문자가 참이면(거짓은 종료 문자임) 반복
        {
            if(s1[i] == s2[j])//s1[i]와 s2[j]가 같으면
            {
                break;//반복문 탈출(s2[j]은 참인 상태임)
            }           
        }
        if(s2[j]==0)//s2[j] 문자가 거짓이면(같은 문자가 없을 때)
        {
            return 0;//anagram이 아님
        }
    }
    return 1;//anagram임
} 
