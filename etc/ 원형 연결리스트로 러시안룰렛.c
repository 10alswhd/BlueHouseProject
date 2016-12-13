//원형 연결리스트로 러시안룰렛
//주석을 살펴보세요.막코딩입니다.
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
typedef struct _Node {
    int bullet;//총알(1:장전, 0:없음)
    struct _Node *next;
}Node;
void Game(); //게임
void MakeRoulette(Node **head, int n); //권총 약실이 n개인 러시안 룰렛 생성
void ClearRoulette(Node **head); //러시안 룰렛 지우기
int main()
{
    int key;
    srand((unsigned)time(0));//랜덤에 사용할 seed값 설정
    while (1)
    {
        printf("=== 러시안 룰렛 게임 ===\n");
        printf("계속하려면 1, 게임을 끝내려면 0\n");
        scanf_s("%d", &key);//게임 진행 여부 입력
        if (key == 0)//0을 입력
        {
            break;//반복문 탈출
        }
        Game();//게임
    }
    return 0;
}
void Game()
{
    int n;
    int choice;
    Node *head;
    printf("참가 인원: ");
    scanf_s("%d", &n);//게임 참가 인원 입력
    MakeRoulette(&head, n);//참가 인원만큼의 러시안 룰렛 생성
    while (1)
    {
        printf("발사? Yes:1 or No:0\n");
        scanf_s("%d", &choice);//발사 여부 입력
        if (choice == 1)//발사를 선택할 때
        {
            if (head->bullet)//총알이 있을 때
            {
                printf("빵~\n");
                printf("Game Over!!!\n");
                ClearRoulette(&head);//러시안 룰렛 지우기
                return;//반복문 탈출(게임 종료)
            }
            else//없다면
            {
                head = head->next;//다음으로 이동
            }
        }
        else//발사를 선택하지 않았다면
        {
            head = head->next;//다음으로 이동
        }
    }
}
void MakeNode(Node **head, int bullet)
{
    Node *now = (Node *)malloc(sizeof(Node));
    now->bullet = bullet;
    if ((*head) == NULL)//빈 상태
    {
        (*head) = now;//맨앞이 now
        now->next = now;//현재 now 하나여서 now->next도 now
    }
    else//비어있지 않음
    {
        //(*head)와 (*head) 다음 노드 사이에 now를 연결
        now->next = (*head)->next;
        (*head)->next = now;
    }
}
void MakeRoulette(Node **head, int n)
{
    int value = rand() % n + 1; //value에 1~n 사이의 랜덤한 수 발생
    (*head) = NULL;//리스트의 맨 앞은 NULL로 초기화
    while (n>0)//만들 개수가 0보다 클 때
    {
        if (value == n)//check와 n이 같으면
        {
            MakeNode(head, 1);//총알을 장전한 노드 생성
        }
        else//아니면
        {
            MakeNode(head, 0);//총알을 장전하지 않은 노드 추가
        }
        n--;
    }
}
void ClearRoulette(Node **head)
{
    Node *seek = (*head)->next;//(*head)의 다음 노드로 초기화
    Node *prev = (*head);//seek의 앞 노드를 (*head)로 설정
    while (seek != (*head))//seek가 (*head)가 아니면 반복
    {
        prev = seek;       //seek를 이동하기 전에 prev에 설정
        seek = seek->next;//seek를 다음 노드로 이동
        free(prev); //설정했던 seek의 앞 노드를 제거
    }
    free(*head);//마지막으로 (*head)노드를 제거
}
