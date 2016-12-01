 
#include <math.h>
#include <stdio.h>
 
int main(void)
{
    double x = 1.0;
    int i = 0;
    for (i = 0; i <= 10;i++)
    {
        printf("exp2(%.1f)  = %f\n", x, exp2(x));
        x += 0.2;
    }
    return 0;
}
