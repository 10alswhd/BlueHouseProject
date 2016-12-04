#include <math.h>
#include <stdio.h>
int main(void)
{
    double x;
    for (x = 0; x <= 5.0; x += 1.0)
    {
        printf("cosh(%f)=%f\n", x, cosh(x));
        printf("cosh(%f)=%f\n", -x, cosh(-x));
    }
    return 0;
}
