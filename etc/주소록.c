#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/* 구조체의 멤버들의 배열 크기 */
#define MAX_NAME    20
#define MAX_PHONE    20
#define MAX_ADDRESS    100

/* menu_main()에서 사용할 무한루프 */
#define FOREVER        1

/**
 * 구조체 선언 ..
 * 형식선언자를 통해 구조체를 book이라는 새로운 형으로 만들어준다.
 */
typedef struct _book
{
    unsigned long index;            /* 항목의 index */

    char name[MAX_NAME];            /* 이름 */
    char phone[MAX_PHONE];            /* 전화번호 */
    char address[MAX_ADDRESS];        /* 주소 */

    struct _book *next;
} book;

/**
 * 전역 변수 선언 ..
 * linked list의 head와 tail 변수 (포인터로 선언한다.)
 */
book *head, *tail;
unsigned long num_books;            /* 주소록 항목의 수를 저장할 변수 */
unsigned long last_index;            /* 주소록 항목의 마지막 index */

/* 데이터를 저장시킬 파일 이름 */
const char *fnbook = "addressbook.dat";

/**
 * 함수 원형 선언 ..
 */

/* 사용자 인터페이스 함수 */
void menu_main();                   // 주메뉴 출력
void menu_add();                   // 항목 추가 메뉴
void menu_search();                   // 항목 검사 메뉴

/* 주소록 관리 함수 */
void init_book();                   // linked list의 초기화
void view_book(book *data);           // 하나의 항목 출력
void list_book();                   // 주소록 전체 항목 출력
int add_book(book data);           // 항목 추가
int delete_book(int index);           // 항목 삭제
void clear_book();                   // linked list 해제
int read_book();                   // 파일에서 데이터 읽기
int write_book();                   // 파일에 데이터 저장

int search_name(char *name);       // 이름 검색
int search_phone(char *phone);       // 전화번호 검색
int search_address(char *address);   // 주소 검색

/**
 * 메인 함수 ..
 */
void main()
{
    init_book();       // Linked list를 초기화한다.
    read_book();       // 파일을 읽어와 linked list에 저장한다.
    menu_main();       // 메인 화면을 보여주고, 사용자 요구를 받는다.
    write_book();       // linked list를 파일에 저장한다.
    clear_book();       // linked list의 내용을 지운다. 즉, 할당된 메모리를 해제해준다.
}

/**
 * 사용자 인터페이스 관련 함수 ..
 */
/**
 * menu_main()
 * 주메뉴를 출력하고 입력을 받아 적절한 조치를 쥐한다.
 * Parameters: none
 * Return: none
 */
void menu_main()
{
    int choice;

    while (FOREVER) {                   // 무한루프
        do {                           // 사용자의 입력 검사
            printf("[원하는 작업이 무엇입니까?]\n");
            printf("1. 주소록 추가\n");
            printf("2. 주소록 보기\n");
            printf("3. 주소록 검색\n");
            printf("4. 주소록 저장\n");
            printf("5. 종료\n\n");
            printf("[선택] ");

            scanf("%d", &choice);
            flushall();               // 입력 버퍼에서 '\n' 삭제
        } while (choice < 1 || choice > 5);

        switch (choice)               // 사용자의 입력에 따라 적절한 함수 호출
        {
        case 1:
            menu_add(); break;
        case 2:
            list_book(); break;
        case 3:
            menu_search(); break;
        case 4:
            write_book(); break;
        case 5:
            return;
        default:
            break;
        }
    }
}

/**
 * menu_add()
 * 새로운 항목 추가 메뉴 출력 ..
 * Parameters: none
 * Return: none
 */
