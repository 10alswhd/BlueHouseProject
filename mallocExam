#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 
typedef struct Data Data;
struct Data
{
    int num;
    char *name;
};
Data *NewData(int num, const char *name);//동적으로 Data 생성
void DeleteData(Data *data);//동적으로 생성한 Data 소멸
void DataView(Data *data);//Data 정보 보기
 
typedef struct Queue Queue;
struct Queue
{
    Data **base;//버퍼 주소
    size_t size; //버퍼 크기(큐 용량)
    size_t count; //보관 개수
    size_t front; //꺼낼 인덱스
    size_t rear; //보관할 인덱스
};
 
Queue *NewQueue(size_t size);//동적으로 큐 생성
int QueuePut(Queue *queue, Data *data);//큐에 Data 보관
Data *QueueGet(Queue *queue);//큐에서 Data 꺼냄
void DeleteQueue(Queue *queue);//동적으로 생성한 큐 소멸
 
int main(void)
{
    Data *data = NULL;
    Queue *queue = NewQueue(10);//크기가 10인 큐 생성   
 
    QueuePut(queue,NewData(1, "홍길동"));//큐에 동적으로 Data를 생성하여 보관
    QueuePut(queue,NewData(2, "강감찬"));//큐에 동적으로 Data를 생성하여 보관
    QueuePut(queue,NewData(3, "을지문덕"));//큐에 동적으로 Data를 생성하여 보관
    QueuePut(queue,NewData(4, "이순신"));//큐에 동적으로 Data를 생성하여 보관
    while ((data = QueueGet(queue)) != NULL)//큐에서 꺼낸 것이 NULL이 아니면(비어있지 않다면) 반복
    {
        DataView(data);//Data 정보 보기
        DeleteData(data);//동적으로 생성한 Data 소멸
    }
    DeleteQueue(queue);//동적으로 생성한 큐 소멸
    return 0;
}
 
Data *NewData(int num, const char *name)
{
    //구조체 Data 크기 1개를 동적으로 메모리 할당
    Data *data = (Data *)malloc(sizeof(Data));
    //입력받은 name 문자열 길이+1 크기 1개를 동적으로 메모리 할당
    data->name = (char *)malloc(strlen(name) + 1);
    //문자열 복사
    strcpy_s(data->name, strlen(name) + 1, name);
    data->num = num;//번호 설정
    return data;//동적으로 할당한 메모리 반환
}
 
void DeleteData(Data *data)
{
    //자신의 내부에 동적으로 생성한 메모리 해제 후에 자신을 해제합니다.
    free(data->name);//동적으로 할당한 name 메모리 해제
    free(data);//동적으로 할당한 data 메모리 해제
}
 
void DataView(Data *data)
{
    printf("이름: %s 번호:%d\n", data->name, data->num);
}
 
Queue *NewQueue(size_t size)
{
    //구조체 Queue 크기 1개를 동적으로 메모리 할당
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    //Data * 크기 size 개를 동적으로 메모리 할당
    queue->base = (Data **)malloc(sizeof(Data *)*size);
    queue->size = size;//큐의 용량 설정
    queue->front = queue->rear = 0;//큐의 보관할 위치와 꺼낼 위치를 0으로 설정
    queue->count = 0;//큐에 보관한 원소 개수를 0으로 설정   
    return queue;//동적으로 생성한 queue 반환
}
 
int QueuePut(Queue *queue, Data *data)
{
    if (queue->count == queue->size)//꽉찼을 때
    {
        return 0;//보관 실패
    }
    queue->base[queue->rear] = data;//base의 rear 인덱스에 data 보관
    queue->rear = (queue->rear+1)%queue->size;//rear 위치를 이동(회전)   
    queue->count++;//보관 개수 1 증가
    return 1;//보관 성공
}
 
Data *QueueGet(Queue *queue)
{
    Data *data = NULL;
    if (queue->count == 0)//큐가 비었음
    {
        return NULL;//꺼내기 실패
    }
    data = queue->base[queue->front];//base의 front 인덱스에 원소를 data에 설정
    queue->front = (queue->front+1)%queue->size; //front 위치를 이동(회전)
    queue->count--;//보관 개수 1 감소
    return data;//꺼내기 성공
   
}
 
void DeleteQueue(Queue *queue)
{
    free(queue->base);//동적으로 생성한 base 메모리 해제
    free(queue);//동적으로 생성한 queue 메모리 해제
}
