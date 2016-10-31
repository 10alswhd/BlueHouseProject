#include <stdio.h> //printf(), scanf()
#include <stdlib.h> //srand(), rand(), malloc()
#include <string.h> //문자열
#include <ctype.h> //문자
#include <time.h> //time(), clock()
#include <math.h> //수학함수
//////////////////////////////////////////////////////////////
// OS, Hardware 종속 라이브러리 헤더 파일
//////////////////////////////////////////////////////////////
#include <windows.h> //윈도우즈 API
//SetConsoleCursorPosition(), GetStdHandle(), Sleep()
#include <conio.h> //getch(), kbhit()
//////////////////////////////////////////////////////////////
// 게임에 자주 사용하는 키보드 상수
//////////////////////////////////////////////////////////////
#define ESC 27 //게임 탈출
#define ENTER 13
#define SPACE 32 //총알, 점프
#define LEFT 75 //224 다음에 75
#define RIGHT 77 //224 다음에 77
#define UP 72 //224 다음에 72
#define DOWN 80 //224 다음에 80
//////////////////////////////////////////////////////////////
#define winX 30  //창의 시작 위치
#define winY 2  //창의 시작 위치
#define winWidth 10 //창의 폭
#define winHeight 20 //창의 높이
#define FREE_DROP 0 //아래 자유 낙하
#define MOVE_DOWN 1 //아래 강제 이동
#define MOVE_LEFT 2 //좌측 이동
#define MOVE_RIGHT 3 //우측 이동
#define MOVE_DROP 4 //떨어뜨리기
#define ROTATION 5 //떨어뜨리기
//////////////////////////////////////////////////////////////
// 함수 프로토타입
//////////////////////////////////////////////////////////////
void gotoXY(int x, int y); //콘솔 화면 특정 위치로 이동
void checkKey(); //키보드 처리 담당
void Display(); //화면 표시 담당, 1초에 25프레임
void Update(); //게임 객체 상태 업데이트, 시뮬레이션
void Start(); //게임 초기 상태 설정
int IsCollision(); //충돌 검사
void FixBrick(); //블록 고정하기
void NewBrick(); //새 블록 만들기
void BarCheck(); //누적된 막대 확인 제거, 점수 상승
//////////////////////////////////////////////////////////////
// 게임 객체의 구조체
//////////////////////////////////////////////////////////////
int brick_x, brick_y; //객체의 윈도우 안의 위치
int brick_shape, brick_rotation; //객체의 모양, 회전
int win[winHeight][winWidth]; //창의 내용물
int brick_action; //객체의 행동
int free_drop_delay = 20; //낙하 시간 간격
int free_drop_count; //낙하 시간 카운트 
// 객체의 모양 7개, 회전 4개, y, x
char brick[7][4][4][4]={
// ㅗ 회전 0
 0,1,0,0,
 1,1,1,0,
 0,0,0,0,
 0,0,0,0,
// ㅏ 회전 1
 0,1,0,0,
 0,1,1,0,
 0,1,0,0,
 0,0,0,0,
// ㅜ 회전 2
 0,0,0,0,
 1,1,1,0,
 0,1,0,0,
 0,0,0,0,
// ㅓ 회전 3
 0,1,0,0,
 1,1,0,0,
 0,1,0,0,
 0,0,0,0,
//Z 회전0
 0,1,1,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
//Z 회전1
 0,1,0,0,
 0,1,1,0,
 0,0,1,0,
 0,0,0,0,
//Z 회전2
 0,1,1,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
//Z 회전3
 0,1,0,0,
 0,1,1,0,
 0,0,1,0,
 0,0,0,0,
//Z 회전0
 1,1,0,0,
 0,1,1,0,
 0,0,0,0,
 0,0,0,0,
//Z 회전1
 0,1,0,0,
 1,1,0,0,
 1,0,0,0,
 0,0,0,0,
//Z 회전2
 1,1,0,0,
 0,1,1,0,
 0,0,0,0,
 0,0,0,0,
//Z 회전3
 0,1,0,0,
 1,1,0,0,
 1,0,0,0,
 0,0,0,0,
//ㄱ회전0
 1,1,0,0,
 0,1,0,0,
 0,1,0,0,
 0,0,0,0,
//ㄱ회전1
 0,0,1,0,
 1,1,1,0,
 0,0,0,0,
 0,0,0,0,
//ㄱ회전2
 0,1,0,0,
 0,1,0,0,
 0,1,1,0,
 0,0,0,0,
//ㄱ회전3
 0,0,0,0,
 1,1,1,0,
 1,0,0,0,
 0,0,0,0,
//ㄴ회전0
 0,1,1,0,
 0,1,0,0,
 0,1,0,0,
 0,0,0,0,
//ㄴ회전1
 0,0,0,0,
 1,1,1,0,
 0,0,1,0,
 0,0,0,0,
//ㄴ회전2
 0,1,0,0,
 0,1,0,0,
 1,1,0,0,
 0,0,0,0,
//ㄴ회전3
 1,0,0,0,
 1,1,1,0,
 0,0,0,0,
 0,0,0,0,
//직선 회전0
 0,1,0,0,
 0,1,0,0,
 0,1,0,0,
 0,1,0,0,
//직선 회전1
 0,0,0,0,
 1,1,1,1,
 0,0,0,0,
 0,0,0,0,
//직선 회전2
 0,1,0,0,
 0,1,0,0,
 0,1,0,0,
 0,1,0,0,
//직선 회전3
 0,0,0,0,
 1,1,1,1,
 0,0,0,0,
 0,0,0,0,
//상자 회전0
 1,1,0,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
//상자 회전1
 1,1,0,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
//상자 회전2
 1,1,0,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0,
//상자 회전3
 1,1,0,0,
 1,1,0,0,
 0,0,0,0,
 0,0,0,0
};
int GameOver = 0;
int GamePoint = 0;
//////////////////////////////////////////////////////////////
// 함수 정의 부분
//////////////////////////////////////////////////////////////
void main()
{
 Start();  //게임 초기 상태 설정
 while(!GameOver)
{
  Display(); //화면에 현재 상태 그리기
  checkKey(); //키보드 입력 처리
  Update(); //게임 객체 상태 업데이트
  Sleep(40); //40ms 잠자기
 }
}
//////////////////////////////////////////////////////////////
void gotoXY(int x, int y) //콘솔 화면 특정 위치로 이동
{
 COORD Pos = {x, y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//////////////////////////////////////////////////////////////
void Start() //게임 초기 상태 설정
{
 int x, y;
 NewBrick(); //새 개체 만들기
 free_drop_count = free_drop_delay; //20 프레임에 1회 다운
 //테트리스 윈도우 초기화
 for (x=0; x<winWidth; x++)
 {
  for(y=0; y<winHeight; y++)
  {
   if (x == 0 || x == winWidth-1 ||
    y == 0 || y == winHeight-1)
   {
    win[y][x]=2;
   } else
   {
    win[y][x]=0;
   }
  }
 }
}
//////////////////////////////////////////////////////////////
int IsCollision() //게임 객체 충돌 검사
{
 int x, y;
 for (y=0; y<4; y++)
 {
 for (x=0; x<4; x++)
 {
  if (brick[brick_shape][brick_rotation][y][x] ==1 )
  {
   if (win[brick_y+y][brick_x+x] != 0)
   {
    return 1; //충돌 있음
   }
  } 
 }
 }
 return 0; //충돌 없음
}
//////////////////////////////////////////////////////////////
void FixBrick() //게임 객체 고정
{
 int x, y;
 for (y=0; y<4; y++)
 {
 for (x=0; x<4; x++)
 {
  if (brick[brick_shape][brick_rotation][y][x] ==1 )
  {
   win[brick_y+y][brick_x+x] = 1;
  } 
 }
 }
}
//////////////////////////////////////////////////////////////
void NewBrick() //새로운 객체 만들기
{
 srand(time(NULL)); //난수 발생 시작점 초기화
 brick_x = winWidth/2; //객체의 x 위치
 brick_y = 1; //객체의 y 위치
 brick_shape = rand()%7; //모양 0 ~ 6
 brick_rotation = 0; //회전 없음
 brick_action = FREE_DROP;
}
//////////////////////////////////////////////////////////////
void BarCheck() //누적 블록 제거 점수 올리기
{
 int x, y, bar, i, j;
 for(y=1; y<winHeight-1; y++)
 {
  bar = 0;
  for (x=1; x<winWidth-1; x++)
  {
   bar += win[y][x];
  }
  if (bar == winWidth-2)
  {
   GamePoint++;
   if(GamePoint % 20 == 0) free_drop_delay--;
   if(free_drop_delay < 0) free_drop_delay = 0;
   for (i=y-1; i>0; i--)
   {
    for (j=1; j<winWidth-1; j++)
    {
     win[i+1][j] = win[i][j];
    }
   }
  }
 }
}
//////////////////////////////////////////////////////////////
void Display() //화면에 현재 상태 그리기
{
 int x, y;
 //창 그리기
for (y=0; y<winHeight; y++)
 {
 gotoXY(winX, winY+y);
  for (x=0; x<winWidth; x++)
  {
  if(win[y][x]==1) printf("■");
  else if(win[y][x]==2) printf("□");
  else printf("·");
  }
 printf("\n");
 }
 //블록 그리기
 for (y=0; y<4; y++)
 {
 for (x=0; x<4; x++)
 {
  if (brick[brick_shape][brick_rotation][y][x] ==1 )
  {
    gotoXY(winX + (brick_x + x)*2, winY + brick_y + y);
    printf("■");
  } 
 }
 }
 //점수 표시
 gotoXY(30, 25);
 printf("Point = %d",GamePoint);
}
//////////////////////////////////////////////////////////////
void Update() //게임 객체 상태 업데이트
{
  switch (brick_action)
  {
   case MOVE_DROP:
    do{
     brick_y++;
    }while(!IsCollision());
    brick_y--;
    if (brick_y == 1) GameOver = 1;
  FixBrick(); //개체 고정
  BarCheck(); //누적 상태 확인
  NewBrick(); //새 개체 만들기
  free_drop_count = free_drop_delay; //20 프레임에 1회 다운
   brick_action = FREE_DROP;
      break;
   case MOVE_LEFT:
    brick_x--;
    if (IsCollision()) brick_x++;
   brick_action = FREE_DROP;
      break;
   case MOVE_RIGHT:
    brick_x++;
    if (IsCollision()) brick_x--;
   brick_action = FREE_DROP;
      break;
   case MOVE_DOWN:
    brick_y++;
    if (IsCollision())
    {
     brick_y--;
     if (brick_y == 1) GameOver = 1;
   FixBrick(); //개체 고정
   BarCheck(); //누적 상태 확인
   NewBrick(); //새 개체 만들기
   free_drop_count = free_drop_delay; //20 프레임에 1회 다운
    }
   brick_action = FREE_DROP;
      break;
   case FREE_DROP:
  free_drop_count--;
  if(free_drop_count < 0)
  {
   free_drop_count = free_drop_delay;
   brick_action = MOVE_DOWN;
  }
      break;
   case ROTATION:
   brick_rotation++;
   if(brick_rotation > 3) brick_rotation = 0;
    if (IsCollision())
    {
     brick_rotation--;
   if(brick_rotation < 0) brick_rotation = 3;
    }
   brick_action = FREE_DROP;
      break;
   default :
      break;
  }
}
//////////////////////////////////////////////////////////////
void checkKey() //키보드 처리 담당
{
 int key;
 if(kbhit() != 0) //키보드 눌림 확인
 {
  key=getch(); //일단 한 글자 읽기
  if (key == 224) //키보드 스캔 코드 224이면 기능키
  {
   key=getch(); //다음 한 글자 추가 읽기
  }
  switch (key)
  {
   case ESC:
    GameOver = 1;
      break;
   case ENTER:
      break;
   case SPACE:
   brick_action = MOVE_DROP;
      break;
   case LEFT:
   brick_action = MOVE_LEFT;
      break;
   case RIGHT:
   brick_action = MOVE_RIGHT;
      break;
   case UP:
   brick_action = ROTATION;
      break;
   case DOWN:
   brick_action = MOVE_DOWN;
      break;
   default :
   brick_action = FREE_DROP;
      break;
  }
 }
}
