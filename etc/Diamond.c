#include <stdio.h>
int main(void)
{
    int n;
    int line, space, star;
 
    printf("정수:");
    scanf_s("%d", &n);//입력
    for (line = 0; line < n; line++)//line: 0~n-1
    {
        for (space = 0; space <(n - line-1); space++)//공백 n-line-1개
        {
            putchar(' ');
        }
        for (star = 0; star < (2 * line + 1); star++)//별 2*line +1개
        {
            putchar('*');
        }
        putchar('\n');//개행
    }
    for (line = n - 2; line >= 0; line--)//line:n-2 ~ 0
    {
        for (space = 0; space < (n - line-1); space++)//공백 n-line-1개
        {
            putchar(' ');
        }
        for (star = 0; star < (2 * line + 1); star++)//별 2*line +1개
        {
            putchar('*');
        }
        putchar('\n');//개행
    }
    return 0;
}
