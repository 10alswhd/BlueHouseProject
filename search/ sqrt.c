#include <stdio.h>
#include <stdlib.h>

#define PRECISION 0.0000001
#define POW2(x) x * x
#define ABS(x) x > 0 ? x : -x

#define TEST(VALUE, EXPECT) {\
    printf("testing: %0.4f expecting %0.4f", VALUE, EXPECT);\
    if (ABS(_sqrt(VALUE) - EXPECT) <= PRECISION)\
        printf("\n PASSED!\n");\
    else printf("\n FAIL %0.4f is not equal of %0.4f\n", _sqrt(VALUE), EXPECT);\
}


double _sqrt(double number)
{
    double start = 0, end = number, middle = 0;
    double guess_result = start;
    while ((end - start) > PRECISION)
    {
        middle = (start + end) / 2.0;
        guess_result = POW2(middle);

        if (guess_result == number)
        {
            return middle; // exact result
        }
        else if (guess_result < number)
        {
            start = middle;
        }
        else // guess_result > number
        {
            end = middle;
        }
    }
    // in case of not exact match, return the most near number as possible
    // due to PRECISION
    return middle;
}

int main(){
    TEST(0.0, 0.0)
    TEST(1.0, 1.0)
    TEST(9.0, 3.0)
    TEST(16.0, 4.0)
    TEST(1.520, 1.2328828005937953)
    TEST(3.0, 1.7320508075688772);
}
