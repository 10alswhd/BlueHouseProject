#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    int a, b;
    div_t dt;
 
    printf("피젯수: ");
    scanf_s("%d",&a);
    printf("젯수: ");
    scanf_s("%d",&b);
    dt= div(a,b);
 
    printf("몫: %d 나머지: %d\n",dt.quot, dt.rem);
    return 0;
}
