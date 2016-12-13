
//큰 수 사이의 덧셈
#include<stdio.h>
#include <string.h>
int main(void)
{
    char buf1[101];
    char buf2[101];
    char numstr1[101];
    char numstr2[101];
    char result[102] = "";
    int i;
    int sum, carry = 0;
 
    printf("첫 번째 수:");
    scanf_s("%s", buf1, sizeof(buf1));
    sprintf_s(numstr1, sizeof(numstr1), "%0100s", buf1);
 
    printf("두 번째 수:");
    scanf_s("%s", buf2, sizeof(buf2));
    sprintf_s(numstr2, sizeof(numstr2), "%0100s", buf2);
 
 
    for (i = 99; i >= 0; i--)
    {
        sum = (numstr1[i] - '0') + (numstr2[i] - '0') + carry;
        carry = sum / 10;
        sum = sum % 10;
        result[i + 1] = sum + '0';
    }
    result[0] = carry + '0';
    for (i = 0; result[i] == '0'; i++);
    printf("%s\n",buf1);
    printf("+\n");
    printf("%s \n", buf2);
    printf("= \n");
    printf("%s\n",result + i);
    printf("\n");
    return 0;
}
