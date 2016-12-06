#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    long long a, b;
    lldiv_t dt;
 
    printf("피젯수: ");
    scanf_s("%lld",&a);
    printf("젯수: ");
    scanf_s("%lld",&b);
   
    dt= lldiv(a,b);
    printf("몫: %lld 나머지: %lld\n",dt.quot, dt.rem);
    return 0;
}
 
