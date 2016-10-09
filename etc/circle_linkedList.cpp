// circle_linkedList.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

//���� ���� ����Ʈ�� ��� ������ ����ü�� ����
typedef struct ListNode
{
	char data[100];
	struct ListNode* link;
}listNode;

//����Ʈ ������ ��Ÿ���� head ��带 ����ü�� ����
typedef struct
{
	listNode* head;
}linkedList_h;

linkedList_h* CL;
listNode *p;

//���� ���� ���� ����Ʈ�� �����ϴ� ����
linkedList_h* createLinkedList_h(void)
{
	linkedList_h* CL;
	CL = (linkedList_h*)malloc(sizeof(linkedList_h));  //��� ��� �Ҵ�
	CL -> head = NULL;   //���� ����Ʈ�̹Ƿ� NULL�� ����
	return CL;
}

//���� ����Ʈ�� ������� ����ϴ� ����
void printList(linkedList_h* CL)
{
	listNode* p;
	printf(" CL = (");
	p = CL -> head;
	do
	{
		printf("%s", p -> data);
		p = p -> link;
		if(p != CL -> head) printf(", ");
	}while(p != CL -> head);
	printf(") \n");
}

//ù ��° ��� ���� ����
void insertFirstNode(linkedList_h *CL, char *x)
{
	listNode* newNode, *temp;
	newNode = (listNode*)malloc(sizeof(listNode)); //������ �� ��� �Ҵ�
	strcpy_s(newNode -> data, x);
	if(CL -> head == NULL)                         //���� ���� ����Ʈ�� ������ ���
	{
		CL -> head = newNode;                      //�� ��带 ����Ʈ�� ���� ���� ����
		newNode -> link = newNode;
	}
	else                                           //���� ���� ����Ʈ�� ������ �ƴ� ���
	{
		temp = CL -> head;
		while(temp -> link != CL -> head)
			temp = temp -> link;
		newNode -> link = temp -> link;
		temp ->link = newNode;                     //������ ��带 ù ��° ����� new�� ���� ����
		CL -> head = newNode;
	}
}

//pre �ڿ� ��带 �����ϴ� ����
void insertMiddleNode(linkedList_h* CL, listNode *pre, char *x)
{
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy_s(newNode -> data, x);
	if(CL == NULL)
	{
		CL -> head = newNode;
		newNode -> link = newNode;
	}
	else
	{
		newNode -> link = pre -> link;
		pre -> link = newNode;
	}
}

//���� ���� ����Ʈ�� pre �ڿ� �ִ� ��� old�� �����ϴ� ����
void deleteNode(linkedList_h* CL, listNode* old)
{
	listNode* pre;                      //������ ����� ������ ��带 ��Ÿ���� ������
	if(CL -> head == NULL) return;      //���� ����Ʈ�� ��� ���� ���� �ߴ�
	if(CL -> head -> link == NULL)      //����Ʈ�� ��尡 �� ���� �ִ� ���
	{
		free(CL -> head);               //ù ��° ����� �޸𸮸� �����ϰ� 
		CL -> head = NULL;              //����Ʈ ���� �����͸� NULL�� ����
		return;
	}
	else if(old == NULL) return;        //������ ��尡 ���� ��� ���� ���� �ߴ�
	else
	{
		pre = CL -> head;               //������ pre�� ����Ʈ�� ���� ��忡 ����
		while(pre -> link != old)
		{
			pre = pre -> link;          //������ ��带 ������ pre�� �̿��� ã��
		}
		pre -> link = old -> link;
		if(old == CL -> head)
			CL -> head = old -> link;
		free(old);                     //���� ����� �޸𸮸� ����
	}
}

//���� ���� ����Ʈ���� x ��带 Ž���ϴ� ����
listNode* searchNode(linkedList_h* CL, char* x)
{
	listNode *temp;
	temp = CL -> head;
	while(temp != NULL)
	{
		if(strcmp(temp -> data, x) == 0) return temp;
		else temp = temp -> link;
	}
	return temp;
}

int SelectMenu()
{    
    int key=0;
    printf("���� ���� ����Ʈ\n");
    printf("1: ���� 2: ���� 3: ��� 4: ���� \n");
    scanf_s("%d",&key);
	system("cls");
    return key;
}

void Run()
{
    int key = 0;
    while((key = SelectMenu()) != 4)//������ �޴��� 0�� �ƴϸ� �ݺ�
    {
        switch(key)//������ Ű�� ���� ��� ����
        {
        case 1: insertFirstNode(CL, "A"); break;
        case 2: p = searchNode(CL, "A"); deleteNode(CL, p); break;
        case 3: printList(CL); break;
        default: printf("�߸� �����Ͽ����ϴ�.\n"); break;
        }        
    }
    printf("���α׷� ����\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	CL = createLinkedList_h();
	Run();

	system("pause");
	return 0;
}

