#include <math.h>
#include <stdio.h>
 
int main(void)
{
    double radian;
    radian = 0.0;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("sin(%f)  = %.30f\n", radian, sin(radian));
    printf("sinf(%f) = %.30f\n", radian, sinf((float)radian));
    printf("sinl(%f) = %.30f\n", radian, sinl(radian));
 
    radian = 30 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("sin(%f)  = %.30f\n", radian, sin(radian));
    printf("sinf(%f) = %.30f\n", radian, sinf((float)radian));
    printf("sinl(%f) = %.30f\n", radian, sinl(radian));
 
    radian = 45 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("sin(%f)  = %.30f\n", radian, sin(radian));
    printf("sinf(%f) = %.30f\n", radian, sinf((float)radian));
    printf("sinl(%f) = %.30f\n", radian, sinl(radian));
 
    radian = 60 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("sin(%f)  = %.30f\n", radian, sin(radian));
    printf("sinf(%f) = %.30f\n", radian, sinf((float)radian));
    printf("sinl(%f) = %.30f\n", radian, sinl(radian));
 
    radian = 90 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("sin(%f)  = %.30f\n", radian, sin(radian));
    printf("sinf(%f) = %.30f\n", radian, sinf((float)radian));
    printf("sinl(%f) = %.30f\n", radian, sinl(radian));
 
    return 0;
}
