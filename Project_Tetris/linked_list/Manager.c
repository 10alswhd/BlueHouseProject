#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct _node {
	char name[10];		// 이름
	char address[30];	// 주소
	char phone[14];		// 전화번호
	char mobile[14];	// 핸드폰
	char mail[20];		// e-mail
	struct _node *link;	// 다음 노드
};

typedef struct _node node;

void Insert(node*);		// 노드 삽입 함수
void Delete(node*);		// 노드 삭제 함수
void Display(node*);	// 노드 정보 출력 함수

int main(void) {
	node *ptr;
	int choice;

	/*
		첫번째 노드 생성
		동적할당을 통해 공간을 생성하여 노드를 만든다.
		다음 노드 위치는 NULL로 초기화한다
	*/
	ptr = (node *)malloc(sizeof(node));
	ptr->link = NULL;

	/*
		do-while을 이용한 반복
		4. 종료를 선택할 때까지 반복한다.
	*/
	do {
		// 메뉴 출력
		printf("주소관리 프로그램\n");
		printf("1. 등    록\n");
		printf("2. 출    력\n");
		printf("3. 삭    제\n");
		printf("4. 종    료\n");
		printf("명령어를 선택하시오: ");
		
		// 1문자를 입력받아 숫자로 변환
		choice = getchar() - '0';
		
		// 입력 버퍼 초기화
		fflush(stdin);

		/* 
			입력받은 숫자에 따라 분기
			1 : 등록 -> Insert
			2 : 출력 -> Display
			3 : 삭제 -> Delete
		*/
		switch(choice) {
			case 1 : 
				Insert(ptr); 
				break;
			case 2 : 
				Display(ptr->link);
				break;
			case 3 : 
				Delete(ptr); 
				break;
		}
	}while(choice!=4);
}


void Insert(node *ptr) {
	while (ptr->link != NULL)
		ptr = ptr->link;

	ptr->link = (node*)malloc(sizeof(node));
	ptr = ptr->link;
	
	printf("이름을 입력하시오: ");
	gets(ptr->name);
	printf("주소를 입력하시오: ");
	gets(ptr->address);
	printf("전화번호 입력하시오: ");
	gets(ptr->phone);
	printf("핸드폰을 입력하시오: ");
	gets(ptr->mobile);
	printf("E-Mail을 입력하시오: ");
	gets(ptr->mail);

	ptr->link = NULL;
	printf("\n");
}

void Delete(node *ptr)  {
	node *prev;
	char _phone[14];

	printf("삭제할 전화번호를 선택하시오: ");
	gets(_phone);

	while (ptr->link != NULL)  {
		prev = ptr;
		ptr = ptr->link;

		/* 저장되어 있는 데이터중에서 전화번호를 기준으로 데이터를 삭제 */
		if (strcmp(_phone, ptr->phone) == 0) {
			prev->link = ptr->link;
			free(ptr);
			break;
		}
	}
	return;
}

void Display(node *ptr)  {
	printf("%6s", "이  름") ;
	printf("%14s", "주   소");
	printf("%14s", "전화번호");
	printf("%14s", "핸드폰");
	printf("%10s\n", "E-Mail");
	
	while (ptr != NULL) {
		printf("%6s", ptr->name);
		printf("%14s", ptr->address);
		printf("%14s", ptr->phone);
		printf("%14s", ptr->mobile);
		printf("%10s", ptr->mail);
		
		ptr = ptr->link;
		printf("\n");
	}
	
	printf("\n");
}
