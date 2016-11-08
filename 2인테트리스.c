#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define LEFT 75  //키보드값들 
#define RIGHT 77 //우로 이동 
#define ROTATE 72 //회전 
#define UP_ROTATE 100 //회전 
#define DOWN 80 //soft drop
#define SPACE 32//hard drop

#define SINGLE 0 
#define PLAYER1 1
#define PLAYER2 2
#define COMPUTER 3

#define ACTIVE_BLOCK ((block.type+11)*(-1))
#define CEILLING -1
#define EMPTY 0
#define WALL 1
#define INACTIVE_BLOCK (block.type+11)

void gotoxy(int x,int y) { //gotoxy함수 
	COORD pos={2*x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c){ //커서 안보이게 하는 함수 
     CONSOLE_CURSOR_INFO CurInfo;
 
     switch (c) {
     case NOCURSOR:
          CurInfo.dwSize=1;
          CurInfo.bVisible=FALSE;
          break;
     case SOLIDCURSOR:
          CurInfo.dwSize=100;
          CurInfo.bVisible=TRUE;
          break;
     case NORMALCURSOR:
          CurInfo.dwSize=20;
          CurInfo.bVisible=TRUE;
          break;
     }
     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

class Blocks{
public:
	Blocks(void){ //생성자
		type_next=rand()%7;
	}
	static const int shape[7][4][4][4]; //블록모양 
	int x; //x좌표
	int y; //y좌표
	int type; //블록 종류
	int rotation; //블록 회전값
	int type_next; //다음 블록값
	int getColor(int num); //블록색깔 구하는 함수
};
const int Blocks::shape[7][4][4][4]={
	{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
	{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
	{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
	{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
	{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
	{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
	{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},{0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}
};
int Blocks::getColor(int num){
	if(num<0) num*=(-1);
	return num-9;
}

class Tetris{
public:
	Tetris(int game_x,int game_y,int status_x,int status_y, int owner); //생성자 각종변수 초기화
	
	int fCnt; // 프레임카운터. 0이되면 블록이 한칸 drop되고 speed[level]로 reset이 됨. 즉 이 값이 작을수록 게임이 빨라짐.
	int owner; // 게임의 플레이어. Player(싱글), Player 1, Player 2, Computer중 하나.(싱글모드 미구현)
	int score; // 점수(미구현)
	int lineCnt; // 몇줄 없앴는지 기억하는 변수

	static const int speed[11]; //게임속도 저장배열
		int level; // 레벨

	int game_x;   // 좌표변수
	int game_y;   //
	int status_x; //
	int status_y; //

	static const int WIDTH=11;  // 게임 가로 크기
	static const int HEIGHT=23; // 게임 세로 크기

	int gameOrg[HEIGHT][WIDTH]; // 게임판            /*게임판에서 게임이 진행되고, cpy에는 이전 게임 frame이 기록되어 있음.*/
	int gameCpy[HEIGHT][WIDTH]; // 게임판 비교용 cpy /*cpy와 비교하여 변화가 있는 부분만 게임을 새로 그림                  */
		void resetGameCpy(void){ // gameCpy를 리셋하는 함수
			for(int i=0;i<HEIGHT;i++) for(int j=0;j<WIDTH;j++) gameCpy[i][j]=999;
		}
	void drawGame(void); //gameOrg와 gameCpy를 비교하여 게임판을 그림

	void newBlock(void); //새로운 블록을 하나 생성
		Blocks block;    //블록 변수
		void move_block(int dir); //블록을 이동시킴
		void dropBlock(void); //일정시간이후 항상 블록을 한칸 밑으로 이동
		bool checkCrush(int x, int y, int rotation); //블록 이동전에 이동이 가능한지 판별
			bool crush_on; // 충돌상태이면 true
	
	void initialGame(void); //게임판을 초기화

	void gameOver(void); // 게임오버를 진행
		bool gameOver_on; // 게임오버시 true
		int gameOverCnt; // 게임오버 애니메이션 카운트
		int gameOverP; // 회색으로 바꾼 줄수를 기록
		
	void gameDelay(int cnt); //게임 delay생성
		bool gameDelay_on; // 생성되면 true
		int gameDelayCnt; // delay 카운트
		void gameDelay(void); //카운트가 0이 되면 delay를 끔

	void gameMsg(int x, int y, int type, int val=0); //게임판에 메세지를 생성
		int gameMsgCnt; //메세지 카운트
		void gameMsg(void); //카운트가 0이되면 gameCpy를 리셋하여 메세지를 지움

	void getKey(void); //keyCnt가 0일때 키입력받음
		int keyCnt; // 키입력 받는 속도 조절변수
		bool upRotate_on;
		
	void checkLine(void); // 줄이 가득찼는지 확인하고 줄을 지움
		int pushAttackReg[HEIGHT][WIDTH]; //콤보시에 지운 줄을 저장(밑에서부터 채워짐) /* pushAttackReg에 값이 있을 경우 BattleTetrisManager가 */
		int pushAttackRegP; //pushAttackReg의 높이를 저장하는 변수                     /* 상대방의 getAttackReg로 이동                         */
	
	void getAttack(void); // getAttackReg를 확인하여 받을 줄이 있으면 추가
		int getAttackReg[HEIGHT][WIDTH]; //상대방으로 부터 받는 줄을 임시 저장하는 배열(밑에서부터 채워짐)
		int getAttackRegP; //getAttackReg의 높이를 저장하는 변수
		int attackQueue_x; //몇줄 공격받는지를 화면에 나타내는 x좌표
	
	int comOutput; //컴퓨터가 getKey로 전달하는 입력값
		void comCheck(void); //블록을 놓을 위치 및 path찾는 함수
			int comX[10]; //블록 path X좌표모음집(현재 [0]과 [1]만 사용)
			int comY[10]; //블록 path Y좌표모음집(현재 [0]과 [1]만 사용)
			int comR[10]; //블록 path 회전값모음집(현재 미사용)
			int comXYRP; //path순서(pointer) 저장
			int comGameValue[HEIGHT][WIDTH]; //현재 게임판의 좌표value를 저장
			int comGameUnder[HEIGHT][WIDTH]; //현재 게임판에서 블록아래 빈공간이 있는 곳을 저장
			bool comCheck_on; //블록 놓을 위치 및 path 재계산이 필요한 경우 true
			int comCheckAroundValue(int x, int y, int rotation); //블록의 주변값을 더해 최종 값 계산
};
const int Tetris::speed[11]={20,20,15,10,20,10,5,15,10,2,1}; //속도 저장

int Tetris::comCheckAroundValue(int x, int y, int rotation){
	int sum=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){ 
			if(block.shape[block.type][rotation][i][j]==1){
				for(int k=0;k<4;k++){
					switch(k){
					case 0:
						if(((i==0)&&(comGameValue[y+i-1][x+j]>0)) || 
							((i!=0)&&(block.shape[block.type][rotation][i-1][j]!=1)&&(comGameValue[y+i-1][x+j]>0))) sum+=comGameValue[y+i-1][x+j];
						break;
					case 1:
						if((i==4)|| 
							(block.shape[block.type][rotation][i+1][j]!=1)) sum+=comGameValue[y+i+1][x+j];
						break;
					case 2:
						if(((j==0)&&(comGameValue[y+i][x+j-1]>0)) || 
							((j!=0)&&(block.shape[block.type][rotation][i][j-1]!=1)&&(comGameValue[y+i][x+j-1]>0))) sum+=comGameValue[y+i][x+j-1];
						break;
					case 3:
						if(((j==4)&&comGameValue[y+i][x+j+1]>0) || 
							((j!=4)&&(block.shape[block.type][rotation][i][j+1]!=1)&&(comGameValue[y+i][x+j+1]>0))) sum+=comGameValue[y+i][x+j+1];
						break;
					}
				}
			}
		}
	}	
	return sum;
}
void Tetris::comCheck(void){
	int val=0;

	if(comCheck_on==true){
		for(int i=0;i<10;i++){ //초기화
			comX[i]=0;
			comY[i]=0;
			comR[i]=0;
		}
		comXYRP=0;

		for(int i=0;i<HEIGHT;i++){ //value표(+값) 구하기
			for(int j=0;j<WIDTH;j++){
				if(gameOrg[i][j]>0) comGameValue[i][j]=i;
				else comGameValue[i][j]=0;
			}
		}
		for(int i=0;i<HEIGHT-1;i++){ //value표(-값) 구하기
			for(int j=0;j<WIDTH;j++){
				if(comGameValue[i][j]==0&&(comGameValue[i][j-1]>0||comGameValue[i][j+1]>0)) comGameValue[i][j]=(-i);
			}
		}
		for(int i=0;i<HEIGHT;i++){ //under표 초기화
			for(int j=0;j<WIDTH;j++){
				comGameUnder[i][j]=0;
			}
		}
		for(int i=0;i<HEIGHT;i++){ //under mark하기
			for(int j=1;j<WIDTH-1;j++){
				if(gameOrg[i][j]>0&&gameOrg[i-1][j]==0){
					for(int k=i-1;k>0;k--){
						if(gameOrg[k][j]>0){
							for(int m=i-1;m>k;m--) comGameUnder[m][j]=1;
							break;
						}
					}
				}
			}
		}

		for(int i=0;i<21;i++){ // 놓을 위치 및 path찾기
			for(int j=0;j<WIDTH;j++){
				for(int k=0;k<4;k++){		

					if(checkCrush(j,i+1,k)==false&&checkCrush(j,i,k)==true&&comCheckAroundValue(j,i,k)>val){
						bool onUnder=false;//onUnder는 hard drop이 가능한지 판별: false면 가능 , true면 불가능(위에 crush가 있음)						
						for(int m=0;m<4;m++){ 
							for(int n=0;n<4;n++){
								if(block.shape[block.type][k][m][n]==1&&comGameUnder[i+m][j+n]==1){
									onUnder=true;
								}
							}
						}					
						if(onUnder==false){ // hard drop이 가능하면 단일path		
							comXYRP=0;
							val=comCheckAroundValue(j,i,k);
							comX[0]=j;
							comY[0]=i;
							comR[0]=k;						
						}
						if(onUnder==true){ // hard drop이 불가능하면 우회합니다.
							comXYRP=0;

							if(checkCrush(j+1,i,k)==false&&checkCrush(j-1,i,k)==false&&checkCrush(j,i-1,k)==false) break;

							int tempX1=j;
							int tempY1=i;
							int tempX2=j;
							int tempY2=i;
							int tempXYRP=0;

							bool underStuck=true; //이 공간이 갇혀 있는지 아닌지를 판별. 무조건 갇혀 있다고 생각하고 출구가 있으면 false
							for(int s=1;s>-2;s-=2){ //현재 한번 우회해서 갈수 있는지만 판별할수 있음..
								for(int x=0;x<WIDTH;x++){
									if(underStuck==false) break;
									for(int y=0;y<HEIGHT;y++){
										if(tempY1-y==0){
											underStuck=false;
											tempXYRP++;
											comX[tempXYRP]=j+x*s;
											comY[tempXYRP]=tempY1;
											comR[tempXYRP]=k;
											break;
										}
										else if(checkCrush(j+x*s,tempY1-y,k)==true){
											tempX2=j+x*s;
											tempY2=tempY1-y;
										}
										else if(checkCrush(tempX1+x*s,tempY1-y,k)==false) break;
										
									}
									if(tempX1==tempX2 && tempY1==tempY2 && x!=0) break;
									else {
										tempX1=tempX2;
										tempY1=tempY2;
									}
								}
							}

							if(underStuck==false){ //1차로 우회가 가능한 경우 최종 path업데이트
								val=comCheckAroundValue(j,i,k);							
								comX[0]=j;
								comY[0]=i;
								comR[0]=k;	
								comXYRP=tempXYRP;
							}
						}
					}
				}
			}
		}
		comCheck_on=false;
	}
//실제 path로 찾아가게 하는 부분
	if(block.rotation!=comR[comXYRP]) comOutput=ROTATE;
	else if(comX[comXYRP]>block.x) comOutput=RIGHT;
	else if(comX[comXYRP]<block.x) comOutput=LEFT;
	else if(comX[comXYRP]==block.x) if(comXYRP==0) comOutput=SPACE; else  comOutput=DOWN;

	if(comX[comXYRP]==block.x && comY[comXYRP]==block.y && comR[comXYRP]==block.rotation && comXYRP>0) comXYRP--;
}
Tetris::Tetris(int game_x,int game_y,int status_x,int status_y, int owner){ // 변수 초기화
	level=1;
	score=0;
	lineCnt=0;
	keyCnt=0;
	fCnt=speed[level];

	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			gameOrg[i][j]=0;
			gameCpy[i][j]=NULL;
			pushAttackReg[i][j]=-1;
			getAttackReg[i][j]=-1;
		}
	}	
	pushAttackRegP=HEIGHT-1;
	getAttackRegP=HEIGHT-1;

	this->game_x=game_x;
	this->game_y=game_y;
	this->status_x=status_x;
	this->status_y=status_y;
	this->owner=owner;
	
	upRotate_on=false;
	crush_on=false;
	gameDelay_on=false;
	gameDelayCnt=-1;
	gameOver_on=false;
	gameOverCnt=-1;
	gameMsgCnt=-1;
	comCheck_on=true;
	
	initialGame(); //게임판을 그림
	newBlock(); //새로운 블록 생성
}
void Tetris::initialGame(void){
	int i,j;
//게임판을 그림//
	for(j=1;j<WIDTH;j++){ 
		gameOrg[3][j]=CEILLING;
	}
	for(i=1;i<HEIGHT-1;i++){ 
		gameOrg[i][0]=WALL;
		gameOrg[i][WIDTH-1]=WALL;
	}
	for(j=0;j<WIDTH;j++){
		gameOrg[HEIGHT-1][j]=WALL;
	}
//status 표시//
	gotoxy(status_x, status_y);
	switch(owner){
	case 0:
		printf("< PLAYER >");
		attackQueue_x=game_x-1;
		break;
	case 1:
		printf("<PLAYER1>");
		attackQueue_x=game_x-1;
		break;
	case 2:
		printf("<PLAYER2>");
		attackQueue_x=game_x+WIDTH;
		break;
	case 3:
		printf("<COMPUTER>");
		attackQueue_x=game_x+WIDTH;
		break;
	}
	gotoxy(status_x, status_y+1);
	printf("Next:");
	gotoxy(status_x, status_y+6);
	if(level==10) printf("Level:MAX");
	else printf("Level:%2d",level);
	gotoxy(status_x, status_y+7);
	printf("Speed:%2d",speed[level]);
}
void Tetris::getKey(){ //키입력받음
	dropBlock();
	if(keyCnt>0){
		keyCnt--;
		return;
	}
	if(owner==COMPUTER)comCheck();

	keyCnt=3; //3 게임프레임마다 키입력 한번씩 받음. 매 프레임마다 키입력을 받으면 너무 빨리 움직임

	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_LEFT)) || 
		(owner==PLAYER1&&GetAsyncKeyState('F')) ||
		(owner==COMPUTER&&comOutput==LEFT))
		if(checkCrush(block.x-1,block.y,block.rotation)==true) move_block(LEFT); 
	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_RIGHT)) || 
		(owner==PLAYER1&&GetAsyncKeyState('H')) ||
		(owner==COMPUTER&&comOutput==RIGHT))
		if(checkCrush(block.x+1,block.y,block.rotation)==true) move_block(RIGHT);
	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_DOWN)) || (owner==PLAYER1&&GetAsyncKeyState('G')) ||
		(owner==COMPUTER&&comOutput==DOWN)) 
		if(checkCrush(block.x,block.y+1,block.rotation)==true) move_block(DOWN);
	if(((owner==SINGLE||owner==PLAYER2)&&GetAsyncKeyState(VK_UP)) || (owner==PLAYER1&&GetAsyncKeyState('T')) ||
		(owner==COMPUTER&&comOutput==ROTATE)) {
		if(checkCrush(block.x,block.y,(block.rotation+1)%4)==true) move_block(ROTATE);
		else if(crush_on==true&&checkCrush(block.x,block.y-1,(block.rotation+1)%4)==true) move_block(UP_ROTATE); //한칸위로 올려서 회전가능할때
	}
	if((owner==SINGLE&&(GetAsyncKeyState(VK_SPACE)||GetAsyncKeyState('L'))) || 
		(owner==PLAYER2&&GetAsyncKeyState('L')) || 
		(owner==PLAYER1&&GetAsyncKeyState('Q')) ||
		(owner==COMPUTER&&comOutput==SPACE)){
		while(crush_on==false){
			dropBlock();
			score+=level;
		}
		fCnt=0;
	}

