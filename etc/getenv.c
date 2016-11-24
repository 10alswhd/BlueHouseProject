 
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    //시스템에 따라 환경 변수 이름은 다를 수 있습니다.
    printf("컴퓨터 이름:%s\n",getenv("COMPUTERNAME"));
    printf("CPU 개수:%s\n",getenv("NUMBER_OF_PROCESSORS"));
 
    return 0;
}
