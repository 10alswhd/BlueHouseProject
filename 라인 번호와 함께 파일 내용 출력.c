//input.txt 파일의 내용을 라인 번호와 함께 output.txt파일에 출력
#include <stdio.h>
#include <stdlib.h>
#define INPUT_FNAME "input.txt"
#define OUTPUT_FNAME "output.txt"
 
int main(void)
{
    FILE *fp,*fp2;
    char buf[4096];
    int line=0;
    //fp = fopen(fname,"r")과 fopen_s(&fp,fname,"r")는 같은 기능 수행
    fopen_s(&fp,INPUT_FNAME,"r");//읽기 모드로 파일 열기
  
    if(fp == NULL)
    {
        perror("input.txt 파일 열기 실패");//에러 출력
        exit(0); //프로그램 종료
    }
 
    //쓰기 모드로 파일을 열면 파일의 내용은 사라집니다.
    //만약 파일이 없으면 새로 생성합니다.
    //fp = fopen(fname,"w")과 fopen_s(&fp,fname,"w")는 같은 기능 수행
    fopen_s(&fp2,OUTPUT_FNAME,"w");//쓰기 모드로 파일 열기
    if(fp == NULL)
    {
        perror("output.txt 파일 열기 실패");//에러 출력
        exit(0); //프로그램 종료
    }
 
 
    while(!feof(fp))//파일의 끝을 만나지 않았다면 반복
    {
        line++;
        fgets(buf,sizeof(buf),fp);
      
        fprintf(fp2,"%3d: %s",line,buf);//하나의 문자를 읽어와서 파일 스트림에 출력
    }
 
    fclose(fp);//파일 스트림 닫기
    fclose(fp2);//파일 스트림 닫기
    return 0;
}
