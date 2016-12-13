//파일의 소문자, 대문자, 숫자문자, 공백, 라인, 기타문자 개수 출력
#include <stdio.h>
#include <stdlib.h>
enum CHAR_TYPE
{
    ETC,LITTLE, BIG, DIGIT,SPACE, LINE,MAX_TYPE
};
const char *ct_strs[MAX_TYPE]={"기타문자","소문자","대문자","숫자문자","공백문자","라인"};
void ReadAndPrint(const char *fname);
int main(void)
{
    char fname[200];
 
    printf("파일 이름: ");
    //공백을 포함한 파일 이름 입력할 때 gets_s(fname,sizeof(fname));
    scanf_s("%s",fname,sizeof(fname));
 
    ReadAndPrint(fname);
    return 0;
}
int Distinction(char ch);
void ReadAndPrint(const char *fname)
{
    FILE *fp;
    char ch;
    int ct;
    int cnts[MAX_TYPE]={0};
    //fp = fopen(fname,"r")과 fopen_s(&fp,fname,"r")는 같은 기능 수행
    fopen_s(&fp,fname,"r");//읽기 모드로 파일 열기
  
    if(fp == NULL)
    {
        perror("파일 열기 실패");//에러 출력
        exit(0); //프로그램 종료
    }
 
    while(1)//무한 반복
    {
        ch = fgetc(fp);//하나의 문자 읽기
        if(feof(fp))//파일의 끝이면
        {
            break;
        }
        ct = Distinction(ch);//문자 종류 판별
        cnts[ct]++;//판별한 문자 종류 개수 1 증가
        printf("%c",ch);//하나의 문자를 읽어와서 콘솔 화면에 출력
    }
 
    fclose(fp);//파일 스트림 닫기
    printf("\n==%s 내용==\n",fname);
    for(ct=0;ct<MAX_TYPE; ct++)
    {
        printf("%10s: %d 개\n",ct_strs[ct], cnts[ct]);
    }
  
}
int Distinction(char ch)
{
    if((ch>='0')&&(ch<='9'))
    {
        return DIGIT;
    }
    if((ch>='a')&&(ch<='z'))
    {
        return LITTLE;
    }
    if((ch>='A')&&(ch<='Z'))
    {
        return BIG;
    }
    if(ch == ' ')
    {
        return SPACE;
    }
    if(ch == '\n')
    {
        return LINE;
    }
    return ETC;
}
