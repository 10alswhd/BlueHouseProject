#include <math.h>
#include <stdio.h>
int main(void)
{
    printf("%f\n", scalbn(1.0, 1));
    printf("%f\n", scalbn(1.0, 3));
    printf("%f\n", scalbn(2.0, 1));
    printf("%f\n", scalbn(2.0, 3));
    return 0;
}
