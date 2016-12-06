#include <stdio.h>
 
//테스트를 위해 400kbytes 크기의 구조체 정의
typedef struct {
    char buf[400000];
}BigData;
 
int main (void)
{
    FILE * fp;
    fpos_t offset;
    int i;
    BigData bigdata={'a'};
 
    fopen_s (&fp,"data.txt","wb");//쓰기 모드로 파일 열기
    if (fp==NULL)
    {
        perror ("error fopen");
        return 0;
    }
 
    //출력 파일 스트림에 400kbytes 데이터를 10000번 출력
    for(i=0;i<10000;i++)
    {
        fwrite(&bigdata,sizeof(BigData),1,fp);
    }   
   
    fgetpos(fp,&offset);//파일 스트림의 파일 position 확인
    printf("%lld\n",offset);    //파일 positon 출력
   
    fclose (fp);//출력 파일 스트림 닫기
    return 0;
}
