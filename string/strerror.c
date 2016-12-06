#include <stdio.h>
#include <errno.h>
#include <string.h>
 
void ListErrorMsg()
{
    int i = 0;
    char *errmsg;
 
    printf("== Error Message List ==\n");
    for(i=0;i<45;i++)
    {
        errmsg = strerror(i);//에러 메시지 확인
        printf("<%d>:%s\n",i,errmsg);//에러 번호와 에러 메시지 출력
    }
}
 
int main(void)
{
    FILE * fp;
   
    ListErrorMsg();//에러 번호와 에러 메시지 목록 출력
 
    printf("\n없는 파일 읽기 모드로 열었을 때의 에러 메시지 확인하기\n");
    fp = fopen ("noexist.txt","rt");//읽기 모드로 없는 파일 열기
    if (fp == NULL)//파일 스트림이 NULL일 때
    {
        perror("file not existed");//에러 메시지 출력
        printf ("%d: %s\n",errno,strerror(errno));//에러 번호와 에러 메시지 출력
        return 0;
    }
    fclose(fp);
    return 0;
}
