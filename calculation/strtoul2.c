 
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    char src[100] = "123 ff 16 1001";
    char *pos = NULL;
    unsigned long value1 = 0, value2 = 0, value3 = 0, value4 = 0;
 
    value1 = strtol(src, &pos, 10);//10진수로 계산
    value2 = strtol(pos, &pos, 16);//16진수로 계산
    value3 = strtol(pos, &pos, 8);//8진수로 계산
    value4 = strtol(pos, &pos, 2); //2진수로 계산
    printf("%lu %lu %lu %lu\n", value1, value2, value3, value4);
 
    return 0;
}