///* Z키를 누르면 막대가 나오는 cheat코드
	if(GetAsyncKeyState('Z')){
		block.type_next=1;
	}
//*/
}
void Tetris::move_block(int dir){ 
	int i,j;
//현재좌표의 블록을 지움//	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j]=EMPTY;
		}
	}
//이동방향에 따라 새로운 블록을 그림//
	switch(dir){
	case LEFT:
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j-1]=ACTIVE_BLOCK;
			}
		}
		block.x--;
		break;
	case RIGHT: 
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j+1]=ACTIVE_BLOCK;
			}
		}
		block.x++;		
		break;
	case DOWN:
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i+1][block.x+j]=ACTIVE_BLOCK;
			}
		}
		block.y++;		
		break;
	case ROTATE:
		block.rotation=(block.rotation+1)%4;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j]=ACTIVE_BLOCK;
			}
		}
		break;
	case UP_ROTATE: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 이를 동작시키는 특수동작 
		block.rotation=(block.rotation+1)%4;
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i-1][block.x+j]=ACTIVE_BLOCK;
			}
		}
		block.y--;
		upRotate_on=true;
		break;
	}
}
void Tetris::checkLine(void){
	int i, j;
	
	int	block_amount; //한줄의 블록갯수를 저장하는 변수 
	int combo=0; //콤보갯수 저장하는 변수 지정및 초기화 
	
	for(i=HEIGHT-2;i>3;){ //i=HEIGHT-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사 
		block_amount=0;
		for(j=1;j<WIDTH-1;j++){ 
			if(gameOrg[i][j]>0) block_amount++;
		}
		if(block_amount==WIDTH-2){
			score+=100*level;//점수는 미구현
			lineCnt++;
			combo++; 

			if(pushAttackRegP>0){ //일단 줄삭제가 있으면 attack에 push함
				for(int m=1;m<WIDTH-1;m++){
					if(m>block.x&&m<block.x+4&&block.shape[block.type][block.rotation][i-block.y][m-block.x]==1) pushAttackReg[pushAttackRegP][m]=0;
					else pushAttackReg[pushAttackRegP][m]=16;
				}
				pushAttackRegP--;
				block.y++;
			}

			for(int k=i;k>1;k--){ //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) 
				for(int l=1;l<WIDTH-1;l++){
					if(gameOrg[k-1][l]!=CEILLING) gameOrg[k][l]=gameOrg[k-1][l];
					if(gameOrg[k-1][l]==CEILLING) gameOrg[k][l]=EMPTY; //윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
				}
			}
		}
		else i--;
	}
//콤보확인//
	if(combo){ 
		if(combo>1){ //2콤보이상인 경우 메세지를 띄움
			drawGame();
			gameMsg((WIDTH/2)-1,block.y-2,0,combo);
			score+=(combo*level*100);
		} else { //콤보가 1일때(콤보가 아닐때) attack reg를 지움
			if(pushAttackRegP>0){
				pushAttackRegP++;
				for(int m=1;m<WIDTH-1;m++){
					pushAttackReg[pushAttackRegP][m]=-1;
				}
			}
		}
//레벨업//
		if(lineCnt>5&&level<10){
			level++;
			lineCnt=0;
			if(speed[level]<speed[level-1]) gameMsg((WIDTH/2)-1,5,1);
			else  gameMsg((WIDTH/2)-1,5,2);
			
			gotoxy(status_x, status_y+6);
			if(level==10) printf("Level:MAX");
			else printf("Level:%2d",level);
			gotoxy(status_x, status_y+7);
			printf("Speed:%2d",speed[level]);
		}
	}
//게임오버체크//
	for(int i=1;i<WIDTH-2;i++) if(gameOrg[3][i]>0) gameOver_on=true;
}
void Tetris::dropBlock(void){
	if(fCnt>0) fCnt--;
	bool can_down=checkCrush(block.x,block.y+1,block.rotation);

	if(crush_on==true && can_down==true){ // crush_on이 켜져있으나 이동하여 다시 drop이 가능하게 된 경우
		move_block(DOWN);
		if(upRotate_on==false) fCnt=speed[level];
		crush_on=false;
	}
	if(crush_on==true && can_down==false && fCnt==0){ // crush_on이 켜져있고 drop이 불가능하며 fCnt가 0인 경우
		if(gameDelayCnt==-1){
			drawGame();
			gameDelay(5);
		}
		else if(gameDelayCnt==0){
			for(int i=0;i<HEIGHT;i++){ //현재 조작중인 블럭을 굳힘 
				for(int j=0;j<WIDTH;j++){
					if(gameOrg[i][j]==ACTIVE_BLOCK) gameOrg[i][j]=INACTIVE_BLOCK;
				}
			}
			gameDelayCnt=-1;
			upRotate_on=false;
			crush_on=false; //flag를 끔 
			checkLine(); //라인체크를 함 
			getAttack(); //공격받을것이 있는지 체크
			if(gameOver_on==false) newBlock(); //게임오버가 아닌 경우 새로운 블록을 만듬
			fCnt=speed[level]; //fCnt를 다시 설정
		}
		return; //함수 종료 
	}
	if(crush_on==false && can_down==true && fCnt==0){ //밑이 비어있으면 밑으로 한칸 이동 
		move_block(DOWN);
		if(upRotate_on==false) fCnt=speed[level];
	}
	if(crush_on==false && can_down==false){ //밑으로 이동이 안되면 crush flag를 켬
		crush_on=true;
		if(upRotate_on==false) fCnt=speed[0];
	}
}
bool Tetris::checkCrush(int x, int y, int rotation){ //지정된 좌표와 회전값으로 충돌이 있는지 검사 
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){ //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
			if(block.shape[block.type][rotation][i][j]==1&&gameOrg[y+i][x+j]>0) return false;
		}
	}	
	return true; //하나도 안겹치면 true리턴 
};
void Tetris::newBlock(void){
	int i, j;	
if(owner==COMPUTER) comCheck_on=true;
	
	block.x=(WIDTH/2)-1; //블록 생성 위치x좌표(게임판의 가운데) 
	block.y=0;  //블록 생성위치 y좌표(제일 위) 
	block.type=block.type_next; //다음블럭값을 가져옴 
	block.type_next=rand()%7; //다음 블럭을 만듦 
	block.rotation=0;  //회전은 0번으로 설정 
//좌표에 active block생성//
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block.shape[block.type][block.rotation][i][j]==1) gameOrg[block.y+i][block.x+j]=ACTIVE_BLOCK;
		}
	}
