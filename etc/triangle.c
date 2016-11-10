#include <stdio.h>
int main(void)
{
    int n;
    int line, space, star;
    printf("삼각형 높이:");
    scanf_s("%d", &n);//입력
    for (line = 0; line < n; line++)//n개 라인
    {
        for (space = 0; space < (n - line); space++)//공백 n-line개
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
