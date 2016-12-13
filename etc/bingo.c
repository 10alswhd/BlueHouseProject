#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
 
#define MAX 5
#define WHITE 15
#define YELLOW 14
 
 
void textcolor(int color_number); // 텍스트 칼라 출력
void gotoxy(int x, int y); // 좌표 이동
int baserand(int x, int y); // 랜덤 범위 지정
 
// 초기값 설정
void InitCount(int Player[MAX][MAX] , int Com[MAX][MAX]);
 
// MAP 설정
void MixMAP(int Player[MAX][MAX]);
int SearchMAP(int Player[MAX][MAX] ,int Num);
void printMAP(int Player[MAX][MAX]);
int CheckMAP(int Player[MAX][MAX]);
 
// 승리조건
void Winner(int flag , int Player[MAX][MAX],int Com[MAX][MAX]);
 
 
 
 
int main(void){
 
        int Player[MAX][MAX];
        int Com[MAX][MAX];
        int playerChk,comChk;
        int Num;       
 
        InitCount(Player,Com);
       
        MixMAP(Player);
 
        while(1){
                gotoxy(0,0);
 
                // 컴퓨터들 출력
                textcolor(WHITE);
                printf(" ====== Player ====== \n");
                printMAP(Player);
                textcolor(WHITE);
                printf(" ===== Computer ===== \n");
                printMAP(Com);         
 
                textcolor(WHITE);
                printf(" > ");
                scanf("%d",&Num);
 
                if( SearchMAP(Player,Num) == 0){
                        printf("잘못입력하셨습니다. \n");                     
                        system("pause");
                        system("cls");
                        continue;
                }
 
                SearchMAP(Com,Num);
 
                // 컴퓨터 턴
                while( 1 ){
                        Num = baserand(1,MAX*MAX);
                        if(SearchMAP(Com, Num) ==1 ){
                                SearchMAP(Player, Num);
                                break;
                        }
                }
 
                playerChk = CheckMAP(Player);
                comChk = CheckMAP(Com);
 
                printf("Player Check = %d \n",playerChk);
                printf("Com Check = %d \n",comChk);
 
                if(playerChk >= MAX && comChk >= MAX){
                        if( playerChk > comChk){
                                Winner(0,Player,Com); // 내가 이겼을 때
                        }else if( playerChk < comChk) {
                                Winner(1,Player,Com); // 내가 졌을 때
                        }else{
                                Winner(2,Player,Com); // 배겼을 때
                        }
                }else  if(playerChk >= MAX){
                        Winner(0,Player,Com); // 내가 이겼을 때
                }else  if(comChk >= MAX){
                        Winner(1,Player,Com); // 내가 졌을 때
                }
 
                system("pause");
                system("cls");
        }
        return 0;
}
 
// 텍스트 칼라 출력
void textcolor(int color_number)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
};
// 좌표 이동
void gotoxy(int x, int y)
{
     COORD Cur;
     Cur.X=x;
     Cur.Y=y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
// 랜덤 범위 지정
int baserand(int x, int y){
 
        static int z = 0;
        int tmp;
        if(z==0){
                srand((int)time(NULL));
                rand();rand();rand();rand();
                srand(rand());
                z=1;
        }
 
        tmp = rand()%(y-x+1)+x;
        return tmp;
}
 
void printMAP(int Player[MAX][MAX]){
        int i,j;
        for(i=0;i<MAX;i++){
                for(j=0;j<MAX;j++){
                        if(Player[i][j] == 0){
                                textcolor(YELLOW);
                                printf("%4s","♥");
 
                        }else{
                                textcolor(WHITE);
                                printf("%4d",Player[i][j]);
                        }
                }
                printf("\n");
        }
}
 
 
void MixMAP(int Player[MAX][MAX]){
 
        int i;
        int x1,y1;
        int x2,y2;
        int tmp;
 
        printMAP(Player);
 
        for(i=0;i< 10*MAX ;i++){
 
                x1 = baserand(0,MAX-1);
                y1 = baserand(0,MAX-1);
 
                x2 = baserand(0,MAX-1);
                y2 = baserand(0,MAX-1);
 
                // 두 값을 서로 바꾸는 코드
                tmp = Player[x1][y1];
                Player[x1][y1] = Player[x2][y2];
                Player[x2][y2] = tmp;
 
                gotoxy(0,0);
                printMAP(Player);              
       
                Sleep(10);
        }
        system("pause");
        system("cls");
       
}
 
int SearchMAP(int Player[MAX][MAX] ,int Num){
 
        int i,j;
        int flag = 0;
 
        for(i=0;i<MAX;i++){
                for(j=0;j<MAX;j++){
                        if(Player[i][j] == Num){
                                flag = 1;
                                Player[i][j] = 0;
                        }
                }
        }
 
        return flag;
}
 
int CheckMAP(int Player[MAX][MAX]){
        int i,j;
        int rowsFlag = 0;
        int columnFlag = 0;
        int crossleftFlag = 0;
        int crossrightFlag = 0;
        int check = 0;         
 
        for(i=0;i<MAX;i++){
                rowsFlag = 0;
                columnFlag = 0;
 
                for(j=0;j<MAX;j++){
                        if(Player[i][j] == 0){
                                rowsFlag++;
                        }
                        if(Player[j][i] == 0){
                                columnFlag++;
                        }
                }
                // 가로체크
                if(rowsFlag == MAX){
                        check++;
                }
                // 세로체크
                if(columnFlag == MAX){
                        check++;
                }
                // 대각선 왼쪽에서 오른쪽
                if(Player[i][i] == 0){
                        crossleftFlag++;
                }
                // 대각선 오른쪽에서 왼쪽
                if(Player[MAX-1-i][i] == 0){
                        crossrightFlag++;
                }
        }
 
        if(crossleftFlag == MAX){
                check++;
        }
 
        if(crossrightFlag == MAX){
                check++;
        }
 
        return check;
}
 
void Winner(int flag , int Player[MAX][MAX],int Com[MAX][MAX]){
        gotoxy(0,0);
        textcolor(WHITE);
        printf(" ====== Player ====== \n");
        printMAP(Player);
        textcolor(WHITE);
        printf(" ===== Computer ===== \n");
        printMAP(Com);         
        gotoxy(0,MAX*2+5);
        switch(flag){
                case 0:
                        printf("당신이 이겼습니다. \n");
                        break;
                case 1:
                        printf("당신이 졌습니다. \n");
                        break;
                case 2:
                        printf("비겼습니다. \n");
                        break;
        }
        exit(0);
 
}
 
void InitCount(int Player[MAX][MAX] , int Com[MAX][MAX]){
 
        int i,j;
        int count =1 ;
        for(i=0;i<MAX;i++){
                for(j=0;j<MAX;j++){
                        Player[i][j] = count;
                        Com[i][j] = count;
                        count++;
                }
        }
}
 
