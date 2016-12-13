//성적 관리 프로그램 - 학생 번호 순으로 배열에 보관
//전역 변수로 학생 구조체 배열을 선언
//최대 학생 수는 고정
//입력 오류에 관한 예외 처리 없음
 
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_NLEN    20 //최대 이름 길이
#define MAX_SUBJECT 3 //과목 수
typedef struct {//학생 구조체 정의
    char name[MAX_NLEN + 1];//이름
    int num; //번호
    int scores[MAX_SUBJECT];//국,영,수 성적
}Student;
 
 
const char *stitles[MAX_SUBJECT] = { "국어","영어","수학" };
 
#define MAX_STUDENT 10//최대 학생 수
 
Student stues[MAX_STUDENT];
 
void Initialize();//학생 데이터 초기화
void Run();
int main(void)
{
 
    Initialize();//학생 데이터 초기화
    Run();
 
    return 0;
}
 
 
void Initialize()
{
    int i = 0;
    int s = 0;
 
    for (i = 0; i<MAX_STUDENT; i++)
    {
        for (s = 0; s<MAX_SUBJECT; s++)
        {
            stues[i].scores[s] = -1; //성적을 -1로 설정
        }
    }
}
 
int SelectMenu();//메뉴 출력 및 선택
void AddStudent();//학생 데이터 입력
void RemoveStudent();//학생 데이터 삭제
void FindStudent();//학생 검색
void ListStudent();//목록 보기
void Run()
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: AddStudent(); break;
        case 2: RemoveStudent(); break;
        case 3: FindStudent(); break;
        case 4: ListStudent(); break;
        default: printf("잘못 선택하였습니다.\n"); break;
        }
    }
    printf("프로그램 종료\n");
}
 
int SelectMenu()
{
    int key = 0;
    printf("성적 관리 프로그램 0:종료\n");
    printf("1: 학생 데이터 입력 2: 학생 데이터 삭제 3: 학생 검색 4: 목록 보기 \n");
    scanf_s("%d", &key);
    return key;
}
 
int IsAvailNum(int num);//유효한 번호인지 판별
int IsAvailScore(int score);//유효한 성적인지 판별
void AddStudent()
{
    int num = 0;
    Student *stu = 0;
    int s = 0;
 
    printf("추가할 학생 번호(1~%d): ", MAX_STUDENT);
    scanf_s("%d", &num);
 
    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 학생 번호입니다.\n");
        return;
    }
 
    if (stues[num - 1].num)//이미 번호를 설정한 상태일 때
    {
        printf("이미 추가하였습니다\n");
        return;
    }
 
    //stues에는 1번 학생 데이터를 관리하는 메모리 주소
    //따라서 stues+(num-1)은 num번 학생 데이터를 관리하는 메모리 주소
    stu = stues + (num - 1);
    stu->num = num;
    printf("이름: ");
    scanf_s("%s", stu->name, sizeof(stu->name));
 
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        printf("%s 성적:", stitles[s]);
        scanf_s("%d", stu->scores + s);
 
        if (IsAvailScore(stu->scores[s]) == 0)//유효한 성적이 아닐 때
        {
            stu->scores[s] = -1;
            printf("입력한 성적이 유효하지 않아서 %s 성적은 입력 처리하지 않았습니다.\n", stitles[s]);
        }
    }
}
int IsAvailNum(int num)
{
    return (num >= 1) && (num <= MAX_STUDENT);
}
int IsAvailScore(int score)
{
    return (score >= 0) && (score <= 100);
}
void RemoveStudent()
{
    int num = 0;
    Student *stu = 0;
    int s = 0;
 
    printf("삭제할 학생 번호(1~%d): ", MAX_STUDENT);
    scanf_s("%d", &num);
 
    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 학생 번호입니다.\n");
        return;
    }
 
    if (stues[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("데이터가 없습니다.\n");
        return;
    }
 
    stu = stues + (num - 1);
    strcpy_s(stu->name, sizeof(stu->name), "");
    stu->num = 0;
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        stu->scores[s] = -1;
    }
 
    printf("삭제하였습니다.\n");
}
void ViewStuData(Student *stu);
void FindStudent()
{
    int num = 0;
    Student *stu = 0;
    int s = 0;
 
    printf("검색할 학생 번호(1~%d): ", MAX_STUDENT);
    scanf_s("%d", &num);
 
    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 학생 번호입니다.\n");
        return;
    }
 
    if (stues[num - 1].num == 0)//번호를 설정한 상태가 아닐 때
    {
        printf("데이터가 없습니다.\n");
        return;
    }
 
    stu = stues + (num - 1);
    ViewStuData(stu);
}
void ViewStuData(Student *stu)
{
    int i = 0;
    int s = 0;
 
    printf("%4d %10s ", stu->num, stu->name);
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        printf("%4d ", stu->scores[s]);
    }
    printf("\n");
}
void ListStudent()
{
    int i = 0;
    int s = 0;
 
    printf("%4s %10s ", "번호", "이름");
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        printf("%4s ", stitles[s]);
    }
    printf("성적이 -1인 곳은 미입력\n");
 
    for (i = 0; i<MAX_STUDENT; i++)
    {
        if (stues[i].num)
        {
            ViewStuData(stues + i);
        }
    }
}
