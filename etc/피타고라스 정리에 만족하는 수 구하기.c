
//피타고라스 정리에 만족하는 a,b,c
#include <stdio.h>
int main(void)
{
    int a = 0, b = 0, c = 0;
    printf(" a  b  c \n");
    for (a = 1; a <= 50; a++)
    {
        for (b = 1; b <= 50; b++)
        {
            for (c = 1; c <= 50; c++)
            {
                if ((a*a) + (b*b) == (c*c))
                {
                    printf("%2d %2d %2d\n", a, b, c);
                }
            }
        }
    }
    return 0;
}