//게임상태표시에 다음에 나올블럭을 표시//	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block.type_next+2);
	for(i=1;i<3;i++){ 
		for(j=0;j<4;j++){
			gotoxy(status_x+j,status_y+i+2);
			if(block.shape[block.type_next][0][i][j]==1) printf("■");
			else printf("  ");
		}
	}
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
}
void Tetris::drawGame(void){ //게임판 그리는 함수 
	int i, j;	
	
	for(j=1;j<WIDTH-1;j++){ //천장은 계속 새로운블럭이 지나가서 지워지면 새로 그려줌 
		if(gameOrg[3][j]==EMPTY) gameOrg[3][j]=CEILLING;
	}
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			if(gameCpy[i][j]!=gameOrg[i][j]){ //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌. 이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림 
				gotoxy(game_x+j,game_y+i); 
				if(gameOrg[i][j]==EMPTY) printf("  ");
				else if(gameOrg[i][j]==CEILLING){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
					printf(". ");
				}else if(gameOrg[i][j]==WALL){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
					printf("▩"); 
				}else if(gameOrg[i][j]<0){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block.getColor(gameOrg[i][j]));
					printf("▣");
				}else if(gameOrg[i][j]>0){
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), block.getColor(gameOrg[i][j]));
					printf("■");
				}	
			}
		}
	}
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
//게임판을 그린 후 gameCpy에 복사//
	for(i=0;i<HEIGHT;i++){ 
		for(j=0;j<WIDTH;j++){
			gameCpy[i][j]=gameOrg[i][j];
		}
	}
}
void Tetris::gameOver(void){
	gameOverCnt++;
	if(gameOverCnt==0) gameOverP=0;
	if(gameOverP<HEIGHT-1&&gameOverCnt%5==0){ //게임오버 애니메이션효과
		for(int j=1;j<WIDTH-1;j++){
			if(gameOrg[gameOverP][j]>10){
				gameOrg[gameOverP][j]=17;	
			}
		}
		gameOverP++;
	}
}
void Tetris::getAttack(void){
	if(getAttackRegP<HEIGHT-1){ // 공격받을것이 있는지 확인
		int line=(HEIGHT-1)-(getAttackRegP);
		if(getAttackRegP<HEIGHT-1){ // 공격이 들어올만큼 게임판에 빈줄생성
			for(int i=4;i<HEIGHT-1;i++){
				for(int j=1;j<WIDTH-1;j++){
					if(i-line>0) gameOrg[i-line][j]=gameOrg[i][j];
					gameOrg[i][j]=EMPTY;
				}
			}
		}
		for(int i=getAttackRegP+1;i<HEIGHT;i++){ // 공격을 받고 reg를 지움
			for(int j=1;j<WIDTH-1;j++){
				gameOrg[i-1][j]=getAttackReg[i][j];
				getAttackReg[i][j]=-1;
			}
		}
		getAttackRegP+=line;
		for(int i=1;i<10;i++){ // 화면에 공격대기 아이콘을 지움
			gotoxy(attackQueue_x, game_y+i);printf("  ");
		}
	}
}
void Tetris::gameMsg(int x, int y, int type, int val){ //게임판에 메세지 생성
	gameMsgCnt=10; //카운트 set
	switch(type){
	case 0:
		gotoxy(game_x+x,game_y+y);printf("%d COMBO!",val);
		break;
	case 1:
		gotoxy(game_x+x,game_y+y);printf("SPEED UP!!");
		break;
	case 2:
		gotoxy(game_x+x,game_y+y);printf("SPEED DOWN!!");
		break;
	}
}
void Tetris::gameMsg(void){ // 카운트가 0이 아니면 카운트를 낮추고, 0이되면 지움
	if(gameMsgCnt>0) gameMsgCnt--;
	else if(gameMsgCnt==0) {
		resetGameCpy();
		gameMsgCnt=-1;
	}
}
void Tetris::gameDelay(int cnt){ //게임 delay생성
	gameDelay_on=true;
	gameDelayCnt=cnt;
}
void Tetris::gameDelay(void){ //카운트가 0이 아니면 카운트를 낮추고, 0이되면 delay를 끔
	if(gameDelayCnt>0) gameDelayCnt--;
	else if(gameDelayCnt==0) gameDelay_on=false;
}

