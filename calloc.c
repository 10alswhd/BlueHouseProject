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
 
typedef struct Stack Stack;
struct Stack
{
    Data **base;
    size_t size;
    int top;
};
 
Stack *NewStack(size_t size);//동적으로 Stack 생성
int StackPush(Stack *stack, Data *data);//스택에 Data 보관
Data *StackPop(Stack *stack);//스택에서 Data 꺼냄
void DeleteStack(Stack *stack);//동적으로 생성한 스택 소멸
 
int main(void)
{
    Stack *stack = NewStack(10);//크기가 10인 스택 생성
    Data *data = NULL;
    StackPush(stack,NewData(1, "홍길동"));//스택에 동적으로 Data를 생성하여 보관
    StackPush(stack,NewData(2, "강감찬"));//스택에 동적으로 Data를 생성하여 보관
    StackPush(stack,NewData(3, "을지문덕"));//스택에 동적으로 Data를 생성하여 보관
    StackPush(stack,NewData(4, "이순신"));//스택에 동적으로 Data를 생성하여 보관
    while ((data = StackPop(stack)) != NULL)//스택에서 꺼낸 것이 NULL이 아니면(비어있지 않다면) 반복
    {
        DataView(data);//Data 정보 보기
        DeleteData(data);//동적으로 생성한 Data 소멸
    }
    DeleteStack(stack);//동적으로 생성한 스택 소멸
    return 0;
}
 
Data *NewData(int num, const char *name)
{
    //구조체 Data 크기 1개를 동적으로 메모리 할당
    Data *data = (Data *)calloc(1, sizeof(Data));
    //입력받은 name 문자열 길이+1 크기 1개를 동적으로 메모리 할당
    data->name = (char *)calloc(1, strlen(name) + 1);
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
 
Stack *NewStack(size_t size)
{
    //구조체 Stack 크기 1개를 동적으로 메모리 할당
    Stack *stack = (Stack *)calloc(1, sizeof(Stack));
    //Data * 크기 size 개를 동적으로 메모리 할당
    stack->base = (Data **)calloc(size, sizeof(Data *));
    stack->size = size;//스택의 용량 설정
    stack->top = -1;//스택의 top을 -1로 설정(top은 가장 최근에 보관한 원소의 인덱스)
    return stack;//동적으로 생성한 stack 반환
}
 
int StackPush(Stack *stack, Data *data)
{
    if ((stack->top + 1) == stack->size)//꽉찼을 때
    {
        return 0;//보관 실패
    }
    stack->top++;//top을 1 증가
    stack->base[stack->top] = data;//base의 top 인덱스에 data 보관
    return 1;//보관 성공
}
 
Data *StackPop(Stack *stack)
{
    Data *data = NULL;
    if (stack->top == -1)//스택이 비었음
    {
        return NULL;//꺼내기 실패
    }
    data = stack->base[stack->top];//base의 top 인덱스에 원소를 data에 설정
    stack->top--; //top 1 감소
    return data;//꺼내기 성공
   
}
 
void DeleteStack(Stack *stack)
{
    free(stack->base);//동적으로 생성한 base 메모리 해제
    free(stack);//동적으로 생성한 stack 메모리 해제
}
