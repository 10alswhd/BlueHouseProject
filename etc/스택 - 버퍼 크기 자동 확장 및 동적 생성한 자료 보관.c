#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef void * Element; //void * 형식을 Element 형식 명으로 정의
 
typedef struct Stack //Stack 구조체 정의
{
    Element *buf;//저장소
    int ssize;//저장소 크기
    int top; //가장 최근에 보관한 인덱스
}Stack;
 
Stack *NewStack();//스택 생성자
void DeleteStack(Stack *stack);//스택 소멸자
int IsFull(Stack *stack); //스택이 꽉 찼는지 확인
int IsEmpty(Stack *stack); //스택이 비었는지 확인
void Push(Stack *stack, Element data); //스택에 보관
Element Pop(Stack *stack); //스택에서 꺼냄
 
 
typedef struct Data
{
    int num;
    char *name;
}Data;
 
Data *NewData(int num, const char *name)
{
    Data *data = (Data *)malloc(sizeof(Data));
    data->num = num;
    data->name = (char *)malloc(strlen(name) + 1);
    strcpy_s(data->name, strlen(name) + 1, name);
    return data;
}
void DeleteData(Data *data)
{
    free(data->name);
    free(data);
}
void ViewData(Data *data)
{
    printf("%-5d %-10s\n", data->num, data->name);
}
 
int main(void)
{
    Data *data = 0;
    Stack *stack = NewStack(); //스택 생성
 
    Push(stack, NewData(3, "홍길동"));//data 생성 후 스택에 보관
    Push(stack, NewData(5, "강감찬")); //data 생성 후 스택에 보관
    Push(stack, NewData(2, "을지문덕")); //data 생성 후 스택에 보관
    Push(stack, NewData(4, "이순신")); //data 생성 후 스택에 보관
 
    printf("%-5s %-10s\n", "번호", "이름");
    while (!IsEmpty(stack))//스택이 비어있지 않다면 반복
    {
        data = (Data *)Pop(stack);//스택에서 꺼냄
        ViewData(data);//data 출력
        DeleteData(data);//data 소멸
    }
    DeleteStack(stack);//스택 소멸
    return 0;
}
 
void InitStack(Stack *stack, int ssize);//스택 초기화
Stack *NewStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));//스택 동적 메모리 할당
    InitStack(stack, 1);//스택 초기화
    return stack;
}
 
void InitStack(Stack *stack, int ssize)
{
    stack->buf = (Element *)malloc(sizeof(Element)*ssize);
    stack->ssize = ssize;
    stack->top = -1; //스택 초기화에서는 top을 -1로 설정
}
 
void DisposeStack(Stack *stack);//스택 해제화
void DeleteStack(Stack *stack)
{
    DisposeStack(stack);//스택 해제화
    free(stack); //스택 메모리 해제
}
void DisposeStack(Stack *stack)
{
    free(stack->buf);
}
 
int IsFull(Stack *stack)
{
    return (stack->top + 1) == stack->ssize;//top+1 이 스택 크기와 같으면 꽉 찬 상태
}
int IsEmpty(Stack *stack)
{
    return stack->top == -1;    //top이 -1이면 빈 상태   
}
void Expand(Stack *stack);//스택 버퍼 확장
void Push(Stack *stack, Element data)
{
    if (IsFull(stack))
    {
        Expand(stack);
    }
    stack->top++; //top을 1 증가
    stack->buf[stack->top] = data;   //데이터 보관
}
void Expand(Stack *stack)
{
    stack->ssize *= 2;//스택 크기를 2배 증가
    stack->buf = (Element *)realloc(stack->buf, sizeof(Element)*stack->ssize);//버퍼 2배로 확장
}
Element Pop(Stack *stack)
{
    Element re = 0;
    if (IsEmpty(stack))
    {
        printf("스택이 비었음\n");
        return re;
    }
    re = stack->buf[stack->top];//top 인덱스에 보관한 값을 re에 설정
    stack->top--;//top을 1 감소
    return re;
}
