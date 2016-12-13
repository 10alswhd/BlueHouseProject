#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node { //宣告singly linked list結構
   int data;
   struct node *next;
};

struct nodeDLL { //宣告doubly linked list結構
   int data;
   struct nodeDLL *prev, *next;
};

struct node *first = NULL; //宣告指向首端的結構指標
struct nodeDLL *firstDLL = NULL, *tailDLL = NULL; //宣告指向首端及尾端的結構指標

void build_a_list(struct node **first, int n); //宣告singly linked list函數群
void print_list(struct node *first);
void clean_list(struct node *first);
void insert_to_list(struct node **first);
void search_list();
void delete_from_list();
void count_list();
void reverse_list();
void merge_list(int n);
void split_list();

void build_a_DLL(struct nodeDLL **firstDLL, struct nodeDLL **tailDLL, int n); //宣告doubly linked list函數群
void prePrint_DLL(struct nodeDLL *firstDLL);
void postPrint_DLL(struct nodeDLL *firstDLL);
void clean_DLL(struct nodeDLL *firstDLL);
void insert_to_DLL(struct nodeDLL **firstDLL, struct nodeDLL **tailDLL);
void search_DLL();
void delete_from_DLL();
void count_DLL();
void reverse_DLL();
void merge_DLL(int n);
void split_DLL();

int main(void)
{
   int DS, n; //DS讀入資料結構型態
   char F; //F讀入執行函數類型

   printf("Please select the data structure or exit: ");
   scanf("%d", &DS);
   srand(time(NULL));
   n = rand() % 10 + 3; //先創造一隨機長度的linked list
   if (DS == 1) {
      printf("Please enter %d numbers to create a initial list: ", n);
      build_a_list(&first, n);
      print_list(first);
   }
   else if (DS == 2) {
      printf("Please enter %d numbers to create a initial list: ", n);
      build_a_DLL(&firstDLL, &tailDLL, n);
      prePrint_DLL(firstDLL);
   }
   else
      return 0;

   while (1) {
      getchar(); //吸收多input的Enter
      printf("Please select the function: ");
      scanf("%c", &F);
      if (DS == 1) { //若選擇singly linked list則執行此選單
         switch (F) {
            case 'a': printf("Enter the number you want to insert: ");
                      insert_to_list(&first);
                      break;
            case 'b': delete_from_list();
                      break;
            case 'c': search_list();
                      break;
            case 'd': count_list();
                      break;
            case 'e': reverse_list();
                      break;
            case 'f': merge_list(n);
                      break;
            case 'g': split_list();
                      break;
            case 'h': print_list(first);
                      break;
            case 'x': clean_list(first);
                      return 0;
         }
      }
      else { //若選擇doubly linked list則執行此選單
         switch (F) {
            case 'a': printf("Enter the number you want to insert: ");
                      insert_to_DLL(&firstDLL, &tailDLL);
                      break;
            case 'b': delete_from_DLL();
                      break;
            case 'c': search_DLL();
                      break;
            case 'd': count_DLL();
                      break;
            case 'e': reverse_DLL();
                      break;
            case 'f': merge_DLL(n);
                      break;
            case 'g': split_DLL();
                      break;
            case 'h': prePrint_DLL(firstDLL);
                      break;
            case 'i': postPrint_DLL(tailDLL);
                      break;
            case 'x': clean_DLL(firstDLL);
                      return 0;
         }
      }
   }
}

void build_a_list(struct node **first, int n) //創造一隨機長度的linked list
{
   int i;
   struct node *new_node, *prev = NULL, *cur;

   new_node = malloc(sizeof(struct node)); //創造第一個節點空間
   if (new_node == NULL) { //若創造失敗則印出錯誤
      printf("Error: malloc failed.\n");
      return;
   }
   new_node->next = *first; //first指向第一個節點
   *first = new_node;
   for (i = 0; i < n; i++) {
      cur = *first;
      scanf("%d", &new_node->data); //讀入數字到節點
      while (cur->data < new_node->data && cur->next != NULL) { //由小到大排列節點
         prev = cur;
         cur = cur->next;
      }
      if (cur->data < new_node->data && cur->next == NULL) { //若原始list內沒有節點的數字比欲插入之節點大，則節點放到尾端
         cur->next = new_node;
         new_node->next = NULL;
      }
      else if (prev == NULL) { //若首端節點數字即比欲插入節點大，則將first指向欲插入之節點，並將節點與原list連結
         if (new_node->next == NULL) //若list內無任何節點，則不需做連結
            ;
         else {
            *first = new_node;
         }
      }
      else { //若為其他狀況則將前一個節點和欲插入之節點連結，欲插入之節點和後一個節點連結
         prev->next = new_node;
         new_node->next = cur;
      }
      new_node = malloc(sizeof(struct node)); //再創一個新節點空間
      if (new_node == NULL) { //若創造失敗則印出錯誤
         printf("Error: malloc failed.\n");
         return;
      }
      if (i == n - 1) //若為最後一次跑for loop，則釋放剛創的節點空間
         free(new_node);
   }
}

void print_list(struct node *first) //印出linked list
{
   if (first == NULL) { //若無list，則印出訊息
      printf("There is no list.\n");
      return;
   }
   struct node *cur;

   for (cur = first; cur != NULL; cur = cur->next) //從第一個節點開始循序印出數字
      printf("%d ", cur->data);
   printf("\n");
}

