#include <stdio.h>
 
#define MAX_NAME_LEN    20
typedef struct {
    char name[MAX_NAME_LEN + 1];
    int age;
}Member;
 
#define MAX_MEMBERS 10
int main(void)
{
    FILE * fp;
    int n;
    fpos_t pos;
    Member members[MAX_MEMBERS] =
    {
        { "홍길동",20 },{ "강감찬",15 },{ "을지문덕",22 },{ "이순신",19 },{ "김구",30 },
        { "안중근",30 },{ "박찬호",35 },{ "김연아",17 },{ "아이유",20 },{ "주니엘",20 }
    };
    Member member;
 
 
    fopen_s(&fp, "data.txt", "wb");//쓰기 모드로 파일 열기
    if (fp == NULL)
    {
        perror("error fopen");
        return 0;
    }
    //출력 파일 스트림에 회원 정보 출력
    if (fwrite(members, sizeof(Member), MAX_MEMBERS, fp) != MAX_MEMBERS)
    {
        printf("출력 오류\n");
        return 0;
    }
    fclose(fp);//출력 파일 스트림 닫기
 
 
    printf("회원 순서 번호 입력(1~%d)  : ", MAX_MEMBERS);
    scanf_s("%d", &n);//조회할 회원 순서 번호 입력
    if ((n<1) || (n>MAX_MEMBERS))//순서 번호가 범위를 벗어날 때
    {
        printf("입력 오류\n");
        return 0;
    }
 
    fopen_s(&fp, "data.txt", "rb");//읽기 모드로 파일 열기
    if (fp == NULL)
    {
        perror("error fopen");
        return 0;
    }
    pos = sizeof(Member)*(n - 1);
    fsetpos(fp, &pos);//파일 position 이동
    fread(&member, sizeof(Member), 1, fp);  //회원 데이터 읽기
    printf("이름: %s 번호: %d\n", member.name, member.age);//회원 데이터 출력
 
    fclose(fp);//입력 파일 스트림 닫기
    return 0;
}
