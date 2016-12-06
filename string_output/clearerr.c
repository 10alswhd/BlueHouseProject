#include <stdio.h>
int main (void)
{
    FILE * fp;
    int re,no;
    fopen_s (&fp,"data.txt","w");//쓰기 모드로 파일 열기
    if (fp==NULL)
    {
        perror ("error fopen");       
        return 0;
    }
    re = fgetc(fp);//출력 파일 스트림에서 문자 읽기
    if(re == -1)
    {    
        no = ferror(fp);//에러 번호 확인
        printf("errno is %d\n",no);//에러 번호 출력
 
        clearerr(fp);//에러 지우기
        no = ferror(fp);//에러 번호 확인
        printf("errno is %d\n",no);//에러 번호 출력
    }
   
    fclose (fp);
    return 0;
}