void menu_add()
{
    book data;
    data.index = last_index + 1;

    /* 사용자에게 적절한 입력을 받을 때까지 루프를 돈다. */
    do {
        printf("[새로운 데이터 입력]\n");
        printf("1. 이름: ");
        gets(data.name);
        printf("2. 전화: ");
        gets(data.phone);
        printf("3. 주소: ");
        gets(data.address);
    } while (strlen(data.name) <= 0 || strlen(data.phone) <= 0 || strlen(data.address) <= 0);

    /* linked list에 새로운 데이터를 추가한다. */
    if (add_book(data)) {
       // 데이터 추가 성공시 last_index와 num_books 증가
        printf("[성공적으로 데이터를 추가하였습니다.]\n\n");
        last_index++;
        num_books++;
    }
    else
        printf("[데이터를 추가하는데 실패하였습니다.]\n\n");
}

/**
 * menu_search()
 * 항목 검사 메뉴 출력 ..
 * Parameters: none
 * Return: none
 */
void menu_search()
{
    int choice;
    char buffer[MAX_ADDRESS];
    int result;

    /* 사용자가 종료할 때까지 무한루프를 돈다. */
    while (FOREVER) {
        /* 사용자의 입력을 받는다. */
        do {
            printf("[어느 항목에서 찾으시겠습니까?]\n");
            printf("1. 이름\n");
            printf("2. 전화\n");
            printf("3. 주소\n");
            printf("4. 종료\n\n");
            printf("[선택] ");

            scanf("%d", &choice);
            flushall();               // 입력 버퍼에서 '\n' 삭제
        } while (choice < 1 || choice > 4);

        if (choice == 1) {
            printf("찾을 이름이 무엇입니까? ");
            gets(buffer);
            result = search_name(buffer);
        }
        else if (choice == 2) {
            printf("찾을 전화번호가 무엇입니까? ");
            gets(buffer);
            result = search_phone(buffer);
        }
        else if (choice == 3) {
            printf("찾을 주소가 무엇입니까? ");
            gets(buffer);
            result = search_address(buffer);
        }
        else if (choice == 4)
            return;

        /* 만약 찾은 결과가 있다면 항목수를 출력해준다. */
        if (result)
            printf("[총 %d개의 항목을 찾았습니다.]\n\n", result);
        else
            printf("[%s]에 일치하는 항목을 찾지 못했습니다.\n\n", buffer);
    }
}

/**
 * linked list 처리 함수 ..
 */

/**
 * init_book()
 * linked list의 초기화 ..
 * Parameters: none
 * Return: none
 */
void init_book()
{
    num_books = 0;
    last_index = 0;
    clear_book();
}

/**
 * view_book()
 * 하나의 항목 출력 ..
 * Parameters: 출력한 데이터의 포인터 ..
 * Return: none
 */
void view_book(book *data)
{
    printf("1. 이름: %s\n", data->name);
    printf("2. 전화: %s\n", data->phone);
    printf("3. 주소: %s\n", data->address);
    printf("[아무 키나 누르세요.] ");
    getch();
    printf("\n\n");
}

/**
 * list_book()
 * linked list의 모든 항목 출력 ..
 * Parameters: none
 * Return: none
 */
void list_book()
{
    book *t;

    /* linked list가 비어있는 경우 */
    if (head == NULL) {
        printf("[데이터가 없습니다.]\n\n");
        return;
    }

    /* linked list의 마지막 노드까지 내용을 출력한다. */
    t = head;
    while (t != NULL) {
        view_book(t);
        t = t->next;
    }

    printf("[총 %d개의 항목이 있습니다.]\n\n", num_books);
}

/**
 * add_book()
 * linked list에 하나의 항목 추가 ..
 * Parameters: 저장할 데이터 ..
 * Return: 성공시 1, 실패시 0
 */
