#include <stdio.h>
 
int main(void)
{
    int n;
    int line, space, star;
 
    printf("높이:");
    scanf_s("%d", &n);//입력
 
    for (line = 1; line <= 2 * n; line++)//line: 1~2n
    {
        if (line <= n)//line is 1~n
        {
            for (space = 1; space <= (4 * n - 1 - line); space++)//공백 4*n - 1 - line개
            {
                putchar(' ');
            }
            for (star = 1; star <= (2 * line - 1); star++)//별 2*line -1개
            {
                putchar('*');
            }
            putchar('\n');//개행
        }
        else//line is n+1 ~ 2n
        {
            for (space = 1; space <= (2 * n - line); space++)//공백 2n-line개
            {
                putchar(' ');
            }
            for (star = 1; star <= 2 * (line - n) - 1; star++)//별 2*(line-n)-1개
            {
                putchar('*');
            }
            for (space = 1; space <= (2 * (2 * n - line)); space++)//공백 2*(2*n-line) 개
            {
                putchar(' ');
            }
            for (star = 1; star <= (2 * line - 1); star++)//별 2*line-1개
            {
                putchar('*');
            }
            for (space = 1; space <= (2 * (2 * n - line)); space++)//공백 2*(2*n-line) 개
            {
                putchar(' ');
            }
            for (star = 1; star <= 2 * (line - n) - 1; star++)//별 2*(line-n)-1개
            {
                putchar('*');
            }
            putchar('\n');//개행
        }
    }
    return 0;
}
