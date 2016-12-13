#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int Palindrome(char str[]);
int main()
{
    char test_str[5][100] =
    {
        "HannaH",//회문인 예
        "ReliefpfeileR",//회문인 예
        "Root",//회문이 아닌 예
        "RotoR",//회문인 예
        "RentneR"//회문인 예
    };
    int i = 0;
    for (i = 0; i<5; i++)//5번 테스트
    {
        if (Palindrome(test_str[i]))//회문이 맞으면
        {
            printf("%s 는 회문임\n", test_str[i]);
        }
        else//회문이 아니면
        {
            printf("%s 는 회문이 아님\n", test_str[i]);
        }
 
    }
    return 0;
}
int Palindrome(char str[])
{
    int len = 0;
    int i = 0;
    //거짓인 문자(널문자)가 나올때까지 이동
    for (len = 0; str[len]; len++); //len = strlen(str); 과 같은 코드입니다.
    for (i = 0; i<(len / 2); i++)//i를 0~len/2까지 이동하면서 반복
    {
        if (str[i] != str[len - i - 1])//str[i]와 str[len-i-1]이 서로 다르면
        {
            return 0;//회문이 아니므로 0 반환
        }
    }
    return 1;//회문이므로 1 반환 
}
