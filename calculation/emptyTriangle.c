#include <stdio.h>
int main(void)
{
    int n;
    int line, space, star;
 
    printf("높이:");
    scanf_s("%d", &n);//입력
    for (space = 1; space <= (n - 1); space++)//공백 = n-line
    {
        putchar(' ');
    }
    putchar('*');//별1
    putchar('\n');//개행
    for (line = 1; line <= (n - 2); line++)//line: 1~(n-2)
    {
        for (space = 1; space <= (n - line - 1); space++) //공백 = n-line-1
        {
            putchar(' ');
        }
        putchar('*');//별1
        for (space = 1; space <= 2 * line - 1; space++) //공백 = 2*line-1
        {
            putchar(' ');
        }
        putchar('*');//별1
        putchar('\n');//개행=1
    }
    for (star = 1; star <= (2 * n - 1); star++)//별 = 2*n -1
    {
        putchar('*');
    }
    putchar('\n');//개행
    return 0;
}
