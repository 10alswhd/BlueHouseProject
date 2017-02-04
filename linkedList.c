#include "stdafx.h"
         #include "stdlib.h"
         #include "memory.h"
        #include "string.h"

        typedef struct Friend //친구 구조체 정의
        {
              char name[30];//이름
              int num; //번호
	      int birth; //생일
              struct Friend *next;
              struct Friend *prev;
        } Friend;

        Friend *head, *tail;

void Initialize(); //초기화
void Menu(); //메뉴
void Exit(); //종료하기 전에 할당한 메모리 해제

int _tmain(int argc, _TCHAR* argv[])
{
    Initialize(); //초기화
    Menu(); //메뉴
    Exit();//종료하기 전에 할당한 메모리 해제
    return 0;
}

void Initialize()
{
    head = (Friend *)malloc(sizeof(Friend));//더미 노드 생성
    tail = (Friend *)malloc(sizeof(Friend));//더미 노드 생성
    head->next = tail;//맨 앞 더미노드 next를 tail로 설정
    tail->prev = head;//맨 뒤 더미노드 prev를 head로 설정
    head->prev = tail->next = NULL;
}

int SelectMenu();//메뉴 출력 및 선택
void AddFriend();//친구 데이터 입력
void RemoveFriend();//친구 데이터 삭제
void FindFriend();//친구 검색
void ViewStuData(Friend *stu);//친구데이터 가리키기

void Menu() //메뉴
{
    int key = 0;
    while ((key = SelectMenu()) != 0)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: AddFriend(); break; //친구데이터입력
        case 2: RemoveFriend(); break; //친구데이터삭제
        case 3: FindFriend(); break; //친구검색
        default: printf("잘못 선택하였습니다.\n"); break;
        }
    }
    printf("프로그램 종료\n");
}

int SelectMenu() //메뉴출력 및 선택
{
    int key = 0;
    printf("생일 관리 프로그램\n");
    printf("1: 친구 데이터 입력 2: 친구 데이터 삭제 3: 친구 검색 0: 종료\n");
    scanf_s("%d", &key);
	system("cls"); //화면지우기
    return key;
}

void AddFriend() //친구데이터입력
{
    int num = 0;
    int birth = 0;
    Friend *stu = 0;

    printf("추가할 학생 번호: ");
    scanf_s("%d", &num);

    stu = (Friend *)malloc(sizeof(Friend));//학생 구조체 동적 메모리 할당    
    stu->num = num;
    printf("이름: ");
    scanf_s("%s", stu->name, sizeof(stu->name));

	//stu->birth = birth; 앞에 달면 0이 들어감!! 주의하기!!
        printf("생일 : ");
	scanf_s("%d", &birth);
	stu->birth = birth; // <--입력받고나서 넣어야함!!
	printf("\n");

    //새로 생성한 노드를 tail 앞에 매달기
    stu->next = tail;
    stu->prev = tail->prev;
    tail->prev->next = stu;
    tail->prev = stu;
}

void RemoveFriend() //친구데이터삭제
{
    int num;
    Friend *seek;
    printf("삭제할 친구 번호: ");
    scanf_s("%d", &num);

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        if (seek->num == num)
        {
            //연결리스트에서 링크 조절
            seek->prev->next = seek->next;
            seek->next->prev = seek->prev;
            free(seek);//메모리 해제
            printf("삭제하였습니다.\n");
            return;
        }
    }
    printf("데이터가 없습니다.\n");
}
void FindFriend() //친구검색
{
    int num = 0;
    Friend *seek = 0;
    printf("검색할 친구 번호: ");
    scanf_s("%d", &num);

    for (seek = head->next; seek != tail; seek = seek->next)
    {
        if (seek->num == num)
        {
            ViewStuData(seek);
			printf("\n");
            return;
        }
    }
    printf("데이터가 없습니다.\n");
}
void ViewStuData(Friend *stu)
{
    printf("%3d %4s ", stu->num, stu->name);
    printf("%4d \n", stu->birth);
}
void Exit() //종료전에 할당한 메모리해제
{
    Friend *seek = head;

    while (seek->next)
    {
        seek = seek->next;
        free(seek->prev);
    }
    free(seek);
}     
