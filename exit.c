#include <stdlib.h>
#include <stdio.h>
 
void EndFunc(void);
int main(void)
{
    int i;
 
    _set_abort_behavior( 0, _WRITE_ABORT_MSG);//abort 함수 호출하였을 때 오류 창 뜨지 않게 설정   
    atexit(EndFunc);//프로그램 종료할 때 수행할 EndFunc 함수 등록
 
    printf("1을 입력하면 정상 종료\n");
    scanf_s("%d",&i);
 
    if(i==1)
    {
        exit(0);//정상 종료
    }
    abort();//비정상 종료
    printf("Here is main\n");//도달하지 않음
 
    return 0;
}
void EndFunc(void)
{
    printf("Here is EndFunc\n");
}
