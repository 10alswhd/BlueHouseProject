#include  <stdio.h>
#include  <math.h>
#pragma warning(disable:4996)
 
int  main(void)
{
    double  a, b, c, d, e;
 
    printf("이차방정식 ax^2+bx+c=0\n");
    printf("a: ");
    scanf("%lf", &a);
 
    printf("b: ");
    scanf("%lf", &b);
 
    printf("c: ");
    scanf("%lf", &c);
 
    if (a == 0)
    {
        printf("x = %f \n", -c / b);
    }
    else
    {
        d = b*b - 4.0*a*c;//판별식
        if (d>0)
        {
            e = sqrt(d);
            printf("두 개의 근: %f, %f \n", (-b + e) / (2.0*a), (-b - e) / (2.0*a));
        }
        else
        {
            if (d == 0)
            {
                printf("한 개의 근: %f \n", (-b) / (2.0*a));
            }
            else
            {
                printf("근이 없습니다.(허근)\n");
            }
        }
    }
    return  0;
}
