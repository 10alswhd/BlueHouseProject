#include <math.h>
#include <stdio.h>
int main(void)
{
    double x;
    for (x = 1.0; x <= 10.0; x += 1.0)
    {
        printf("acosh(%f)=%f\n", x, acosh(x));
    }
    return 0;
}
 
