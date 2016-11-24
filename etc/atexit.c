#include <stdlib.h>
#include <stdio.h>
 
void EndFuncA(void);
void EndFuncB(void);
void EndFuncC(void);
void Test(void);
 
int main(void)
{
    atexit(EndFuncA);//프로그램 종료할 때 수행할 EndFuncA 함수 등록
    atexit(EndFuncB);//프로그램 종료할 때 수행할 EndFuncB 함수 등록
    atexit(EndFuncC);//프로그램 종료할 때 수행할 EndFuncC 함수 등록
 
    Test();
    printf("Here is main\n");
 
    return 0;
}
void EndFuncA(void)
{
    printf("Here is EndFuncA\n");
}
void EndFuncB(void)
{
    printf("Here is EndFuncB\n");
}
void EndFuncC(void)
{
    printf("Here is EndFuncC\n");
}
void Test(void)
{
    printf("Test 1\n");
    exit(0);//프로그램 종료
    printf("Test 2\n");
}
