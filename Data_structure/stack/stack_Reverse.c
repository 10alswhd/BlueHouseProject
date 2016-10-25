#include "stdafx.h"
#include "stdlib.h"

#define N 10

int push(char );
int pop();
int top = -1;
int s[N],info;

void main()
{
	char ch;
	ch = getchar();
	while(ch != '\n')
	{
		if(push(ch) == 0)
		{
			printf("error");
			return;
		}
		ch = getchar();
	}
	while(top >= 0)
	{
		ch = pop();
		if(ch == 0)
		{
			printf("error");
			return;
		}
		printf("%c", ch);
	}

	system("pause");
}

int push(char info)
{
	if(top == N-1)
		return 0;
	s[++top] = info;
	return 1;
}
int pop()
{
	if(top == -1)
		return 0;
	return s[top--];
}
