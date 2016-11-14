#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
char *encrypt(char *dest, const char *src, const char *key);
char *decrypt(char *dest, const char *encryptstr, const char *key);
int main(void)
{
    char source[100] = "Welcome! Here is ehclub.net";
    char en_str[100];
    char de_str[100];
 
    printf("source: %s\n", source);
    encrypt(en_str, source, "hello");
    printf("encrypted: %s\n", en_str);
    decrypt(de_str, en_str, "hello");
    printf("decrypted: %s\n", de_str);
 
    return 0;
}
 
char *encrypt(char *dest, const char *src, const char *key)
{
    char *origin;
    int len = strlen(key);
    int cnt = 0;
    for (origin = dest; *src; dest++, src++)//종료 문자를 만날 때까지 반복
    {
        if (isupper(*src))//대문자일 때
        {
            //(key[cnt]-'a')칸 밀기
            *dest = (*src - 'A' + (key[cnt] - 'a')) % 26 + 'A';
        }
        if (islower(*src))//소문자일 때
        {
            //(key[cnt]-'a')칸 밀기
            *dest = (*src - 'a' + (key[cnt] - 'a')) % 26 + 'a';
        }
        if (isdigit(*src))//숫자 문자일 때
        {
            //(key[cnt]-'a')칸 밀기
            *dest = (*src - '0' + (key[cnt] - 'a')) % 10 + '0';//3칸 밀기(0->3)
        }
        if (isalnum(*src) == 0)
        {
            *dest = *src;
        }
        cnt = (cnt + 1) % len;
    }
    *dest = '\0';
    return origin;
}
char *decrypt(char *dest, const char *encryptstr, const char *key)
{
    char *origin;
    int len = strlen(key);
    int cnt = 0;
    for (origin = dest; *encryptstr; dest++, encryptstr++)//종료 문자를 만날 때까지 반복
    {
        if (isupper(*encryptstr))//대문자일 때
        {
            //(26 -(key[cnt] - 'a'))칸 밀기 => (key[cnt]-'a')칸 당기기
            *dest = (*encryptstr - 'A' + (26 - (key[cnt] - 'a'))) % 26 + 'A';
        }
        if (islower(*encryptstr))//소문자일 때
        {
            //(26 -(key[cnt] - 'a'))칸 밀기 => (key[cnt]-'a')칸 당기기
            *dest = (*encryptstr - 'a' + (26 - (key[cnt] - 'a'))) % 26 + 'a';
        }
        if (isdigit(*encryptstr))//숫자 문자일 때
        {
            //(26 -(key[cnt] - 'a'))칸 밀기 => (key[cnt]-'a')칸 당기기
            *dest = (*encryptstr - '0' + (26 - (key[cnt] - 'a'))) % 10 + '0';
        }
        if (isalnum(*encryptstr) == 0)
        {
            *dest = *encryptstr;
        }
        cnt = (cnt + 1) % len;
    }
    *dest = '\0';
    return origin;
}
