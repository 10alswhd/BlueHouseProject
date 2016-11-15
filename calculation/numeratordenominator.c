include <math.h>
#include <stdio.h>
int main(void)
{
    double numerator, denominator;
    printf("분자와 분모를 입력: ");
    scanf_s("%lf %lf",&numerator, &denominator);
 
    printf("몫: %.lf ",floor(numerator/denominator));
    printf("나머지: %f \n",fmod(numerator, denominator));
    return 0;
}
