
#include <math.h>
#include <stdio.h>
int main(void)
{
    double x;
    for (x = -5.0; x <= 5.0; x += 1.0)
    {
        printf("asinh(%f)=%f\n", x, asinh(x));
    }
    return 0;
}
 
