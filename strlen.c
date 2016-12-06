#include <string.h>
#include <stdio.h>
 
size_t ehstrlen(const char *str)
{
    size_t s = 0;
    for (s = 0; str[s]; s++);//거짓인 문자를 만날 때까지 반복
    return s;
}
 
int main (void)
{
    char *str = "hello world";
    char *kstr="안녕하세요.";//한글은 한 개의 글자를 2로 취급
    char name[50] = "abc";
    char name2[50] = "0123456789";
 
    printf("== strlen 함수 이용 ==\n");
    printf("%s 길이 : %d\n", str, strlen(str));
    printf("%s 길이 : %d\n", kstr, strlen(kstr));
    printf("%s 길이 : %d\n", name, strlen(name));
    printf("%s 길이 : %d\n", name2, strlen(name2));
    printf("%s 길이 : %d\n", str+3, strlen(str+3));
 
    printf("\n== ehstrlen 함수 이용 ==\n");
    printf("%s 길이 : %d\n", str, ehstrlen(str));
    printf("%s 길이 : %d\n", kstr, ehstrlen(kstr));
    printf("%s 길이 : %d\n", name, ehstrlen(name));
    printf("%s 길이 : %d\n", name2, ehstrlen(name2));
    printf("%s 길이 : %d\n", str + 3, ehstrlen(str + 3));
    return 0;
}