int add_book(book data)
{
    book *t;

    if (data.index == 0) return 0;

    /* 동적 메모리 할당 */
    if ((t = (book *) malloc(sizeof(book))) == NULL) {
        printf("[메모리가 부족하여 더 이상 데이터를 추가할 수 없습니다!]\n");
        return 0;
    }

    /* 할당된 메모리, 즉 새로운 노드에 값을 저장한다.*/
    t->index = data.index;
    strcpy(t->name, data.name);
    strcpy(t->phone, data.phone);
    strcpy(t->address, data.address);
    t->next = NULL;

    /* 현재 리스트가 비어있다면 */
    if (tail == NULL)
        head = tail = t;
    else {
        tail->next = t;
        tail = t;
    }

    return 1;
}

/**
 * delete_book()
 * linked list에서 하나의 항목 삭제 ..
 * Parameters: 삭제시킬 항목의 index
 * Return: 성공시 1, 실패시 0
 */
int delete_book(int index)
{
    return 1;
}

/**
 * clear_book()
 * linked list 해제 ..
 * Parameters: none
 * Return: none
 */
void clear_book()
{
    book *t;

    /* 리스트의 끝까지 루프를 돌면서 메모리를 해제해준다. */
    while (head != NULL) {
        t = head;
        head = head->next;
        free(t);
    }

    head = tail = NULL;
}

/**
 * read_book()
 * 파일에서 데이터를 읽어와 linked list에 저장 ..
 * Parameters: none
 * Return: 성공시 1, 실패시 0
 */
int read_book()
{
    book data;
    FILE *fp;

    /* 파일을 바이너리 읽기 모드로 연다. */
    if ((fp = fopen(fnbook, "rb")) == NULL) {
        printf("[데이터 파일을 읽는데 실패했습니다.]\n");
        return 0;
    }

    /* 파일의 끝까지 */
    while (!feof(fp)) {
        data.index = 0;
        /* 구조체 크기만큼 하나씩 읽어서 이를 linked list에 추가한다. */
        if (fread(&data, sizeof(book), 1, fp)) {
            add_book(data);
            num_books++;
        }
    }

    /* 파일을 닫는다. */
    fclose(fp);

    last_index = data.index;
    return 1;
}

/**
 * write_book()
 * linked list의 내용을 파일에 저장 ..
 * Parameters: none
 * Return: 성공시 1, 실패시 0
 */
int write_book()
{
    book *t;
    FILE *fp;

    /* 파일을 바이너리 쓰기 모드로 연다. */
    if ((fp = fopen(fnbook, "wb")) == NULL) {
        printf("[데이터 파일에 쓰는데 실패했습니다.]\n");
        return 0;
    }

    /* linked list의 내용을 하나씩 파일에 저장한다. */
    t = head;
    while (t != NULL) {
        fwrite(t, sizeof(book), 1, fp);
        t = t->next;
    }

    fclose(fp);
    printf("[성공적으로 데이터 파일에 저장했습니다.]\n\n");
    return 1;
}

/**
 * search_name()
 * lined list에서 이름 검색 ..
 * Parameters: 찾을 이름(문자열)
 * Return: 찾은 항목의 수 ..
 */
int search_name(char *name)
{
    book *t;
    int num = 0;

    t = head;
    while (t != NULL) {
        if (strstr(t->name, name)) {
            view_book(t);
            num++;
        }
        t = t->next;
    }

    return num;
}

/**
 * search_phone()
 * lined list에서 전화번호 검색 ..
 * Parameters: 찾을 전화번호(문자열)
 * Return: 찾은 항목의 수 ..
 */
int search_phone(char *phone)
{
    book *t;
    int num = 0;

    t = head;
    while (t != NULL) {
        if (strstr(t->phone, phone)) {
            view_book(t);
            num++;
        }
        t = t->next;
    }

    return num;
}

/**
 * search_address()
 * lined list에서 주소 검색 ..
 * Parameters: 찾을 주소(문자열)
 * Return: 찾은 항목의 수 ..
 */
int search_address(char *address)
{
    book *t;
    int num = 0;

    t = head;
    while (t != NULL) {
        if (strstr(t->address, address)) {
            view_book(t);
            num++;
        }
        t = t->next;
    }

    return num;
}
