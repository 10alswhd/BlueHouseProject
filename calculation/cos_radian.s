#include <math.h>
#include <stdio.h>
 
int main(void)
{
    double radian;
    radian = 0.0;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("cos(%f)  = %.30f\n", radian, cos(radian));
    printf("cosf(%f) = %.30f\n", radian, cosf((float)radian));
    printf("cosl(%f) = %.30f\n", radian, cosl(radian));
 
    radian = 30 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("cos(%f)  = %.30f\n", radian, cos(radian));
    printf("cosf(%f) = %.30f\n", radian, cosf((float)radian));
    printf("cosl(%f) = %.30f\n", radian, cosl(radian));
 
    radian = 45 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("cos(%f)  = %.30f\n", radian, cos(radian));
    printf("cosf(%f) = %.30f\n", radian, cosf((float)radian));
    printf("cosl(%f) = %.30f\n", radian, cosl(radian));
 
    radian = 60 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("cos(%f)  = %.30f\n", radian, cos(radian));
    printf("cosf(%f) = %.30f\n", radian, cosf((float)radian));
    printf("cosl(%f) = %.30f\n", radian, cosl(radian));
 
    radian = 90 * 3.141592 / 180;
    printf("%f 도\n", radian * 180 / 3.141592);
    printf("cos(%f)  = %.30f\n", radian, cos(radian));
    printf("cosf(%f) = %.30f\n", radian, cosf((float)radian));
    printf("cosl(%f) = %.30f\n", radian, cosl(radian));
 
    return 0;
}
}
