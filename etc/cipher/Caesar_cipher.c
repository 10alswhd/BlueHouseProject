#include <stdio.h>
#include <ctype.h>
 
char *encrypt(char *dest, const char *src);
char *decrypt(char *dest, const char *encryptstr);
int main(void)
{
    char source[100] = "Welcome! Here is ehclub.net";
    char en_str[100];
    char de_str[100];
 
    printf("source: %s\n", source);
    encrypt(en_str, source);
    printf("encrypted: %s\n", en_str);
    decrypt(de_str, en_str);
    printf("decrypted: %s\n", de_str);
 
    return 0;
}
 
char *encrypt(char *dest, const char *src)
{
    char *origin;
    for (origin = dest; *src; dest++, src++)//종료 문자를 만날 때까지 반복
    {
        if (isupper(*src))//대문자일 때
        {
            *dest = (*src - 'A' + 5) % 26 + 'A';//5칸 밀기('A'->'F')
        }
        if (islower(*src))//소문자일 때
        {
            *dest = (*src - 'a' + 10) % 26 + 'a';//10칸 밀기('a'->'k')
        }
        if (isdigit(*src))//숫자 문자일 때
        {
            *dest = (*src - '0' + 3) % 10 + '0';//3칸 밀기(0->3)
        }
        if (isalnum(*src) == 0)
        {
            *dest = *src;
        }
    }
    *dest = '\0';
    return origin;
}
char *decrypt(char *dest, const char *encryptstr)
{
    char *origin;
    for (origin = dest; *encryptstr; dest++, encryptstr++)//종료 문자를 만날 때까지 반복
    {
        if (isupper(*encryptstr))//대문자일 때
        {
            *dest = (*encryptstr - 'A' + 21) % 26 + 'A';//21칸 밀기('F'->'A')
        }
        if (islower(*encryptstr))//소문자일 때
        {
            *dest = (*encryptstr - 'a' + 16) % 26 + 'a';//16칸 밀기('k'->'a')
        }
        if (isdigit(*encryptstr))//숫자 문자일 때
        {
            *dest = (*encryptstr - '0' + 7) % 10 + '0';//7칸 밀기(3->0)
        }
        if (isalnum(*encryptstr) == 0)
        {
            *dest = *encryptstr;
        }
    }
    *dest = '\0';
    return origin;
}
