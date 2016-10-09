#include "stdafx.h"
#include "stdlib.h"
#define cQ_SIZE 100

typedef char element;
typedef struct
{
	element queue[cQ_SIZE];
	int front, rear;
}QueueType;

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ -> front = 0;
	cQ -> rear = 0;
	return cQ;
}

int isEmpty(QueueType *cQ)
{
	if(cQ->front==cQ->rear)
	{
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if(((cQ->rear+1) % cQ_SIZE) == cQ->front)
	{
		printf("Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;
	else
	{
		cQ->rear = (cQ->rear+1)%cQ_SIZE;
		cQ->queue[cQ->rear]=item;
	}
}

element deQueue(QueueType *cQ)
{
	if(isEmpty(cQ)) exit(1);
	else
	{
		cQ->front = (cQ->front+1)%cQ_SIZE;
		return cQ->queue[cQ->front];
	}
}

element peek(QueueType *cQ)
{
	if(isEmpty(cQ)) exit(1);
	else return cQ->queue[(cQ->front+1)%cQ_SIZE];
}

void printQ(QueueType *cQ)
{
	int i, first, last;
	first = (cQ->front+1)%cQ_SIZE;
	last = (cQ->rear+1)%cQ_SIZE;
	printf("Circular Queue : [");
	i = first;
	while(i != last)
	{
		printf("%2c", cQ->queue[i]);
		i=(i+1)%cQ_SIZE;
	}
	printf(" ]");
}

int SelectMenu() //메뉴출력 및 선택
{
    int key = 0;
    printf("원형큐\n");
    printf("1: 삽입 2: 삭제 3: 큐출력 4: 종료\n");
    scanf_s("%d", &key);
    return key;
}

int _tmain(int argc, _TCHAR* argv[])
{
	QueueType *cQ = createQueue();
	int key = 0;
    while ((key = SelectMenu()) != 4)//선택한 메뉴가 0이 아니면 반복
    {
        switch (key)//선택한 키에 따라 기능 수행
        {
        case 1: enQueue(cQ,'A'); break; //삽입
        case 2: deQueue(cQ); break; //삭제
        case 3: printQ(cQ); break; //큐출력
        default: printf("잘못 선택하였습니다.\n"); break;
        }
    }

    printf("프로그램 종료\n");
	system("pause");
	return 0;
}
