// ConsoleApplication1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define LEFT 75  //Ű���尪�� 
#define RIGHT 77 //��� �̵� 
#define ROTATE 72 //ȸ�� 
#define UP_ROTATE 100 //ȸ�� 
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

void gotoxy(int x, int y) { //gotoxy�Լ� 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) { //Ŀ�� �Ⱥ��̰� �ϴ� �Լ� 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

class Blocks {
public:
	Blocks(void) { //������
		type_next = rand() % 7;
	}
	static const int shape[7][4][4][4]; //��ϸ�� 
	int x; //x��ǥ
	int y; //y��ǥ
	int type; //��� ����
	int rotation; //��� ȸ����
	int type_next; //���� ��ϰ�
	int getColor(int num); //��ϻ��� ���ϴ� �Լ�
};
const int Blocks::shape[7][4][4][4] = {
	{ { 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0 } },
	{ { 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0 },{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 },{ 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0 },{ 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 } },
	{ { 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 },{ 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0 },{ 0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0 } },
	{ { 0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0 },{ 0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0 },{ 0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0 },{ 0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0 } },
	{ { 0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0 },{ 0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 } },
	{ { 0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0 },{ 0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0 },{ 0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0 } },
	{ { 0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 },{ 0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0 },{ 0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0 },{ 0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0 } }
};
int Blocks::getColor(int num) {
	if (num<0) num *= (-1);
	return num - 9;
}

class Tetris {
public:
	Tetris(int game_x, int game_y, int status_x, int status_y, int owner); //������ �������� �ʱ�ȭ

	int fCnt; // ������ī����. 0�̵Ǹ� ����� ��ĭ drop�ǰ� speed[level]�� reset�� ��. �� �� ���� �������� ������ ������.
	int owner; // ������ �÷��̾�. Player(�̱�), Player 1, Player 2, Computer�� �ϳ�.(�̱۸�� �̱���)
	int score; // ����(�̱���)
	int lineCnt; // ���� ���ݴ��� ����ϴ� ����

	static const int speed[11]; //���Ӽӵ� ����迭
	int level; // ����

	int game_x;   // ��ǥ����
	int game_y;   //
	int status_x; //
	int status_y; //

	static const int WIDTH = 11;  // ���� ���� ũ��
	static const int HEIGHT = 23; // ���� ���� ũ��

	int gameOrg[HEIGHT][WIDTH]; // ������            /*�����ǿ��� ������ ����ǰ�, cpy���� ���� ���� frame�� ��ϵǾ� ����.*/
	int gameCpy[HEIGHT][WIDTH]; // ������ �񱳿� cpy /*cpy�� ���Ͽ� ��ȭ�� �ִ� �κи� ������ ���� �׸�                  */
	void resetGameCpy(void) { // gameCpy�� �����ϴ� �Լ�
		for (int i = 0; i<HEIGHT; i++) for (int j = 0; j<WIDTH; j++) gameCpy[i][j] = 999;
	}
	void drawGame(void); //gameOrg�� gameCpy�� ���Ͽ� �������� �׸�

	void newBlock(void); //���ο� ����� �ϳ� ����
	Blocks block;    //��� ����
	void move_block(int dir); //����� �̵���Ŵ
	void dropBlock(void); //�����ð����� �׻� ����� ��ĭ ������ �̵�
	bool checkCrush(int x, int y, int rotation); //��� �̵����� �̵��� �������� �Ǻ�
	bool crush_on; // �浹�����̸� true

	void initialGame(void); //�������� �ʱ�ȭ

	void gameOver(void); // ���ӿ����� ����
	bool gameOver_on; // ���ӿ����� true
	int gameOverCnt; // ���ӿ��� �ִϸ��̼� ī��Ʈ
	int gameOverP; // ȸ������ �ٲ� �ټ��� ���

	void gameDelay(int cnt); //���� delay����
	bool gameDelay_on; // �����Ǹ� true
	int gameDelayCnt; // delay ī��Ʈ
	void gameDelay(void); //ī��Ʈ�� 0�� �Ǹ� delay�� ��

	void gameMsg(int x, int y, int type, int val = 0); //�����ǿ� �޼����� ����
	int gameMsgCnt; //�޼��� ī��Ʈ
	void gameMsg(void); //ī��Ʈ�� 0�̵Ǹ� gameCpy�� �����Ͽ� �޼����� ����

	void getKey(void); //keyCnt�� 0�϶� Ű�Է¹���
	int keyCnt; // Ű�Է� �޴� �ӵ� ��������
	bool upRotate_on;

	void checkLine(void); // ���� ����á���� Ȯ���ϰ� ���� ����
	int pushAttackReg[HEIGHT][WIDTH]; //�޺��ÿ� ���� ���� ����(�ؿ������� ä����) /* pushAttackReg�� ���� ���� ��� BattleTetrisManager�� */
	int pushAttackRegP; //pushAttackReg�� ���̸� �����ϴ� ����                     /* ������ getAttackReg�� �̵�                         */

	void getAttack(void); // getAttackReg�� Ȯ���Ͽ� ���� ���� ������ �߰�
	int getAttackReg[HEIGHT][WIDTH]; //�������� ���� �޴� ���� �ӽ� �����ϴ� �迭(�ؿ������� ä����)
	int getAttackRegP; //getAttackReg�� ���̸� �����ϴ� ����
	int attackQueue_x; //���� ���ݹ޴����� ȭ�鿡 ��Ÿ���� x��ǥ

	int comOutput; //��ǻ�Ͱ� getKey�� �����ϴ� �Է°�
	void comCheck(void); //����� ���� ��ġ �� pathã�� �Լ�
	int comX[10]; //��� path X��ǥ������(���� [0]�� [1]�� ���)
	int comY[10]; //��� path Y��ǥ������(���� [0]�� [1]�� ���)
	int comR[10]; //��� path ȸ����������(���� �̻��)
	int comXYRP; //path����(pointer) ����
	int comGameValue[HEIGHT][WIDTH]; //���� �������� ��ǥvalue�� ����
	int comGameUnder[HEIGHT][WIDTH]; //���� �����ǿ��� ��ϾƷ� ������� �ִ� ���� ����
	bool comCheck_on; //��� ���� ��ġ �� path ������ �ʿ��� ��� true
	int comCheckAroundValue(int x, int y, int rotation); //����� �ֺ����� ���� ���� �� ���
};
const int Tetris::speed[11] = { 20,20,15,10,20,10,5,15,10,2,1 }; //�ӵ� ����

int Tetris::comCheckAroundValue(int x, int y, int rotation) {
	int sum = 0;
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (block.shape[block.type][rotation][i][j] == 1) {
				for (int k = 0; k<4; k++) {
					switch (k) {
					case 0:
						if (((i == 0) && (comGameValue[y + i - 1][x + j]>0)) ||
							((i != 0) && (block.shape[block.type][rotation][i - 1][j] != 1) && (comGameValue[y + i - 1][x + j]>0))) sum += comGameValue[y + i - 1][x + j];
						break;
					case 1:
						if ((i == 4) ||
							(block.shape[block.type][rotation][i + 1][j] != 1)) sum += comGameValue[y + i + 1][x + j];
						break;
					case 2:
						if (((j == 0) && (comGameValue[y + i][x + j - 1]>0)) ||
							((j != 0) && (block.shape[block.type][rotation][i][j - 1] != 1) && (comGameValue[y + i][x + j - 1]>0))) sum += comGameValue[y + i][x + j - 1];
						break;
					case 3:
						if (((j == 4) && comGameValue[y + i][x + j + 1]>0) ||
							((j != 4) && (block.shape[block.type][rotation][i][j + 1] != 1) && (comGameValue[y + i][x + j + 1]>0))) sum += comGameValue[y + i][x + j + 1];
						break;
					}
				}
			}
		}
	}
	return sum;
}
void Tetris::comCheck(void) {
	int val = 0;

	if (comCheck_on == true) {
		for (int i = 0; i<10; i++) { //�ʱ�ȭ
			comX[i] = 0;
			comY[i] = 0;
			comR[i] = 0;
		}
		comXYRP = 0;

		for (int i = 0; i<HEIGHT; i++) { //valueǥ(+��) ���ϱ�
			for (int j = 0; j<WIDTH; j++) {
				if (gameOrg[i][j]>0) comGameValue[i][j] = i;
				else comGameValue[i][j] = 0;
			}
		}
		for (int i = 0; i<HEIGHT - 1; i++) { //valueǥ(-��) ���ϱ�
			for (int j = 0; j<WIDTH; j++) {
				if (comGameValue[i][j] == 0 && (comGameValue[i][j - 1]>0 || comGameValue[i][j + 1]>0)) comGameValue[i][j] = (-i);
			}
		}
		for (int i = 0; i<HEIGHT; i++) { //underǥ �ʱ�ȭ
			for (int j = 0; j<WIDTH; j++) {
				comGameUnder[i][j] = 0;
			}
		}
		for (int i = 0; i<HEIGHT; i++) { //under mark�ϱ�
			for (int j = 1; j<WIDTH - 1; j++) {
				if (gameOrg[i][j]>0 && gameOrg[i - 1][j] == 0) {
					for (int k = i - 1; k>0; k--) {
						if (gameOrg[k][j]>0) {
							for (int m = i - 1; m>k; m--) comGameUnder[m][j] = 1;
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i<21; i++) { // ���� ��ġ �� pathã��
			for (int j = 0; j<WIDTH; j++) {
				for (int k = 0; k<4; k++) {

					if (checkCrush(j, i + 1, k) == false && checkCrush(j, i, k) == true && comCheckAroundValue(j, i, k)>val) {
						bool onUnder = false;//onUnder�� hard drop�� �������� �Ǻ�: false�� ���� , true�� �Ұ���(���� crush�� ����)						
						for (int m = 0; m<4; m++) {
							for (int n = 0; n<4; n++) {
								if (block.shape[block.type][k][m][n] == 1 && comGameUnder[i + m][j + n] == 1) {
									onUnder = true;
								}
							}
						}
						if (onUnder == false) { // hard drop�� �����ϸ� ����path		
							comXYRP = 0;
							val = comCheckAroundValue(j, i, k);
							comX[0] = j;
							comY[0] = i;
							comR[0] = k;
						}
						if (onUnder == true) { // hard drop�� �Ұ����ϸ� ��ȸ�մϴ�.
							comXYRP = 0;

							if (checkCrush(j + 1, i, k) == false && checkCrush(j - 1, i, k) == false && checkCrush(j, i - 1, k) == false) break;

							int tempX1 = j;
							int tempY1 = i;
							int tempX2 = j;
							int tempY2 = i;
							int tempXYRP = 0;

							bool underStuck = true; //�� ������ ���� �ִ��� �ƴ����� �Ǻ�. ������ ���� �ִٰ� �����ϰ� �ⱸ�� ������ false
							for (int s = 1; s>-2; s -= 2) { //���� �ѹ� ��ȸ�ؼ� ���� �ִ����� �Ǻ��Ҽ� ����..
								for (int x = 0; x<WIDTH; x++) {
									if (underStuck == false) break;
									for (int y = 0; y<HEIGHT; y++) {
										if (tempY1 - y == 0) {
											underStuck = false;
											tempXYRP++;
											comX[tempXYRP] = j + x*s;
											comY[tempXYRP] = tempY1;
											comR[tempXYRP] = k;
											break;
										}
										else if (checkCrush(j + x*s, tempY1 - y, k) == true) {
											tempX2 = j + x*s;
											tempY2 = tempY1 - y;
										}
										else if (checkCrush(tempX1 + x*s, tempY1 - y, k) == false) break;

									}
									if (tempX1 == tempX2 && tempY1 == tempY2 && x != 0) break;
									else {
										tempX1 = tempX2;
										tempY1 = tempY2;
									}
								}
							}

							if (underStuck == false) { //1���� ��ȸ�� ������ ��� ���� path������Ʈ
								val = comCheckAroundValue(j, i, k);
								comX[0] = j;
								comY[0] = i;
								comR[0] = k;
								comXYRP = tempXYRP;
							}
						}
					}
				}
			}
		}
		comCheck_on = false;
	}
	//���� path�� ã�ư��� �ϴ� �κ�
	if (block.rotation != comR[comXYRP]) comOutput = ROTATE;
	else if (comX[comXYRP]>block.x) comOutput = RIGHT;
	else if (comX[comXYRP]<block.x) comOutput = LEFT;
	else if (comX[comXYRP] == block.x) if (comXYRP == 0) comOutput = SPACE; else  comOutput = DOWN;

	if (comX[comXYRP] == block.x && comY[comXYRP] == block.y && comR[comXYRP] == block.rotation && comXYRP>0) comXYRP--;
}
Tetris::Tetris(int game_x, int game_y, int status_x, int status_y, int owner) { // ���� �ʱ�ȭ
	level = 1;
	score = 0;
	lineCnt = 0;
	keyCnt = 0;
	fCnt = speed[level];

	for (int i = 0; i<HEIGHT; i++) {
		for (int j = 0; j<WIDTH; j++) {
			gameOrg[i][j] = 0;
			gameCpy[i][j] = NULL;
			pushAttackReg[i][j] = -1;
			getAttackReg[i][j] = -1;
		}
	}
	pushAttackRegP = HEIGHT - 1;
	getAttackRegP = HEIGHT - 1;

	this->game_x = game_x;
	this->game_y = game_y;
	this->status_x = status_x;
	this->status_y = status_y;
	this->owner = owner;

	upRotate_on = false;
	crush_on = false;
	gameDelay_on = false;
	gameDelayCnt = -1;
	gameOver_on = false;
	gameOverCnt = -1;
	gameMsgCnt = -1;
	comCheck_on = true;

	initialGame(); //�������� �׸�
	newBlock(); //���ο� ��� ����
}
void Tetris::initialGame(void) {
	int i, j;
	//�������� �׸�//
	for (j = 1; j<WIDTH; j++) {
		gameOrg[3][j] = CEILLING;
	}
	for (i = 1; i<HEIGHT - 1; i++) {
		gameOrg[i][0] = WALL;
		gameOrg[i][WIDTH - 1] = WALL;
	}
	for (j = 0; j<WIDTH; j++) {
		gameOrg[HEIGHT - 1][j] = WALL;
	}
	//status ǥ��//
	gotoxy(status_x, status_y);
	switch (owner) {
	case 0:
		printf("< PLAYER >");
		attackQueue_x = game_x - 1;
		break;
	case 1:
		printf("<PLAYER1>");
		attackQueue_x = game_x - 1;
		break;
	case 2:
		printf("<PLAYER2>");
		attackQueue_x = game_x + WIDTH;
		break;
	case 3:
		printf("<COMPUTER>");
		attackQueue_x = game_x + WIDTH;
		break;
	}
	gotoxy(status_x, status_y + 1);
	printf("Next:");
	gotoxy(status_x, status_y + 6);
	if (level == 10) printf("Level:MAX");
	else printf("Level:%2d", level);
	gotoxy(status_x, status_y + 7);
	printf("Speed:%2d", speed[level]);
}
void Tetris::getKey() { //Ű�Է¹���
	dropBlock();
	if (keyCnt>0) {
		keyCnt--;
		return;
	}
	if (owner == COMPUTER)comCheck();

	keyCnt = 3; //3 ���������Ӹ��� Ű�Է� �ѹ��� ����. �� �����Ӹ��� Ű�Է��� ������ �ʹ� ���� ������

	if (((owner == SINGLE || owner == PLAYER2) && GetAsyncKeyState(VK_LEFT)) ||
		(owner == PLAYER1&&GetAsyncKeyState('F')) ||
		(owner == COMPUTER&&comOutput == LEFT))
		if (checkCrush(block.x - 1, block.y, block.rotation) == true) move_block(LEFT);
	if (((owner == SINGLE || owner == PLAYER2) && GetAsyncKeyState(VK_RIGHT)) ||
		(owner == PLAYER1&&GetAsyncKeyState('H')) ||
		(owner == COMPUTER&&comOutput == RIGHT))
		if (checkCrush(block.x + 1, block.y, block.rotation) == true) move_block(RIGHT);
	if (((owner == SINGLE || owner == PLAYER2) && GetAsyncKeyState(VK_DOWN)) || (owner == PLAYER1&&GetAsyncKeyState('G')) ||
		(owner == COMPUTER&&comOutput == DOWN))
		if (checkCrush(block.x, block.y + 1, block.rotation) == true) move_block(DOWN);
	if (((owner == SINGLE || owner == PLAYER2) && GetAsyncKeyState(VK_UP)) || (owner == PLAYER1&&GetAsyncKeyState('T')) ||
		(owner == COMPUTER&&comOutput == ROTATE)) {
		if (checkCrush(block.x, block.y, (block.rotation + 1) % 4) == true) move_block(ROTATE);
		else if (crush_on == true && checkCrush(block.x, block.y - 1, (block.rotation + 1) % 4) == true) move_block(UP_ROTATE); //��ĭ���� �÷��� ȸ�������Ҷ�
	}
	if ((owner == SINGLE && (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState('L'))) ||
		(owner == PLAYER2&&GetAsyncKeyState('L')) ||
		(owner == PLAYER1&&GetAsyncKeyState('Q')) ||
		(owner == COMPUTER&&comOutput == SPACE)) {
		while (crush_on == false) {
			dropBlock();
			score += level;
		}
		fCnt = 0;
	}

	///* ZŰ�� ������ ���밡 ������ cheat�ڵ�
	if (GetAsyncKeyState('Z')) {
		block.type_next = 1;
	}
	//*/
}
void Tetris::move_block(int dir) {
	int i, j;
	//������ǥ�� ����� ����//	
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i][block.x + j] = EMPTY;
		}
	}
	//�̵����⿡ ���� ���ο� ����� �׸�//
	switch (dir) {
	case LEFT:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i][block.x + j - 1] = ACTIVE_BLOCK;
			}
		}
		block.x--;
		break;
	case RIGHT:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i][block.x + j + 1] = ACTIVE_BLOCK;
			}
		}
		block.x++;
		break;
	case DOWN:
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i + 1][block.x + j] = ACTIVE_BLOCK;
			}
		}
		block.y++;
		break;
	case ROTATE:
		block.rotation = (block.rotation + 1) % 4;
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i][block.x + j] = ACTIVE_BLOCK;
			}
		}
		break;
	case UP_ROTATE: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� �̸� ���۽�Ű�� Ư������ 
		block.rotation = (block.rotation + 1) % 4;
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i - 1][block.x + j] = ACTIVE_BLOCK;
			}
		}
		block.y--;
		upRotate_on = true;
		break;
	}
}
void Tetris::checkLine(void) {
	int i, j;

	int	block_amount; //������ ��ϰ����� �����ϴ� ���� 
	int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

	for (i = HEIGHT - 2; i>3;) { //i=HEIGHT-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
		block_amount = 0;
		for (j = 1; j<WIDTH - 1; j++) {
			if (gameOrg[i][j]>0) block_amount++;
		}
		if (block_amount == WIDTH - 2) {
			score += 100 * level;//������ �̱���
			lineCnt++;
			combo++;

			if (pushAttackRegP>0) { //�ϴ� �ٻ����� ������ attack�� push��
				for (int m = 1; m<WIDTH - 1; m++) {
					if (m>block.x&&m<block.x + 4 && block.shape[block.type][block.rotation][i - block.y][m - block.x] == 1) pushAttackReg[pushAttackRegP][m] = 0;
					else pushAttackReg[pushAttackRegP][m] = 16;
				}
				pushAttackRegP--;
				block.y++;
			}

			for (int k = i; k>1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
				for (int l = 1; l<WIDTH - 1; l++) {
					if (gameOrg[k - 1][l] != CEILLING) gameOrg[k][l] = gameOrg[k - 1][l];
					if (gameOrg[k - 1][l] == CEILLING) gameOrg[k][l] = EMPTY; //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
				}
			}
		}
		else i--;
	}
	//�޺�Ȯ��//
	if (combo) {
		if (combo>1) { //2�޺��̻��� ��� �޼����� ���
			drawGame();
			gameMsg((WIDTH / 2) - 1, block.y - 2, 0, combo);
			score += (combo*level * 100);
		}
		else { //�޺��� 1�϶�(�޺��� �ƴҶ�) attack reg�� ����
			if (pushAttackRegP>0) {
				pushAttackRegP++;
				for (int m = 1; m<WIDTH - 1; m++) {
					pushAttackReg[pushAttackRegP][m] = -1;
				}
			}
		}
		//������//
		if (lineCnt>5 && level<10) {
			level++;
			lineCnt = 0;
			if (speed[level]<speed[level - 1]) gameMsg((WIDTH / 2) - 1, 5, 1);
			else  gameMsg((WIDTH / 2) - 1, 5, 2);

			gotoxy(status_x, status_y + 6);
			if (level == 10) printf("Level:MAX");
			else printf("Level:%2d", level);
			gotoxy(status_x, status_y + 7);
			printf("Speed:%2d", speed[level]);
		}
	}
	//���ӿ���üũ//
	for (int i = 1; i<WIDTH - 2; i++) if (gameOrg[3][i]>0) gameOver_on = true;
}
void Tetris::dropBlock(void) {
	if (fCnt>0) fCnt--;
	bool can_down = checkCrush(block.x, block.y + 1, block.rotation);

	if (crush_on == true && can_down == true) { // crush_on�� ���������� �̵��Ͽ� �ٽ� drop�� �����ϰ� �� ���
		move_block(DOWN);
		if (upRotate_on == false) fCnt = speed[level];
		crush_on = false;
	}
	if (crush_on == true && can_down == false && fCnt == 0) { // crush_on�� �����ְ� drop�� �Ұ����ϸ� fCnt�� 0�� ���
		if (gameDelayCnt == -1) {
			drawGame();
			gameDelay(5);
		}
		else if (gameDelayCnt == 0) {
			for (int i = 0; i<HEIGHT; i++) { //���� �������� ���� ���� 
				for (int j = 0; j<WIDTH; j++) {
					if (gameOrg[i][j] == ACTIVE_BLOCK) gameOrg[i][j] = INACTIVE_BLOCK;
				}
			}
			gameDelayCnt = -1;
			upRotate_on = false;
			crush_on = false; //flag�� �� 
			checkLine(); //����üũ�� �� 
			getAttack(); //���ݹ������� �ִ��� üũ
			if (gameOver_on == false) newBlock(); //���ӿ����� �ƴ� ��� ���ο� ����� ����
			fCnt = speed[level]; //fCnt�� �ٽ� ����
		}
		return; //�Լ� ���� 
	}
	if (crush_on == false && can_down == true && fCnt == 0) { //���� ��������� ������ ��ĭ �̵� 
		move_block(DOWN);
		if (upRotate_on == false) fCnt = speed[level];
	}
	if (crush_on == false && can_down == false) { //������ �̵��� �ȵǸ� crush flag�� ��
		crush_on = true;
		if (upRotate_on == false) fCnt = speed[0];
	}
}
bool Tetris::checkCrush(int x, int y, int rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
	int i, j;

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
			if (block.shape[block.type][rotation][i][j] == 1 && gameOrg[y + i][x + j]>0) return false;
		}
	}
	return true; //�ϳ��� �Ȱ�ġ�� true���� 
};
void Tetris::newBlock(void) {
	int i, j;
	if (owner == COMPUTER) comCheck_on = true;

	block.x = (WIDTH / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
	block.y = 0;  //��� ������ġ y��ǥ(���� ��) 
	block.type = block.type_next; //���������� ������ 
	block.type_next = rand() % 7; //���� ���� ���� 
	block.rotation = 0;  //ȸ���� 0������ ���� 
						 //��ǥ�� active block����//
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			if (block.shape[block.type][block.rotation][i][j] == 1) gameOrg[block.y + i][block.x + j] = ACTIVE_BLOCK;
		}
	}
	//���ӻ���ǥ�ÿ� ������ ���ú��� ǥ��//	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block.type_next + 2);
	for (i = 1; i<3; i++) {
		for (j = 0; j<4; j++) {
			gotoxy(status_x + j, status_y + i + 2);
			if (block.shape[block.type_next][0][i][j] == 1) printf("��");
			else printf("  ");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}
void Tetris::drawGame(void) { //������ �׸��� �Լ� 
	int i, j;

	for (j = 1; j<WIDTH - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
		if (gameOrg[3][j] == EMPTY) gameOrg[3][j] = CEILLING;
	}
	for (i = 0; i<HEIGHT; i++) {
		for (j = 0; j<WIDTH; j++) {
			if (gameCpy[i][j] != gameOrg[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���. �̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ� 
				gotoxy(game_x + j, game_y + i);
				if (gameOrg[i][j] == EMPTY) printf("  ");
				else if (gameOrg[i][j] == CEILLING) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
					printf(". ");
				}
				else if (gameOrg[i][j] == WALL) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
					printf("��");
				}
				else if (gameOrg[i][j]<0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block.getColor(gameOrg[i][j]));
					printf("��");
				}
				else if (gameOrg[i][j]>0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block.getColor(gameOrg[i][j]));
					printf("��");
				}
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
	//�������� �׸� �� gameCpy�� ����//
	for (i = 0; i<HEIGHT; i++) {
		for (j = 0; j<WIDTH; j++) {
			gameCpy[i][j] = gameOrg[i][j];
		}
	}
}
void Tetris::gameOver(void) {
	gameOverCnt++;
	if (gameOverCnt == 0) gameOverP = 0;
	if (gameOverP<HEIGHT - 1 && gameOverCnt % 5 == 0) { //���ӿ��� �ִϸ��̼�ȿ��
		for (int j = 1; j<WIDTH - 1; j++) {
			if (gameOrg[gameOverP][j]>10) {
				gameOrg[gameOverP][j] = 17;
			}
		}
		gameOverP++;
	}
}
void Tetris::getAttack(void) {
	if (getAttackRegP<HEIGHT - 1) { // ���ݹ������� �ִ��� Ȯ��
		int line = (HEIGHT - 1) - (getAttackRegP);
		if (getAttackRegP<HEIGHT - 1) { // ������ ���ø�ŭ �����ǿ� ���ٻ���
			for (int i = 4; i<HEIGHT - 1; i++) {
				for (int j = 1; j<WIDTH - 1; j++) {
					if (i - line>0) gameOrg[i - line][j] = gameOrg[i][j];
					gameOrg[i][j] = EMPTY;
				}
			}
		}
		for (int i = getAttackRegP + 1; i<HEIGHT; i++) { // ������ �ް� reg�� ����
			for (int j = 1; j<WIDTH - 1; j++) {
				gameOrg[i - 1][j] = getAttackReg[i][j];
				getAttackReg[i][j] = -1;
			}
		}
		getAttackRegP += line;
		for (int i = 1; i<10; i++) { // ȭ�鿡 ���ݴ�� �������� ����
			gotoxy(attackQueue_x, game_y + i); printf("  ");
		}
	}
}
void Tetris::gameMsg(int x, int y, int type, int val) { //�����ǿ� �޼��� ����
	gameMsgCnt = 10; //ī��Ʈ set
	switch (type) {
	case 0:
		gotoxy(game_x + x, game_y + y); printf("%d COMBO!", val);
		break;
	case 1:
		gotoxy(game_x + x, game_y + y); printf("SPEED UP!!");
		break;
	case 2:
		gotoxy(game_x + x, game_y + y); printf("SPEED DOWN!!");
		break;
	}
}
void Tetris::gameMsg(void) { // ī��Ʈ�� 0�� �ƴϸ� ī��Ʈ�� ���߰�, 0�̵Ǹ� ����
	if (gameMsgCnt>0) gameMsgCnt--;
	else if (gameMsgCnt == 0) {
		resetGameCpy();
		gameMsgCnt = -1;
	}
}
void Tetris::gameDelay(int cnt) { //���� delay����
	gameDelay_on = true;
	gameDelayCnt = cnt;
}
void Tetris::gameDelay(void) { //ī��Ʈ�� 0�� �ƴϸ� ī��Ʈ�� ���߰�, 0�̵Ǹ� delay�� ��
	if (gameDelayCnt>0) gameDelayCnt--;
	else if (gameDelayCnt == 0) gameDelay_on = false;
}

class BattleTetrisManager { //�ΰ��� ���Ӱ��� ���ݹ� �¸�, �������Ḧ ��Ű�� class
public:
	BattleTetrisManager(void); //������
	Tetris* p1; // tetris 2�� �����Ҽ� �ִ� ������
	Tetris* p2;
	int gameMode;

	void titleMenu(void);
	void keyInstructions(int menuP);

	void resetManager(void); //�޴��� ����

	void gamePlay(Tetris &A); // ���� ������ ����
	void getKey(void); //Ű�Է¹���
	void pushAttack(Tetris &A, Tetris &B); //A���ӿ��� B�������� ������ push
	void checkWinner(Tetris A, Tetris B); //�¸��ڰ� �ִ��� Ȯ��
	bool winner_on; //�¸��ڰ� ���� �ִ� �������� ���� ����
};

BattleTetrisManager::BattleTetrisManager(void) { //������ ���������͸� �ʱ�ȭ
	p1 = NULL;
	p2 = NULL;
}

#define PvC 0
#define PvP	1
void BattleTetrisManager::resetManager(void) { //������ �ʱ�ȭ
	system("cls");
	delete p1; //���������� ������ϴ� ��츦 ���� ���� ������ ����
	delete p2; //

	winner_on = false;

	GetAsyncKeyState(VK_LEFT); //Ű���尪 ����
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

	switch (gameMode) {
	case PvC:
		p1 = new Tetris(2, 1, 14, 2, SINGLE);
		p2 = new Tetris(27, 1, 22, 2, COMPUTER);
		break;
	case PvP:
		p1 = new Tetris(2, 1, 14, 2, PLAYER1);
		p2 = new Tetris(27, 1, 22, 2, PLAYER2);
		break;
	}
}
void BattleTetrisManager::gamePlay(Tetris &A) { //��������		

	if (A.gameMsgCnt >= 0)	A.gameMsg();

	if (A.gameDelay_on == true) A.gameDelay();
	else {
		if (A.gameOver_on == false) A.getKey();
		else A.gameOver();
		A.drawGame();
	}
}
void BattleTetrisManager::getKey(void) {
	if (GetAsyncKeyState(VK_ESCAPE)) {
		delete p1;
		delete p2;
		gotoxy(0, 24);
		printf("Thanks for playing :)");
		exit(0);
	}
}
void BattleTetrisManager::pushAttack(Tetris &A, Tetris &B) {
	if (A.pushAttackRegP<A.HEIGHT - 1) {//������ �ִ� ��� A�� push reg���� B�� get reg�� �̵�
		int line = (A.HEIGHT - 1) - (A.pushAttackRegP);
		for (int i = B.getAttackRegP + 1; i<B.HEIGHT; i++) {
			for (int j = 0; j<B.WIDTH - 1; j++) {
				if (i - line>0) B.getAttackReg[i - line][j] = B.getAttackReg[i][j];
			}
		}
		for (int i = A.pushAttackRegP + 1; i<A.HEIGHT; i++) {
			for (int j = 0; j<A.WIDTH - 1; j++) {
				B.getAttackReg[i][j] = A.pushAttackReg[i][j];
				A.pushAttackReg[i][j] = -1;
			}
		}
		B.getAttackRegP -= line;
		A.pushAttackRegP += line;
		//B�� ȭ�鿡 ���� ������ ǥ��//			
		int queue = B.HEIGHT - 1 - B.getAttackRegP;
		int queueP = 0;
		while (queue >= 5) { //5���ΰ�� ��ǥ �Ѱ�
			gotoxy(B.attackQueue_x, B.game_y + 1 + queueP);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000C);
			printf("��");
			queue -= 5;
			queueP++;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
		while (queue >= 1) { //������ �� �Ѱ�
			gotoxy(B.attackQueue_x, B.game_y + 1 + queueP);
			printf("��");
			queue--;
			queueP++;
		}
		while (queueP<10) { //�ִ� 10ĭ���� ǥ�� ������ĭ���� ��ĭ���� ǥ��
			gotoxy(B.attackQueue_x, B.game_y + 1 + queueP);
			printf("  ");
			queueP++;
		}
	}
}
void BattleTetrisManager::checkWinner(Tetris A, Tetris B) {

	if (winner_on == true) { //���ʰ� �ִ� ��� ����Ű�� ������ ������ �����
		if (GetAsyncKeyState(VK_RETURN)) resetManager();
		return;
	}
	//���� �̰���� Ȯ��//
	int whoWin;
	if (winner_on == false && A.gameOver_on == true) {
		winner_on = true;
		whoWin = B.owner;
	}
	else if (winner_on == false && B.gameOver_on == true) {
		winner_on = true;
		whoWin = A.owner;
	}
	else return;
	//�޼��� ǥ��//		
	gotoxy(15, 10);
	switch (whoWin) {
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
void BattleTetrisManager::keyInstructions(int menuP) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
	switch (menuP) {
	case PvP:
		gotoxy(21, 15); printf("������<  Key Instructions  >������");
		gotoxy(21, 16); printf("�� PLAYER 1            PLAYER 2 ��");
		gotoxy(21, 17); printf("��    T       ROTATE      ��    ��");
		gotoxy(21, 18); printf("��    H        RIGHT      ��    ��");
		gotoxy(21, 19); printf("��    F        LEFT       ��    ��");
		gotoxy(21, 20); printf("��    G      SOFT DROP    ��    ��");
		gotoxy(21, 21); printf("��    Q      HARD DROP     L    ��");
		gotoxy(21, 22); printf("����������������������������������");
		break;
	case PvC:
		gotoxy(21, 15); printf("������<  Key Instructions  >������");
		gotoxy(21, 16); printf("��                   PLAYER     ��");
		gotoxy(21, 17); printf("��     ROTATE          ��       ��");
		gotoxy(21, 18); printf("��      RIGHT          ��       ��");
		gotoxy(21, 19); printf("��      LEFT           ��       ��");
		gotoxy(21, 20); printf("��    SOFT DROP        ��       ��");
		gotoxy(21, 21); printf("��    HARD DROP      SPACE      ��");
		gotoxy(21, 22); printf("����������������������������������");

	}
}
void BattleTetrisManager::titleMenu(void) { // ����Ÿ��Ʋ
	int i, j;

	int text_battle_x = 3;
	int text_battle_y = 2;

	int text_tetris_x = 16;
	int text_tetris_y = 9;

	int text_menu_x = 4;
	int text_menu_y = 17;

	int menuP = PvC;
	int totalMenu = 2;
	int menuCnt = 0;

	int text_battle_order[9] = { 0,1,2,3,4,2,1,4,2 };
	int text_battle[5][6][25] = {
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

	int text_tetris[5][21] = {
		1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,0,1,1,1,
		0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,
		0,1,0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,0,1,1,1,
		0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,
		0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1
	};

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);
	for (int k = 1; k<9; k++) {
		for (i = 0; i<6; i++) {
			for (j = 0; j<25; j++) {
				if (text_battle[text_battle_order[k]][i][j] != text_battle[text_battle_order[k - 1]][i][j]) {
					gotoxy(text_battle_x + j, text_battle_y + i);
					if (text_battle[text_battle_order[k]][i][j] == 1) printf("��");
					else if (text_battle[text_battle_order[k]][i][j] == 0) printf("  ");
				}
			}
		}
		Sleep(100);
	}
	Sleep(200);



	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000F);
	gotoxy(text_menu_x, text_menu_y); printf("    1. PLAYER VS COMPUTER");
	gotoxy(text_menu_x, text_menu_y + 2); printf("    2. PLAYER 1 VS PLAYER 2");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
	gotoxy(33, 7); printf("ver. 2.0");


	keyInstructions(menuP);
	gotoxy(21, 23); printf("  http://blog.naver.com/azure0777");

	for (int cnt = 0;; cnt++) {
		if (menuCnt>0) menuCnt--;
		Sleep(10);

		if ((cnt + 0) % 60 == 0) {
			switch (menuP) {
			case PvC:
				gotoxy(text_menu_x, text_menu_y);
				break;
			case PvP:
				gotoxy(text_menu_x, text_menu_y + 2);
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000F);
			printf(" ��");
		}
		if ((cnt + 30) % 60 == 0) {
			switch (menuP) {
			case PvC:
				gotoxy(text_menu_x, text_menu_y);
				break;
			case PvP:
				gotoxy(text_menu_x, text_menu_y + 2);
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000F);
			printf("�� ");
		}
		if (cnt % 75 == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cnt % 7 + 2);
			for (i = 0; i<5; i++) {
				for (j = 0; j<21; j++) {
					gotoxy(text_tetris_x + j, text_tetris_y + i);
					if (text_tetris[i][j] == 1) printf("��");
				}
			}
		}
		if (GetAsyncKeyState(VK_UP) && menuCnt == 0) {
			menuCnt = 20;
			gotoxy(text_menu_x, text_menu_y); printf("   ");
			gotoxy(text_menu_x, text_menu_y + 2); printf("   ");
			menuP = (menuP + 1) % totalMenu;
			keyInstructions(menuP);
		}
		if (GetAsyncKeyState(VK_DOWN) && menuCnt == 0) {
			menuCnt = 20;
			gotoxy(text_menu_x, text_menu_y); printf("   ");
			gotoxy(text_menu_x, text_menu_y + 2); printf("   ");
			menuP = (menuP + totalMenu - 1) % totalMenu;
			keyInstructions(menuP);
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			gameMode = menuP;
			break;
		}
		if (GetAsyncKeyState('1')) {
			gameMode = PvC;
			break;
		}
		if (GetAsyncKeyState('2')) {
			gameMode = PvP;
			break;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}

int main() {
	srand((unsigned)time(NULL)); //����ǥ���� 
	setcursortype(NOCURSOR); //Ŀ�� ���� 

	BattleTetrisManager GM; //���Ӹ޴�������
	GM.titleMenu(); //����Ÿ��Ʋ
	GM.resetManager(); // ���Ӹ޴��� ����

	Tetris &player1 = *GM.p1;
	Tetris &player2 = *GM.p2;

	while (1) {
		Sleep(20);
		GM.getKey();
		GM.gamePlay(player1);
		GM.gamePlay(player2);
		GM.pushAttack(player1, player2);
		GM.pushAttack(player2, player1);
		GM.checkWinner(player1, player2);
	}
}//��! 