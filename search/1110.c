#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct student
{
	char name[30];
	int mid;
	int final;
};
struct node
{
	struct student data;
	struct node *next;
};
typedef struct node node;

const char fname[] = "data.bin";

node *init()
{
	FILE *f;
	node *temp_node, *head = NULL, *prv, *cur;

	if ((f = fopen(fname, "rb+")) == NULL) {
		if ((f = fopen(fname, " wb+")) == NULL) {
			printf( "파일이 열리지 않습니다.\n" );
			exit(1);
		}
	}

	while(1)
	{
		temp_node = (node *)malloc(sizeof(node));

		if(fread(temp_node, sizeof(node), 1, f) == 1)
		{
			if(head == NULL)
			{
				head = temp_node;
				prv = head;
				cur = head->next;
			}
			else
			{
				cur = temp_node;
				prv->next = cur;
				prv = cur;
				cur = cur->next;
			}
		}
		else if(feof(f)) break;
	}
	return head;
}

node *new_student(char name[], int mid, int final)
{
	node *nw = (node *)malloc(sizeof(node));

	strcpy(nw->data.name, name);
	nw->data.mid = mid;
	nw->data.final = final;
	nw->next = NULL;

	return nw;
}

void show(node *head)
{
	double s_mid=0, s_final=0;
	int cnt = 0;

	if(head == NULL)
	{
		printf("정보가 없습니다.\n");
		return;
	}
	
	while(head != NULL)
	{
		printf("%d %8s %3d %3d\n", ++cnt, head->data.name, head->data.mid, head->data.final);
		s_mid += head->data.mid;
		s_final += head->data.final;
		head = head->next;
	}
	printf("------------------\n");
	printf("    평균    %.0f  %.0f\n", s_mid / cnt, s_final / cnt);
}

void search(node *head)
{
	char name[30];
	printf("탐색할 정보의 이름을 입력하세요:");
	scanf("%s", name);

	while(head != NULL)
	{
		if( strcmp(head->data.name, name) == 0)
		{
			printf("%s의 정보: (%s, %d, %d)\n", name, name, head->data.mid, head->data.final);
			return;
		}
		head = head->next;
	}

	printf("%s:없는 정보입니다.\n", name);
}

void modify(node *head)
{
	int num;
	int cnt = 1;
	
	char m_name[30];
	int m_mid, m_final;

	printf("수정할 정보의 번호를 입력하세요:");
	scanf("%d", &num);

	while(head != NULL)
	{
		if(num == cnt)
		{
			printf("수정할 내용:");
			scanf("%s %d %d", m_name, &m_mid, &m_final);
			strcpy(head->data.name, m_name);
			head->data.mid = m_mid;
			head->data.final = m_final;

			return;
		}

		head = head->next;
		cnt++;
	}

	printf("NOT FOUND\n");
}

node *add(node *head)
{
	char name[30];
	int mid;
	int final;

	node *cur = head;
	node *prv = NULL;

	while( printf("이름, 국어와 수학 성적을 입력하시오:") && scanf("%s %d %d", name, &mid, &final) == 3 )
	{
		if(head == NULL)
		{
			head = new_student(name, mid, final);
			prv = head;
			cur = head;
		}
		else
		{
			while(cur != NULL)
			{
				prv = cur;
				cur = cur->next;
			}

			cur = new_student(name, mid, final);
			prv->next = cur;
			prv = cur;
			cur = cur->next;
		}
	}

	return head;
}

void end(node *head)
{
	FILE *f;
	node *t = NULL;
	f = fopen(fname, "wb+");

	printf("프로그램을 종료합니다.\n");
	while(head != NULL)
	{
		fwrite(head, sizeof(node), 1, f);
		t = head;
		head = head->next;
		free(t);
	}
}

int main()
{
	node *head = NULL;

	char cmd;

	// init
	head = init();

	// 
	while(1)
	{
		printf("전체정보출력(t), 탐색(s), 수정(u), 입력(i), 종료(f)를 선택하세요:");
		scanf(" %c", &cmd);
		switch(cmd)
		{
		case 't': // show
			show(head);
			break;
		case 's': // search
			search(head);
			break;
		case 'u': // modify
			modify(head);
			break;
		case 'i': // add
			head = add(head);
			break;
		case 'f': // save and clear
			end(head);
			return 0;
		}
	}

	return 0;
}
