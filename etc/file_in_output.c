// file_in_out_put.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

typedef struct score *PSCORE;
typedef struct score
{
	char name[20]; 
	int number;
	int grade;
	PSCORE link;
}SCORE;

PSCORE createNode(SCORE a);
void reader(char *fname, PSCORE *head);
void writer(char *fname, PSCORE *head);
void RemoveAllList(PSCORE ptr);

int _tmain(int argc, _TCHAR* argv[])
{
	PSCORE stdPt = NULL;

	reader("input.txt", &stdPt);
	writer("output.txt", &stdPt);
	RemoveAllList(stdPt);

	system("pause");
	return 0;
}

void RemoveAllList(PSCORE ptrHead)
{
	PSCORE ptr;
	for(ptr = ptrHead; ptrHead != NULL; ptr = ptrHead)
	{
		ptrHead = ptrHead->link;
		if(ptr != NULL)
			free(ptr);
	}
}

void reader(char *fname, PSCORE *head)
{
	SCORE st;
	PSCORE ptr;
	FILE *fp;
	if((fp = fopen(fname, "r")) == NULL)
	{
		printf("입력 파일을 열 수 없습니다.\n");
		exit(1);
	}
	while(fscanf_s(fp, "%s %d %d", st.name, &st.number, &st.grade) != EOF)
	{
		ptr = createNode(st);
		if(*head == NULL)
			*head = ptr;
		else
		{
			ptr->link = *head;
			*head = ptr;
		}
	}
	fclose(fp);
}

void writer(char *fname, PSCORE *head)
{
	FILE *fp;
	int i;
	PSCORE ptr;

	if((fp = fopen(fname, "w")) == NULL)
	{
		printf("출력 파일을 열 수 없습니다.\n");
		exit(1);
	}
	fprintf(fp, "# : name   number  grade\n");
	fprintf(fp, "------------------------\n");
	for(ptr = *head, i = 0; ptr; ptr = ptr->link, i++)
	{
		fprintf(fp, "%d : %3s %3d %3d\n",i, ptr->name, ptr->number, ptr->grade);
	}
}

PSCORE createNode(SCORE a)
{
	PSCORE ptr;
	ptr = (PSCORE)malloc(sizeof(SCORE));
	strcpy_s(ptr->name, a.name);
	ptr->number = a.number;
	ptr->grade = a.grade;
	ptr->link = NULL;
	return ptr;
}
