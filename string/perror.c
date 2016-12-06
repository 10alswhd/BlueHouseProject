#include <stdio.h>
int main (void)
{
    FILE * fp;
 
    fopen_s (&fp,"noexist.txt","r");//읽기 모드로 파일 열기
    if (fp==NULL)
    {
        perror ("error fopen");//에러 메시지 출력
        return 0;
    }   
    fclose (fp);  
    return 0;
}
