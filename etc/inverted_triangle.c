#include <stdio.h>
int main(void)
{
    int n;
    int line, space, star;
 
    printf("삼각형의 높이:");
    scanf_s("%d", &n);//입력
 
    for (line = 0; line<n; line++)//n개 라인
    {
        for (space = 0; space<line; space++)//공백 line개
        {
            putchar(' ');
        }
        for (star = 0; star<2 * (n - line) - 1; star++)//별 2*(n-line)-1개
        {
            putchar('*');//별 출력
        }
        putchar('\n');//개행
    }
    return 0;
}
