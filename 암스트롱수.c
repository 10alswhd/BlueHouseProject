
//암스트롱의 수
//abc = a*a*a + b*b*b + c*c*c
#include <stdio.h>
 
int IsAmstrong(int num);
int main(void)
{
    int num = 0;
    printf("암스트롱의 수 abc = a*a*a + b*b*b + c*c*c\n");
    for (num = 100; num <= 999; num++)
    {
        if (IsAmstrong(num))
        {
            printf("%3d ", num);
        }
    }
    printf("\n");
    return 0;
}
 
int IsAmstrong(int num)
{
    int num2 = num;
    int sum = 0;
    while (num2>0)
    {
        sum += (num2 % 10)*(num2 % 10)*(num2 % 10);
        num2 = num2 / 10;
    }
    return sum == num;
}
