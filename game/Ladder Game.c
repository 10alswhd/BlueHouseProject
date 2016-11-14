#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
 
#define RED 12
#define WHITE 15
 
#define LINE 6           // 라인수를 증가 시킬 수 있습니다.
#define MAX (LINE*4)
 
void textcolor(int color_number); // 텍스트 칼라 출력
void gotoxy(int x, int y); // 좌표 이동
int baserand(int x, int y); // 랜덤 범위 지정
 
void VerticalSet(int MAP[20][MAX]);
void HorizonSet(int MAP[20][MAX]);
 
void PrintLine(int MAP[20][MAX]);
 
void LadderStart( int MAP[20][MAX] , int Select );
 
int main(void){
 
        int MAP[20][MAX];
        int Select;
        printf("출발점 설정 ( 1 ~ %d ) : ",LINE);
        scanf("%d",&Select);
        Select--;
        system("pause");
        system("cls"); 
       
        // 세로선 설정
        VerticalSet(MAP);
        // 가로선 설정
        HorizonSet(MAP);
       
        PrintLine(MAP);        
 
        LadderStart(MAP,Select);       
 
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
 
void VerticalSet(int MAP[20][MAX]){
        int i,j;
        // 직선 긋기
        for(i=0;i<20;i++){
                for(j=0;j<MAX;j++){
                        if( (j%4 ==0) ){
                                MAP[i][j] = 5;    
                        }else{
                                MAP[i][j] = 0;
                        }
                }
        }
}
void HorizonSet(int MAP[20][MAX]){
        int i,j;       
        int x,y;
        for(i=0;i<20;i++){
                // 선 긋기
                x = baserand(0,LINE-2)*4;
                y = baserand(1,19);  
                if( MAP[y][x+4] == 5 && MAP[y][x-4] == 5 ){
                        j=x;
                        MAP[y][j++] = 25;
                        for(;j<x+4;j++){
                                MAP[y][j] = 6;
                        }
 
                        MAP[y][j] = 23;
                }
        }
}
 
void PrintLine(int MAP[20][MAX]){
        int i,j;
        for(i=0;i<20;i++){
                for(j=0;j<MAX;j++){
                        switch(MAP[i][j]){
                        case 0:
                                printf(" ");
                                break;
                        case 6:
                                printf("%c",MAP[i][j]);        
                                break;    
                        default:
                                printf("%c",MAP[i][j]);
                        }
                }
                printf("\n");
        }
        printf("\n");
        for(i=1;i<LINE+1;i++){
                printf("%-4d",i);
        }
        printf("\n\n");
}
 
void LadderStart( int MAP[20][MAX] , int Select ){
        int i;
        int x,y;
        x = Select*4,y= 0;
        for(y=0;y<20;y++){
                if( MAP[y][x] == 25 ){
                        for(i = x; i < x + 4; i++){
                                Sleep(200);
                                gotoxy(i,y);
                                textcolor(RED);
                                printf("%c",MAP[y][i]);
                        }
                        x = i;
                }else if( MAP[y][x] == 23 ){
                        for(i = x; i > x - 4; i--){
                                Sleep(200);
                                gotoxy(i,y);
                                textcolor(RED);
                                printf("%c",MAP[y][i]);
                        }
                        x = i;
                }
                Sleep(200);
                gotoxy(x,y);
                textcolor(RED);
                printf("%c",MAP[y][x]);
        }
 
        textcolor(WHITE);
        gotoxy(0,22);
        printf("%d 번 당첨 \n",(x/4)+1);
}
