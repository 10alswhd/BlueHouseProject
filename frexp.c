#include <math.h>
#include <stdio.h>
 
int main(void)
{
    double value;
    double exp;
    float expf;
    long double expl;
    int mantissa;
 
    value = 1.0;
    exp = frexp(value, &mantissa);
    printf("%f = %f*2^%d \n", value, exp, mantissa);
 
    value = 2.0;
    exp = frexp(value, &mantissa);
    printf("%f = %f*2^%d \n", value, exp, mantissa);
 
    value = 4.0;
    exp = frexp(value, &mantissa);
    printf("%f = %f*2^%d \n", value, exp, mantissa);
 
    value = 0.5;
    exp = frexp(value, &mantissa);
    printf("%f = %f*2^%d \n", value, exp, mantissa);
 
    value = 3.5;
    exp = frexp(value, &mantissa);
    printf("%f = %f*2^%d \n", value, exp, mantissa);
 
    value = 0.1;
    exp = frexp(value, &mantissa);
    expf = frexpf((float)value, &mantissa);
    expl = frexpl(value, &mantissa);
    printf("frexp  함수 사용: %f = %.30f*2^%d \n", value, exp, mantissa);
    printf("frexpf 함수 사용: %f = %.30f*2^%d \n", value, expf, mantissa);
    printf("frexpl 함수 사용: %f = %.30f*2^%d \n", value, expl, mantissa);
    return 0;
}
