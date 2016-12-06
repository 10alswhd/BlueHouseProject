#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    char src[100]="123.45abcd";
    char *pos=NULL;
    double value=0;
    value = strtod(src,&pos);//실수 부분을 추출
    printf("value is %.2f\n",value);//추출한 값 출력
    printf("%s\n",pos);//나머지 부분도 출력
    return 0;
}
