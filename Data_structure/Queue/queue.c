
// ttest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdlib.h"
#define cQ_SIZE 5

typedef int element;
typedef struct
{
	element queue[cQ_SIZE];
	int front, rear;
}QueueType;

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

void enQueue(QueueType *cQ, element item)
{
	if (((cQ->rear + 1) % cQ_SIZE) == cQ->front) 
	{
		printf("isFull\n");
		return;
	}
	else
	{
		cQ->rear = (cQ->rear + 1) % cQ_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

element deQueue(QueueType *cQ)
{
	if (cQ->front == cQ->rear) 
	{
		printf("isEmpty\n");
		return 0;
	}
	else
	{
		cQ->front = (cQ->front + 1) % cQ_SIZE;
		return cQ->queue[cQ->front];
	}
}

void printQ(QueueType *cQ)
{
	int i, first, last;
	first = (cQ->front + 1) % cQ_SIZE;
	last = (cQ->rear + 1) % cQ_SIZE;
	printf("원형큐 출력 : [ ");
	i = first;
	while (i != last)
	{
		printf("%d", cQ->queue[i]);
		i = (i + 1) % cQ_SIZE;
	}
	printf(" ]\n");
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
	element data = 0;
	while ((key = SelectMenu()) != 4)
	{
		switch(key)//선택한 키에 따라 기능 수행
		{
		case 1:
			printf("입력 : ");
			scanf_s("%d", &data);
			enQueue(cQ, data);
			printf("\n");
			break;
		case 2: deQueue(cQ);
				printf("\n"); break;
		case 3: printQ(cQ); break;
		default: printf("잘못 선택하였습니다.\n"); break;
		}
	}

	printf("프로그램 종료\n");
	system("pause");
	return 0;
}

