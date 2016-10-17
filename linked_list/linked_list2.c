#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char name[15];
	struct student* next;
};
struct student *head, *tail;
void studentAddLast(char *name); // 연결리스트 뒤 부분에 학생을 삽입.
void studentAdd(char *frontStudent, char *newStudent); // 앞 학생 이름 뒤에 새로운 학생 삽입.
void travel(); // 출석을 부르는 함수.
void studentOut(char* studentName); // 학생을 삭제하는 함수.

int main(void)
{

	studentAddLast("한재");
	studentAddLast("광영");
	studentAddLast("치호");
	studentAddLast("건희");
	travel();
	studentAdd("광영", "문익");
	travel();
	studentOut("치호");
	travel();
	return 0;
}

void studentOut(char* studentName)
{
	struct student *i = head, *remover;
	while( i != NULL ){
		if( strcmp( i->next->name , studentName) == 0 ){
			remover = i->next;
			i->next = remover->next;
			free(remover);
			return;
		}
		i = i->next; // 연결리스트에서 다음 노드로 진행.
	}
}

void studentAdd(char *frontStudent, char *newStudent)
{
	struct student *i = head, *temp;
	while( i != NULL ){
		if( strcmp( i->name , frontStudent ) == 0 ){		//광영을 찾는지
			temp = (struct student *)malloc(sizeof(struct student));
			strcpy( temp->name, newStudent );
			temp->next = i->next;
			i->next = temp;
			return;
		}
		i = i->next;
	}
	// 이름을 찾지 못한경우
	printf("Name Not found!\n");
}

void studentAddLast(char *newStudent)
{
	struct student * p = (struct student*)malloc(sizeof(struct student));
	strcpy(p->name, newStudent);
	p->next = NULL;
	if( head == NULL ){		// 비어있을 경우
		head = p;
		tail = p;
	}
	else{
		tail->next = p;
		tail = p;
	}
}

void travel()
{
	struct student * i = head;
	printf("travel start------\n");
	while( i != NULL ){
		printf("Name = %s\n", i->name);
		i = i->next;
	}
	printf("travel end---------\n");
}
