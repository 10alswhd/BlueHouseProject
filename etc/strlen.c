#include <stdio.h>
 
int mystrlen(const char *str);
int main(void)
{
    char name[100] = "Hello World";
    printf("%s\n", name);
    printf("길이: %d\n", mystrlen(name));
    return 0;
}
 
int mystrlen(const char *str)
{
    int cnt;
    //str[cnt]가 거짓 문자(종료 문자, '\0')가 나올 때까지 cnt를 1증가
    for (cnt = 0; str[cnt]; cnt++);
    return cnt;
}
