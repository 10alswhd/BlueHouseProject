#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
void make_num(int *num); 
int compare(int* input, int* num); 
void result(int* num, int strike, int cnt); 
int restart_check(); 
int main() { 
   int num[3]={0}; 
   int input[3]={0}; 
   int i=0, j=0; 
   int cnt=1; 
   int strike=0; 
   int re_chk=0; 
   while(1) { 
      printf("====================== 야구게임 ======================\n"); 
      printf("3개의 수를 맞춰라!!\n"); 
      printf("숫자와 위치가 맞을경우 스트라이크,\n숫자는 맞는데 위치가 틀린경우 볼!\n"); 
      printf("기회는 9번!! start!!\n"); 
      printf("======================================================\n"); 
      cnt=1; 
      make_num(num); // 랜덤한 숫자 생성 
      printf("num f : %d, s : %d, t : %d\n", num[0], num[1], num[2]); 
      while(cnt < 10) { 
         printf("입력 : "); 
         // 사용자에게 숫자를 입력받음. 숫자외 다른수를 입력했을경우 
         if(scanf("%d%d%d", &input[0], &input[1], &input[2]) != 3) { 
            printf("잘못입력하였습니다. 다시 입력하세요.\n"); 
            fflush(stdin); 
            continue; 
         } 
         // 예외처리 / 같은수를 입력했거나, 1~9사이가 아닌 수를 입력했을경우 
         if( (input[0] == input[1] || input[0] == input[2] || input[1] == input[2]) || 
         (input[0] < 1 || input[1] < 1 || input[2] < 1 || input[0] > 10 ||  input[1] > 10 ||  input[2] > 10) ){ 
            printf("잘못입력하였습니다. 다시 입력하세요.\n"); 
            continue; 
         } 
         strike = compare(input, num); // 세가지 숫자를 비교 
         result(num, strike, cnt); // 결과 출력 
         if(strike == 3) 
         break; 
         cnt++;  
      } 
      //몇번만에 맞췄는지 출력 
      printf( "당신은 %d번만에 맞췄습니다\n", cnt ); 
      // 재시작 여부 확인 
      re_chk = restart_check(); 
      if( (strike == 3 || cnt == 10) && (re_chk == 1) ) { 
         system("cls"); 
         continue; 
      } 
      else 
      break; 
   } 
   return 0; 
} 
// 서로 동일하지 않은 3개의 랜덤한 수를 생성하는 함수 
void make_num(int *num) 
{ 
   int i=0; 
   int j=0; 
   // 3개의 수를 랜덤하게 생성 
   srand(time(NULL)); 
   for(i=2; i>=0; i--) { 
      num[i] = rand() % 9 + 1; 
      while(num[i] == num[i+1] || num[i] == num[i+2]) 
      num[i] = rand() % 9 + 1; 
   } 
} 
// 생성한 수와 사용자 입력값을 비교하는 함수 
int compare(int* input, int* num) 
{ 
   int i, j; 
   int strike=0, ball=0; 
   // input과 num 값을 비교하여 strike, ball을 구함 
   for(i=0, j=0; i<3; i++) { 
      for(j=0; j<3; j++) { 
         if(input[i] == num[i]) { 
            strike++; 
            break; 
         } 
         else if(input[i] == num[j]) 
         ball++; 
      } 
   } 
   printf("%d strike, %d ball!!\n", strike, ball); // strike, ball 갯수를 출력 
   return strike; // strike 갯수를 반환 
} 
// 결과를 출력하는 함수 
void result(int* num, int strike, int cnt) 
{  
   // 숫자 세개를 다 맞췄을 경우 맞춘 횟수에 따라 다른 메시지를 출력 
   if(strike == 3) { 
      if(cnt <= 2) 
      printf("와우! 최고다!!\n"); 
      else if(cnt <= 5) 
      printf("와우! 잘한다!!\n"); 
      else if(cnt <= 9) 
      printf("겨우! 이겼네!!\n"); 
   } 
   // 숫자 세개를 다 맞추지 못했을 경우 남은 횟수를 출력 
   else 
   printf("%d번 남았습니다.\n", 9-cnt); 
   //9번 모두 맞추지 못했을 경우 패배하였다는 메시지 출력 
   if(cnt == 10) 
   printf("\n당신이 졌어요. ㅠㅠ "); 
   // 모두 맞췄거나 9회를 초과한 경우 정답 출력 
   if(strike == 3 || cnt == 10) 
   printf("정답은 %d, %d, %d입니다.\n\n", num[0], num[1], num[2]); 
} 
// 재시작 여부 확인 함수 
int restart_check() 
{ 
   char select='n'; 
   int rlt=0; 
   printf("다시 시작할까요?(yes : 'y', no : 'n') : "); 
   fflush(stdin); 
   scanf("%c", &select); 
   if(select == 'y') 
   rlt=1; 
   else if(select == 'n') 
   rlt=0; 
   else 
   rlt=0; 
   return rlt; 
} 
