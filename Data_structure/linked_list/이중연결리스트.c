//이중 연결리스트 - 정렬 상태로 보관
//연결리스트 정의, 노드 정의, 초기화, 추가, 삭제, 검색, 전체 출력, 해제
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node//노드 정의
{
    int data;//데이터
    struct Node *next;//링크(다음 노드의 위치 정보)
    struct Node *prev;//링크(이전 노드의 위치 정보)
}Node;
 
Node *NewNode(int data)
{
    Node *now = (Node *)malloc(sizeof(Node));
    now->data = data;
    now->prev = now->next = NULL;
    return now;
}
 
typedef struct List//연결리스트 정의
{
    Node *head;
    Node *tail;
    int count;
}List;
void InitList(List *list);//초기화
void AddData(List *list, int data);//데이터 추가
void Remove(List *list, Node *now);//노드 삭제
Node *Find(List *list, int data);//노드 검색
void ViewAll(List *list);//전체 출력
void Clear(List *list);//해제
 
int main(void)
{
    List list;
    {//초기화 및 추가 테스트를 위한 블록
        InitList(&list);
        AddData(&list, 3); //3
        AddData(&list, 6); //3 6
        AddData(&list, 5); //3 5 6
        AddData(&list, 8); //3 5 6 8
        AddData(&list, 1); //1 3 5 6 8
        ViewAll(&list);// 1 3 5 6 8 출력
    }
 
    {//검색과 삭제 테스트를 위한 블록
        Node *seek = Find(&list, 5);
        if (seek)
        {
            printf("5를 보관한 노드를 찾았음\n");
            Remove(&list, seek); //1 3 6 8
            printf("5를 보관한 노드 제거 후\n");
            ViewAll(&list);// 1 3 6 8 출력
        }
    }
    Clear(&list);//전체 해제
    printf("전체 해제 후\n");
    ViewAll(&list);// 아무것도 출력하지 않음
 
    return 0;
}
 
void InitList(List *list)
{
    list->head = NewNode(0);//연결 리스트의 맨 앞에 더미 노드 생성
    list->tail = NewNode(0);//연결 리스트의 맨 뒤에 더미 노드 생성
    list->head->next = list->tail;//head의 다음은 tail로 설정
    list->tail->prev = list->head;//tail의 다음은 head로 설정
    list->count = 0;//보관한 데이터 개수를 0으로 설정   
}
 
Node *FindSeat(List *list, int data);
void AddData(List *list, int data)
{
    //새로 생성한 노드를 tail앞에 매답니다.
    Node *now = NewNode(data);//새로운 노드 생성
 
    Node *pos = FindSeat(list, data);
 
    now->prev = pos->prev;//now의 prev를 pos의 앞 노드로 설정
    now->next = pos;//now의 next를 pos로 설정
    pos->prev->next = now;//pos의 이전 노드의 next를 now로 설정
    pos->prev = now;//poos의 prev를 now로 설정
    list->count++;//보관한 데이터 개수를 1 증가
}
Node *FindSeat(List *list, int data)
{
    Node *seek = list->head->next;//head의 next부터 검색합니다.
    while (seek != list->tail) //seek가 tail이 아니면
    {
        if (seek->data >= data)//찾았을 때
        {
            break;//반복문 탈출
        }
        seek = seek->next;//seek를 다음으로 이동
    }
    return seek;
}
 
void Remove(List *list, Node *now)
{
    now->prev->next = now->next;//이전 노드의 next를 now의 다음 노드로 설정
    now->next->prev = now->prev;//다음 노드의 prev를 now의 이전 노드로 설정
    free(now);//노드 소멸
    list->count--;//보관한 노드 개수를 1 감소
}
 
Node *Find(List *list, int data)
{
    //head와 tail은 더미 노드입니다.
    Node *seek = list->head->next;//head의 next부터 검색합니다.
    while (seek != list->tail) //seek가 tail이 아니면
    {
        if (seek->data == data)//찾았을 때
        {
            return seek;
        }
        seek = seek->next;//seek를 다음으로 이동
    }
    return NULL;//못 찾았을 때
}
 
 
void ViewAll(List *list)
{
    //head와 tail은 더미 노드입니다.
    Node *seek = list->head->next;//head->next 부터 출력합니다.
    int i = 0;
    printf("보관한 데이터 개수: %d\n", list->count);
 
    while (seek != list->tail) //seek가 참이면(NULL 이 아니면)
    {
        i++;
        printf("[%2d]:%-05d ", i, seek->data);
 
        if (i % 5 == 0)//5의 배수일 때
        {
            printf("\n");//개행
        }
        seek = seek->next;//seek를 다음으로 이동
    }
    printf("\n");
}
 
void Clear(List *list)
{
    //head 다음 노드가 tail이 아닐 때까지 리스트에서 제거
    Node *seek = list->head->next;
    while (seek != list->tail) //seek가 참이면(NULL 이 아니면)
    {
        Remove(list, seek);
        seek = list->head->next;
    }
}
