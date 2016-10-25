#include "stdafx.h"
#include "stdlib.h"

struct node
{
    int data;
    struct node *next;
}*head;

void insert(int num)
{
    node *tmp, *last;
	tmp=(node*)malloc(sizeof(node));
	tmp->data=num;
	tmp->next=NULL;
	if(head==NULL)
	{
		head=tmp;
		return;
	}
	last=head;
	while(last->next!=NULL)
		last=last->next;
	last->next=tmp;
}

int Delete(int num)
{
    struct node *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
		if(temp->data==num)
		{
		    if(temp==head)
		    {
				head=temp->next;
				free(temp);
				return 1;
		    }
			else
		    {
				prev->next=temp->next;
				free(temp);
				return 1;
			}
		}
		else
		{
			prev=temp;
			temp= temp->next;
		}
    }
    return 0;
}

void  display(struct node *r)
{
    r=head;
    if(r==NULL)
    {
		return;
    }
    while(r!=NULL)
    {
		printf("%d ",r->data);
		r=r->next;
    }
    printf("\n");
}

int  main()
{
    int i,num;
    struct node *n = 0;
    head=NULL;
    while(1)
    {
		printf("연결리스트\n");
		printf("1: 삽입 2: 삭제 3: 큐출력 4: 종료\n");
		printf("선택 : ");
		if(scanf_s("%d",&i)<=0)
		{
			printf("Enter only an Integer\n");
			exit(0);
		} 
		else 
		{
			switch(i)
			{
				case 1: printf("삽입할 숫자 : ");
						scanf_s("%d",&num);
						insert(num);
						break;
				case 2: if(head==NULL)
						printf("is Empty\n");
						else
						{
							printf("삭제할 숫자 : ");
							scanf_s("%d",&num);
							if(Delete(num))
								printf("%d 삭제성공\n",num);
							else
								printf("%d 리스트에 없습니다\n",num);
						}
						break;
				case 3: if(head==NULL)
						{
							printf("is Empty\n");
						}
						else
						{
							printf("리스트 출력 : ");
						}
						display(n);
						break;
			
				case 4: return 0;
				default: printf("잘못된 선택입니다\n");
			}
			printf("\n");
		}
    }
    return 0;
}
