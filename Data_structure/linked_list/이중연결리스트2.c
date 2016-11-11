#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 
typedef void * Element;
 
typedef struct Node//노드 정의
{
    Element data;//데이터
    struct Node *next;//링크(다음 노드의 위치 정보)
    struct Node *prev;//링크(이전 노드의 위치 정보)
}Node;
 
Node *NewNode(Element data)//노드 생성
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
 
 
typedef struct Data//테스트에서 리스트에 보관할 데이터 형식
{
    int num;
    char *name;
}Data;
 
Data *NewData(int num, const char *name)//데이터 동적 생성
{
    Data *data = (Data *)malloc(sizeof(Data));
    data->num = num;
    data->name = (char *)malloc(strlen(name) + 1);
    strcpy_s(data->name, strlen(name) + 1, name);
    return data;
}
void DeleteData(Data *data)//데이터 동적 소멸
{
    free(data->name);
    free(data);
}
void ViewData(Data *data)//데이터 정보 출력
{
    printf("%-5d %-10s\n", data->num, data->name);
}
 
typedef int(*IsEqual)(Element e1);//비교 알고리즘
typedef void(*View)(Element e1);//출력 알고리즘
typedef void(*Dispose)(Element e1);//소멸 알고리즘
 
List *NewList();//리스트 동적 생성
void DeleteList(List *list, Dispose dispose);//리스트 소멸
void AddData(List *list, Element data);//데이터 추가
void Remove(List *list, Node *now, Dispose dispose);//노드 삭제
Node *Find(List *list, IsEqual isequal);//노드 검색
void ViewAll(List *list, View view);//전체 출력
void Clear(List *list, Dispose dispose);//해제
 
 
void AlgoDeleteData(Element elem)//데이터 동적 소멸 래퍼
{
    DeleteData((Data *)elem);
}
void AlgoViewData(Element elem)//데이터 정보 출력 래퍼
{
    ViewData((Data *)elem);
}
 
int find_num; //검색할 번호
int AlgoEqual(Element e1)//검색 알고리즘
{
    Data *data = (Data *)e1;
    return find_num == data->num;
 
}
int main(void)
{
    List *list = NewList();
    {//추가  테스트를 위한 블록
        AddData(list, NewData(3, "홍길동")); //3
        AddData(list, NewData(6, "강감찬")); //3, 6
        AddData(list, NewData(4, "을지문덕")); //3, 6, 4
        AddData(list, NewData(9, "이순신")); //3, 6, 4, 9
        ViewAll(list, AlgoViewData);// 3 4 6 9 출력
    }
 
    {//삭제 테스트를 위한 블럭
 
        Node *seek;
        find_num = 4;
        seek = Find(list, AlgoEqual);
        if (seek)
        {
            printf("4를 보관한 노드를 찾았음\n");
            Remove(list, seek, AlgoDeleteData); //3 6 9
            printf("4를 보관한 노드 제거 후\n");
            ViewAll(list, AlgoViewData);// 3 6 9 출력
        }
    }
    Clear(list, AlgoDeleteData);//전체 해제
    printf("전체 해제 후\n");
    ViewAll(list, AlgoViewData);// 아무것도 출력하지 않음
    DeleteList(list, AlgoDeleteData);//리스트 해제
    return 0;
}
void InitList(List *list);//초기화
List *NewList()
{
    List *list = (List *)malloc(sizeof(List));//리스트 동적 메모리 할당
    InitList(list);//리스트 초기화
    return list;
}
void DeleteList(List *list, Dispose dispose)
{
    Clear(list, dispose);//자료를 보관한 모든 노드를 제거
    free(list->head);//맨 앞의 더미 노드 제거
    free(list->tail);//맨 뒤의 더미 노드 제거
    free(list);//리스트 제거
}
void InitList(List *list)
{
    list->head = NewNode(NULL);//연결 리스트의 맨 앞에 더미 노드 생성
    list->tail = NewNode(NULL);//연결 리스트의 맨 뒤에 더미 노드 생성
    list->head->next = list->tail;//head의 다음은 tail로 설정
    list->tail->prev = list->head;//tail의 다음은 head로 설정
    list->count = 0;//보관한 데이터 개수를 0으로 설정   
}
void AddData(List *list, Element data)
{
    //새로 생성한 노드를 tail앞에 매답니다.
    Node *now = NewNode(data);//새로운 노드 생성
    now->prev = list->tail->prev;//now의 prev를 tail 앞 노드로 설정
    now->next = list->tail;//now의 next를 tail로 설정
    list->tail->prev->next = now;//tail의 이전 노드의 next를 now로 설정
    list->tail->prev = now;//tail의 prev를 now로 설정
    list->count++;//보관한 데이터 개수를 1 증가
}
 
void Remove(List *list, Node *now, Dispose dispose)
{
    now->prev->next = now->next;//이전 노드의 next를 now의 다음 노드로 설정
    now->next->prev = now->prev;//다음 노드의 prev를 now의 이전 노드로 설정
    dispose(now->data);
    free(now);
    list->count--;//보관한 노드 개수를 1 감소
}
 
Node *Find(List *list, IsEqual isequal)
{
    //head와 tail은 더미 노드입니다.
    Node *seek = list->head->next;//head의 next부터 검색합니다.
    while (seek != list->tail) //seek가 tail이 아니면
    {
        if (isequal(seek->data))//찾았을 때
        {
            return seek;
        }
        seek = seek->next;//seek를 다음으로 이동
    }
    return NULL;//못 찾았을 때
}
 
void ViewAll(List *list, View view)
{
    //head와 tail은 더미 노드입니다.
    Node *seek = list->head->next;//head->next 부터 출력합니다.
    int i = 0;
    printf("보관한 데이터 개수: %d\n", list->count);
 
    while (seek != list->tail) //seek가 참이면(NULL 이 아니면)
    {
        i++;
        view(seek->data);
 
        if (i % 5 == 0)//5의 배수일 때
        {
            printf("\n");//개행
        }
        seek = seek->next;//seek를 다음으로 이동
    }
    printf("\n");
}
 
void Clear(List *list, Dispose dispose)
{
    //head 다음 노드가 tail이 아닐 때까지 리스트에서 제거
    Node *seek = list->head->next;
    while (seek != list->tail) //seek가 참이면(NULL 이 아니면)
    {
        Remove(list, seek, dispose);
        seek = list->head->next;
    }
}
