#include <stdio.h>
 
int main(void)
{
    double pi = 0;
    int k = 0;
 
    while (k<10000000) //반복문의 횟수가 많을 수록 PI값과 비슷합니다.
    {
        ++k;
        if (k % 2)
        {
            pi += 4.0 / (2.0 * k - 1.0);
        }
        else
        {
            pi -= 4.0 / (2.0 * k - 1.0);
        }
    }
 
    printf("pi = %.15f\n", pi);
    return 0;
}