void clean_list(struct node *first) //清除linked list
{
   struct node *prev, *cur;

   for (cur = first; cur != NULL;) {
      prev = cur;
      cur = cur->next;
      first = cur;
      free(prev);
   }
   first = NULL;
}

void insert_to_list(struct node **first) //插入一個新節點
{
   struct node *new_node, *prev = NULL, *cur;

   new_node = malloc(sizeof(struct node)); //創造新節點空間
   if (new_node == NULL) { //若創造失敗則印出訊息
      printf("Error: malloc failed.\n");
      return;
   }
   scanf("%d", &new_node->data); //讀入數字
   if (*first == NULL) { //若無list可插入新節點則印出訊息
      printf("There is no list to insert a new node.\n");
      free(new_node);
      return;
   }
   for (cur = *first; cur->data < new_node->data && cur->next != NULL;) { //確定新節點位置
      prev = cur;
      cur = cur->next;
   }
   if (prev == NULL) { //若為第一個則first指向新節點，並將新節點與原list連結
      new_node->next = *first;
      *first = new_node;
   }
   else {
      if (cur->next == NULL) { //若為最後一個則原list尾端節點與之連結
         cur->next = new_node;
         new_node->next = NULL;
      }
      else { //其他狀況則前一個和後一個與之連結
         prev->next = new_node;
         new_node->next = cur;
      }
   }
}

void delete_from_list() //從list中刪除一個節點
{
   int n;
   struct node *cur, *prev = NULL;

   if (first == NULL) { //若無list則印出訊息
      printf("Nothing to delete.\n");
      return;
   }
   printf("Enter the number you want to delete: "); //印出要求
   scanf("%d", &n); //讀入數字
   for (cur = first; cur != NULL && cur->data != n; prev = cur, cur = cur->next) //定位
      ;
   if (cur == NULL) { //若找不到欲刪除之節點則印出訊息
      printf("The number doesn't exist in the list.\n");
      return;
   }
   else if (prev == NULL) //若為首端節點則將first指向下一個節點
      first = cur->next;
   else //其他狀況則前一個與後一個連結
      prev->next = cur->next;
   free(cur); //釋放節點空間
   printf("The node has been deleted.\n"); //印出訊息
}

void search_list() //搜尋節點
{
   int n, num_node = 1;
   struct node *cur;

   cur = first;
   printf("Enter the number you want to search: "); //印出要求
   scanf("%d", &n); //讀入數字
   for (; cur != NULL; cur = cur->next, num_node++) //搜尋是否存在
      if (cur->data == n) {
         printf("The number is in no.%d list.\n", num_node); //存在則印出訊息
         return;
      }
   printf("The number doesn't exist in the list.\n"); //不存在則印出訊息
}

void count_list() //計算節點數
{
   int num_nodes = 0;
   struct node *cur;

   for (cur = first; cur != NULL; cur = cur->next) //計算節點數後印出結果
      num_nodes++;
   printf("There are %d nodes in the list.\n", num_nodes);
}

void reverse_list() //反轉list
{
   struct node *prev, *cur;

   cur = first;
   first = NULL;
   while (cur != NULL) { //反轉各節點間的連結並改變first指向
      prev = cur;
      cur = cur->next;
      prev->next = first;
      first = prev;
   }
   printf("The list has been reversed.\n"); //印出訊息
}

void merge_list(int n) //合併兩條linked list
{
   int i;
   struct node *head = NULL;

   srand(time(NULL));
   n = rand() % 10 + 1;
   printf("Please enter %d numbers for the first list: ", n); //輸入第一條list並創建
   build_a_list(&head, n);
   n = rand() % 10 + 1;
   printf("Please enter %d numbers for the second list: ", n); //輸入第二條list並插入第一條list中
   for (i = 0; i < n; i++)
      insert_to_list(&head);
   printf("The merged list:\n");
   print_list(head);
   printf("But the initial list won't change.\n"); //並不會改變最初創建的initial list
   clean_list(head);
}

void split_list() //將list分成奇數及偶數並印出
{
   struct node *cur, *even = NULL, *odd = NULL;

   for (cur = first; cur->data % 2 != 0 && cur->next != NULL; cur = cur->next) //找存偶數的第一個節點
      ;
   if (cur->data % 2 != 0 && cur->next == NULL) {
      printf("There is no even number in the list.");
      return;
   }
   else
      even = cur;
   for (cur = first; cur->data % 2 == 0 && cur->next != NULL; cur = cur->next) //找存奇數的第一個節點
      ;
   if (cur->data % 2 == 0 && cur->next == NULL) {
      printf("There is no odd number in the list.");
      return;
   }
   else
      odd = cur;
   cur = even;
   printf("The even list:\n%d ", cur->data); //依序找出存偶數的節點並印出
   while (cur->next != NULL) {
      cur = cur->next;
      while (cur->data % 2 != 0 && cur->next != NULL)
         cur = cur->next;
      if (cur->data % 2 == 0)
         printf("%d ", cur->data);
      else
         break;
   }
   printf("\n");
   cur = odd;
   printf("The odd list:\n%d ", cur->data); //依序找出存奇數的節點並印出
   while (cur->next != NULL) {
      cur = cur->next;
      while (cur->data % 2 == 0 && cur->next != NULL)
         cur = cur->next;
      if (cur->data % 2 != 0)
         printf("%d ", cur->data);
      else
         break;
   }
   printf("\n");
}
