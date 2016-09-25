#include "stdafx.h"
#include "stdlib.h"

#define STACK_SIZE 100

typedef int element;   //스택 원소(element)의 자료형을 int로 정의

element stack[STACK_SIZE]; //1차원 배열 스택 선언
int top = -1;   //top 초기화

//스택이 공백 상태인지 확인하는 연산
int isEmpty()
{
	if(top == -1)
		return 1;
	else 
		return 0;
}

//스택이 포화 상태인지 확인하는 연산
int isFull()
{
	if(top == STACK_SIZE -1)
		return 1;
	else
		return 0;
}

//스택의 top에 원소를 삽입하는 연산
void push(element item)
{
	if(isFull()) //스택이 포화
	{
		printf("\n\n Stack is FULL! \n");
		return;
	}
	else //top증가후 현재 top에 원소삽입
		stack[++top] = item;
}

//스택의 top에서 원소를 삭제하는 연산
element pop()
{
	if(isEmpty()) //스택이 공백 상태인 경우
	{
		printf("\n\n Stack is Empty!!\n");
		return 0;
	}
	else //현재 top원소 삭제후 top감소
		return stack[top--];
}

//스택의 top원소를 검색하는 연산
element peek()
{
	if(isEmpty())
	{
		printf("\n\n Stack is Empty! \n");
		exit(1);
	}
	else
		return stack[top];
}

//스택의 원소를 출력하는 연산
void printStack()
{
	int i;
	printf("\n STACK [ ");
	for(i = 0; i <= top; i++)
		printf("%d ",stack[i]);
	printf("] ");
}

int _tmain(int argc, _TCHAR* argv[])
{
	element item;
	printf("\n** 순차 스택 연산 **\n");
	printStack();
	push(1); printStack(); //1삽입
	push(2); printStack(); //2삽입
	push(3); printStack(); //3삽입

	item = peek();
	printStack(); //현재 top의 원소 출력
	printf("peek => %d", item);

	item = pop();
	printStack();
	printf("\t pop  => %d", item); //삭제

	item = pop();
	printStack();
	printf("\t pop  => %d", item);

	item = pop();
	printStack();
	printf("\t pop  => %d", item);

	getchar();

	system("pause");
	return 0;
}
