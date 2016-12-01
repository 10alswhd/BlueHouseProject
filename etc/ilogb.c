#include <math.h>
#include <stdio.h>
int main(void)
{
    double value = 1.0;
    int i;
    for (i = 0; i < 10; i++)
    {
        value *= 2.0;
        printf("ilogb(%.f) = %d \n",value, ilogb(value));
    }
 
    return 0;
}
