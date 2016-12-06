 
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    char src[100] = "1234567890 123456789abcdef 16 1111111111111111111111111111111111111111";
    char *pos = NULL;
    unsigned long long value1 = 0, value2 = 0, value3 = 0, value4 = 0;
 
    value1 = strtoll(src, &pos, 10);//10진수로 계산
    value2 = strtoll(pos, &pos, 16);//16진수로 계산
    value3 = strtoll(pos, &pos, 8);//8진수로 계산
    value4 = strtoll(pos, &pos, 2); //2진수로 계산
    printf("%llu %llu %llu %llu\n", value1, value2, value3, value4);
 
    return 0;
}
