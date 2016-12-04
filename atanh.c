#include <math.h>
#include <stdio.h>
int main(void)
{
    double x;
    for (x = 0.0; x < 1.0; x += 0.1)
    {
        printf("atanh(%f)=%f\n", x, atanh(x));
        printf("atanh(%f)=%f\n", -x, atanh(-x));
    }
    x -= 0.1;
    printf("last x: %.25f -x: %.25f\n", x, -x);
    printf("atanh(%.25f)=%f\n", -1.0, atanh(-1.0));
    printf("atanh(%.25f)=%f\n", 1.0, atanh(1.0));
    return 0;
}
 