class BattleTetrisManager{ //두개의 게임간에 공격및 승리, 게임종료를 시키는 class
public:
	BattleTetrisManager(void); //생성자
	Tetris* p1; // tetris 2개 저장할수 있는 포인터
	Tetris* p2;
	int gameMode;
	
	void titleMenu(void);
		void keyInstructions(int menuP);

	void resetManager(void); //메니져 리셋
	
	void gamePlay(Tetris &A); // 개별 게임을 진행
	void getKey(void); //키입력받음
	void pushAttack(Tetris &A, Tetris &B); //A게임에서 B게임으로 공격을 push
	void checkWinner(Tetris A, Tetris B); //승리자가 있는지 확인
		bool winner_on; //승리자가 나와 있는 상태인지 저장 변수
};

BattleTetrisManager::BattleTetrisManager(void){ //생성자 게임포인터를 초기화
	p1=NULL;
	p2=NULL;
}

#define PvC 0
#define PvP	1
void BattleTetrisManager::resetManager(void){ //게임을 초기화
	system("cls");
	delete p1; //게임종료후 재시작하는 경우를 위해 이전 게임을 지움
	delete p2; //

	winner_on=false;

	GetAsyncKeyState(VK_LEFT); //키보드값 지움
	GetAsyncKeyState(VK_RIGHT);
	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
	GetAsyncKeyState(VK_SPACE);
	GetAsyncKeyState('L');
	GetAsyncKeyState('F');
	GetAsyncKeyState('H');
	GetAsyncKeyState('G');
	GetAsyncKeyState('T');
	GetAsyncKeyState('Q');

	switch(gameMode){
	case PvC:
		p1=new Tetris(2,1,14,2, SINGLE);  
		p2=new Tetris(27,1,22,2, COMPUTER);
		break;
	case PvP:
		p1=new Tetris(2,1,14,2, PLAYER1);  
		p2=new Tetris(27,1,22,2, PLAYER2);
		break;
	}
}
void BattleTetrisManager::gamePlay(Tetris &A){ //게임진행		

	if(A.gameMsgCnt>=0)	A.gameMsg();

	if(A.gameDelay_on==true) A.gameDelay();
	else{  
		if(A.gameOver_on==false) A.getKey();
		else A.gameOver();
		A.drawGame();
	}
}
void BattleTetrisManager::getKey(void){ 
	if(GetAsyncKeyState(VK_ESCAPE)){
		delete p1;
		delete p2;
		gotoxy(0,24);
		printf("Thanks for playing :)");
		exit(0);
	}
}
void BattleTetrisManager::pushAttack(Tetris &A, Tetris &B){
	if(A.pushAttackRegP<A.HEIGHT-1){//공격이 있는 경우 A의 push reg에서 B의 get reg로 이동
		int line=(A.HEIGHT-1)-(A.pushAttackRegP);
		for(int i=B.getAttackRegP+1;i<B.HEIGHT;i++){
			for(int j=0;j<B.WIDTH-1;j++){
				if(i-line>0) B.getAttackReg[i-line][j]=B.getAttackReg[i][j];
			}
		}
		for(int i=A.pushAttackRegP+1;i<A.HEIGHT;i++){
			for(int j=0;j<A.WIDTH-1;j++){
				B.getAttackReg[i][j]=A.pushAttackReg[i][j];
				A.pushAttackReg[i][j]=-1;
			}
		}
		B.getAttackRegP-=line;
		A.pushAttackRegP+=line;
//B의 화면에 공격 아이콘 표시//			
		int queue=B.HEIGHT-1-B.getAttackRegP;
		int queueP=0;
		while(queue>=5){ //5줄인경우 별표 한개
			gotoxy(B.attackQueue_x, B.game_y+1+queueP);
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000C);
			printf("★");
			queue-=5;
			queueP++;
		}
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
		while(queue>=1){ //한줄은 원 한개
			gotoxy(B.attackQueue_x, B.game_y+1+queueP);
			printf("○");
			queue--;
			queueP++;
		}
		while(queueP<10){ //최대 10칸까지 표시 나머지칸들은 빈칸으로 표시
			gotoxy(B.attackQueue_x, B.game_y+1+queueP);
			printf("  ");
			queueP++;
		}
	}
}
void BattleTetrisManager::checkWinner(Tetris A, Tetris B){

	if(winner_on==true){ //위너가 있는 경우 엔터키를 눌러서 게임을 재실행
		if(GetAsyncKeyState(VK_RETURN)) resetManager();
		return;
	}
//누가 이겼는지 확인//
	int whoWin;
	if(winner_on==false && A.gameOver_on==true){
		winner_on=true;
		whoWin=B.owner;
	} else if (winner_on==false && B.gameOver_on==true){
		winner_on=true;
		whoWin=A.owner;
	} else return;
//메세지 표시//		
	gotoxy(15, 10);
	switch(whoWin){
	case SINGLE:
		printf(" <<   YOU WIN!   >>");
		break;
	case PLAYER1:
		printf(" << PLAYER 1 WIN >>");
		break;
	case PLAYER2:
		printf(" << PLAYER 2 WIN >>");
		break;
	case COMPUTER:
		printf(" << COMPUTER WIN >>");
		break;
	}
	gotoxy(14, 12);
		printf("Press <ENTER> to restart");
}
void BattleTetrisManager::keyInstructions(int menuP){
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
	switch(menuP){
	case PvP:
		gotoxy(21,15); printf("┌──<  Key Instructions  >──┐");		
		gotoxy(21,16); printf("│ PLAYER 1            PLAYER 2 │");
		gotoxy(21,17); printf("│    T       ROTATE      ↑    │"); 
		gotoxy(21,18); printf("│    H        RIGHT      →    │"); 
		gotoxy(21,19); printf("│    F        LEFT       ←    │"); 
		gotoxy(21,20); printf("│    G      SOFT DROP    ↓    │"); 
		gotoxy(21,21); printf("│    Q      HARD DROP     L    │"); 
		gotoxy(21,22); printf("└───────────────┘"); 
		break;
	case PvC:
		gotoxy(21,15); printf("┌──<  Key Instructions  >──┐");		
		gotoxy(21,16); printf("│                   PLAYER     │");
		gotoxy(21,17); printf("│     ROTATE          ↑       │"); 
		gotoxy(21,18); printf("│      RIGHT          →       │"); 
		gotoxy(21,19); printf("│      LEFT           ←       │"); 
		gotoxy(21,20); printf("│    SOFT DROP        ↓       │"); 
		gotoxy(21,21); printf("│    HARD DROP      SPACE      │"); 
		gotoxy(21,22); printf("└───────────────┘"); 

	}
}
void BattleTetrisManager::titleMenu(void){ // 게임타이틀
	int i,j;

	int text_battle_x=3;
	int text_battle_y=2;
	
	int text_tetris_x=16;
	int text_tetris_y=9;
	
	int text_menu_x=4;
	int text_menu_y=17;

	int menuP=PvC;
	int totalMenu=2;
	int menuCnt=0;

	int text_battle_order[9]={0,1,2,3,4,2,1,4,2};
	int text_battle [5][6][25]={
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,

		1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,
		0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,
		0,1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,
		0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,
		0,1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,
		1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,
		1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,0,

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,0,0,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,
		0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,
		0,0,1,1,0,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,
		0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,
		0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,1,0,1,1,1
	};

	int text_tetris [5][21]={
		1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,1,
		0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,
		0,1,0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,0,1,1,1,
		0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,
		0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1
	};
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0003);
	for(int k=1;k<9;k++){
		for(i=0;i<6;i++){
			for(j=0;j<25;j++){
				if(text_battle[text_battle_order[k]][i][j]!=text_battle[text_battle_order[k-1]][i][j]){
					gotoxy(text_battle_x+j,text_battle_y+i); 
					if(text_battle[text_battle_order[k]][i][j]==1) printf("■");
					else if(text_battle[text_battle_order[k]][i][j]==0) printf("  ");
				}
			}
		}
		Sleep(100);
	}
	Sleep(200);

	
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000F);
	gotoxy(text_menu_x,text_menu_y); printf("    1. PLAYER VS COMPUTER");
	gotoxy(text_menu_x,text_menu_y+2); printf("    2. PLAYER 1 VS PLAYER 2");
	
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
	gotoxy(33,7); printf("ver. 2.0");

	
	keyInstructions(menuP);
	gotoxy(21,23); printf("  http://blog.naver.com/azure0777");

	for(int cnt=0;;cnt++){
		if(menuCnt>0) menuCnt--;
		Sleep(10);

		if((cnt+0)%60==0){
			switch(menuP){
			case PvC:
				gotoxy(text_menu_x,text_menu_y); 
				break;
			case PvP:
				gotoxy(text_menu_x,text_menu_y+2); 
				break;
			}
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000F);
			printf(" →");
		}
		if((cnt+30)%60==0){
			switch(menuP){
			case PvC:
				gotoxy(text_menu_x,text_menu_y); 
				break;
			case PvP:
				gotoxy(text_menu_x,text_menu_y+2); 
				break;
			}
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x000F);
			printf("→ ");
		}
		if(cnt%75==0){	
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), cnt%7+2);
			for(i=0;i<5;i++){
				for(j=0;j<21;j++){
					gotoxy(text_tetris_x+j,text_tetris_y+i);
					if(text_tetris[i][j]==1) printf("▣");
				}
			}
		}
		if(GetAsyncKeyState(VK_UP)&&menuCnt==0){
			menuCnt=20;
			gotoxy(text_menu_x,text_menu_y); printf("   ");
			gotoxy(text_menu_x,text_menu_y+2); printf("   ");
			menuP=(menuP+1)%totalMenu;
			keyInstructions(menuP);
		}
		if(GetAsyncKeyState(VK_DOWN)&&menuCnt==0){
			menuCnt=20;
			gotoxy(text_menu_x,text_menu_y); printf("   ");
			gotoxy(text_menu_x,text_menu_y+2); printf("   ");
			menuP=(menuP+totalMenu-1)%totalMenu;
			keyInstructions(menuP);
		}
		if(GetAsyncKeyState(VK_RETURN)){
			gameMode=menuP;
			break;
		}
		if(GetAsyncKeyState('1')){
			gameMode=PvC;
			break;
		}
		if(GetAsyncKeyState('2')){
			gameMode=PvP;
			break;
		}
	}
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0007);
}

int main(){
	srand((unsigned)time(NULL)); //난수표생성 
	setcursortype(NOCURSOR); //커서 없앰 
	
	BattleTetrisManager GM; //게임메니져생성
	GM.titleMenu(); //게임타이틀
	GM.resetManager(); // 게임메니져 리셋
	
	Tetris &player1=*GM.p1;
	Tetris &player2=*GM.p2;
	
	while(1){
		Sleep(20);
		GM.getKey();
		GM.gamePlay(player1);	
		GM.gamePlay(player2);
		GM.pushAttack(player1, player2);
		GM.pushAttack(player2, player1);
		GM.checkWinner(player1, player2);
	}
}//끝! 
