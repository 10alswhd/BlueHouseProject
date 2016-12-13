//회원 구조체 배열을 파일에 출력 및 로딩
#include <stdio.h>
#include <stdlib.h>
#define FNAME "data.txt"
 
typedef struct Member
{
    int num;
    char name[200];
    char addr[200];
}Member;
 
 
void StoreData()
{
    Member arr[5]=
    {
        {1,"홍길동","서울특별시 종로구 종로 1가 1번지"},
        {6,"강감찬","서울특별시 종로구 종로 1가 2번지"},
        {12,"이순신","서울특별시 종로구 종로 1가 3번지"},
        {8,"을지문덕","서울특별시 종로구 종로 1가 4번지"},
        {9,"한석봉","서울특별시 종로구 종로 1가 5번지"},
    };
    FILE *fp;
    int n=5;
 
    //쓰기 모드로 파일을 열면 파일의 내용은 사라집니다.
    //만약 파일이 없으면 새로 생성합니다.
    //fp = fopen(fname,"w")과 fopen_s(&fp,fname,"w")는 같은 기능 수행
    fopen_s(&fp,FNAME,"w");//파일 쓰기 모드로 열기
  
    if(fp == NULL)
    {
        perror("파일 열기 실패");//에러 출력
        exit(0); //프로그램 종료
    }
  
    fwrite(&n,sizeof(int),1,fp);//기록할 회원 수 출력
    fwrite(arr,sizeof(Member),n,fp);//회원 데이터 출력
  
    fclose(fp);
}
void LoadData()
{
    Member arr[5];
    FILE *fp;
    int n;
    int i;
 
    //fp = fopen(fname,"r")과 fopen_s(&fp,fname,"r")는 같은 기능 수행
    fopen_s(&fp,FNAME,"r");//파일 쓰기 모드로 열기
  
    if(fp == NULL)
    {
        perror("파일 열기 실패");//에러 출력
        exit(0); //프로그램 종료
    }
  
    fread(&n,sizeof(int),1,fp);//회원 수 읽기
    fread(arr,sizeof(Member),n,fp);//회원 데이터 읽기
  
  
    fclose(fp);
 
    printf("회원 수: %d\n",n);
    for(i=0;i<n;i++)
    {
        printf("번호:%d 이름:%s 주소:%s\n",arr[i].num,arr[i].name,arr[i].addr);      
    }
 
}
int main(void)
{
    StoreData();
    LoadData();  
    return 0;
}
