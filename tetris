#include "DxLib.h"
#include <ctime>

static const int FRAME_RATE = 10;
static const int DOWN_RATE = 5;
static const int BROCK_LENGTH = 24;
static const int BOARD_WIDTH = 10;
static const int BOARD_HEIGHT = 20;

int BROCK_COLOR[8];
struct {
	// 回転方向の種類
	int r;
	
	// 中心のブロックを基準とした、他のブロックの相対座標
	struct {
		int x, y;
	} p[3];
} BROCK[8] = {
	{1, {{0, 0}, {0, 0}, {0, 0}}}, // Null
	{2, {{0, -1}, {0, 1}, {0, 2}}}, // Tetris
	{1, {{0, 1}, {1, 0}, {1, 1}}}, // Square
	{4, {{0, 1}, {-1, 0}, {1, 0}}}, // T
	{4, {{0, -1}, {0, 1}, {1, -1}}}, // L1
	{4, {{0, -1}, {0, 1}, {-1, -1}}}, // L2
	{2, {{-1, 0}, {0, 1}, {1, 1}}}, // Key1
	{2, {{-1, 0}, {0, -1}, {1, -1}}} // Key2
};

struct STATUS {
	int x, y, r, b;
};

// +2 := 両端
// +3 := 下端(+1)と上端(+2)
int board[BOARD_WIDTH + 2][BOARD_HEIGHT + 3];
bool GAMEOVER = false;

// Wikipedia の rand の項目参照
int getRandom(int max) {
	return (int)(rand() / (RAND_MAX + 1.0) * max);
}

// 色情報をキャッシュ
void setColorValue() {
	BROCK_COLOR[0] = GetColor(255, 255, 255);
	BROCK_COLOR[1] = GetColor(255, 0, 0);
	BROCK_COLOR[2] = GetColor(255, 255, 0);
	BROCK_COLOR[3] = GetColor(0, 255, 0);
	BROCK_COLOR[4] = GetColor(0, 255, 255);
	BROCK_COLOR[5] = GetColor(0, 0, 255);
	BROCK_COLOR[6] = GetColor(255, 0, 255);
	BROCK_COLOR[7] = GetColor(255, 128, 0);
}

void showBoard() {
	ClearDrawScreen();
	// 背景を灰色に
	const int back_ground_color = GetColor(192, 192, 192);
	DrawBox(0, 0, BROCK_LENGTH * BOARD_WIDTH, BROCK_LENGTH * BOARD_HEIGHT, back_ground_color, true);
	
	for(int x = 1; x <= BOARD_WIDTH; x++) {
		for(int y = 1; y <= BOARD_HEIGHT; y++) {
			const int x1 = (x - 1) * BROCK_LENGTH + 1;
			const int y1 = (BOARD_HEIGHT - y) * BROCK_LENGTH + 1;
			const int x2 = x * BROCK_LENGTH - 1;
			const int y2 = (BOARD_HEIGHT - y + 1) * BROCK_LENGTH - 1;

			const int c = BROCK_COLOR[board[x][y]];
			DrawBox(x1, y1, x2, y2, c, true);
		}
	}
	// 実際に表示
	ScreenFlip();
}

// 行列の一次変換を利用して回転移動
// ***** result_x と result_y に対して変更が発生します *****
void rotate(const STATUS &s, int *result_x, int *result_y) {
	const int x = s.x;
	const int y = s.y;
	const int b = s.b;
	const int r = s.r % BROCK[b].r;

	for(int i = 0; i < 3; i++) {
		int ox = BROCK[b].p[i].x;
		int oy = BROCK[b].p[i].y;

		for(int j = 0; j < r; j++) {
			// 反時計回りに90°回転
			int px = -oy;
			int py = ox;
			ox = px;
			oy = py;
		}
		result_x[i] = ox + x;
		result_y[i] = oy + y;
	}
}

// ブロックを置く。
// 置くことができたら true
// できなければ false を返す。
bool putBrock(const STATUS &s) {
	int nx[3], ny[3];

	// 回転させる
	rotate(s, nx, ny);

	bool f = true;
	if(board[s.x][s.y] != 0) f = false;
	for(int i = 0; i < 3; i++) {
		if(board[nx[i]][ny[i]] != 0) f = false;
	}
	if(f == false){
		return false;
	} else {
		board[s.x][s.y] = s.b;
		for(int i = 0; i < 3; i++) {
			board[nx[i]][ny[i]] = s.b;
		}
		return true;
	}
}

// ブロックを削除
void deleteBrock(const STATUS &s) {
	int nx[3], ny[3];

	rotate(s, nx, ny);

	board[s.x][s.y] = 0;
	for(int i = 0; i < 3; i++) {
		board[nx[i]][ny[i]] = 0;
	}
}

// ゲームオーバーの処理。
// putBrockのような動作をしているのは、
// putBrockの仕様が甘いことによる。
// 作り込むならば修正すべき
void gameOver(const STATUS &s) {
	int nx[3], ny[3];

	rotate(s, nx, ny);

	board[s.x][s.y] = s.b;
	for(int i = 0; i < 3; i++) {
		board[nx[i]][ny[i]] = s.b;
	}

	GAMEOVER = true;
	for(int x = 1; x <= BOARD_WIDTH; x++) {
		for(int y = 1; y <= BOARD_HEIGHT; y++) {
			if(board[x][y]) {
				board[x][y] = 1;
			}
		}
	}
	showBoard();
}

// 新しいブロックの生成
// ***** 変数sに対して変更が発生します *****
void nextBrock(STATUS &s) {
	s.x = 5;
	s.y = 20;
	s.r = getRandom(4);
	s.b = getRandom(7) + 1;
	if(!putBrock(s))
		gameOver(s);
}

// 番兵データの初期化
void initBoard() {
	for(int x = 0; x < BOARD_WIDTH + 2; x++) {
		for(int y = 0; y < BOARD_HEIGHT + 3; y++) {
			if(x == 0 || x == BOARD_WIDTH + 1 || y == 0) {
				board[x][y] = 1;
			} else {
				board[x][y] = 0;
			}
		}
	}
}

// 埋まった行を消す処理
void deleteLine() {
	for(int y = 1; y <= BOARD_HEIGHT; y++) {
		bool f = true;
		for(int x = 1; x <= BOARD_WIDTH; x++) {
			if(board[x][y] == 0) {
				f = false;
				break;
			}
		}
		if(f) {
			for(int ny = y; ny <= BOARD_HEIGHT; ny++) {
				for(int nx = 1; nx <= BOARD_WIDTH; nx++) {
					board[nx][ny] = board[nx][ny + 1];
				}
			}
			y--;
		}
	}
}

// ブロックが落ちる処理。
// 固定動作が必要になるため、
// 別関数とした。
// ***** 変数sに対して変更が発生します *****
void brockDown(STATUS &s) {
	deleteBrock(s);
	s.y--;
	if(putBrock(s) == false) {
		s.y++;
		putBrock(s);
		deleteLine();
		nextBrock(s);
		WaitTimer(1000 / FRAME_RATE);
	}
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int cmdShow) {
	// 前処理
	// ウィンドウの大きさを指定
	SetGraphMode(BROCK_LENGTH * BOARD_WIDTH, BROCK_LENGTH * BOARD_HEIGHT, 32);
	// ウィンドウのタイトルを指定
	SetMainWindowText("Tetris");
	// ウィンドウモードにする
	ChangeWindowMode(true);
	if(DxLib_Init() == -1) {
		return -1;
	}
	// 前処理終わり
	// フレームバッファを仕様
	SetDrawScreen(DX_SCREEN_BACK);

	// 初期設定
	// rand() 関数用のシードを与える
	srand((unsigned int)time(NULL));
	// 色データをキャッシュ
	setColorValue();
	// 初期化
	initBoard();

	// ゲームループ
	showBoard();
	// 現在の状態
	STATUS cur;
	 // 最初のブロックを置く
	nextBrock(cur);
	showBoard();
	unsigned int counter = 0;
	while(!GAMEOVER && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == false) {
		bool down = false;
		WaitTimer(1000 / FRAME_RATE);

		// キー操作
		if(CheckHitKey(KEY_INPUT_RIGHT)) {
			deleteBrock(cur);
			cur.x++;
			if(!putBrock(cur)) {
				cur.x--;
				putBrock(cur);
			}
		}
		else if(CheckHitKey(KEY_INPUT_LEFT)) {
			deleteBrock(cur);
			cur.x--;
			if(!putBrock(cur)) {
				cur.x++;
				putBrock(cur);
			}
		}
		else if(CheckHitKey(KEY_INPUT_DOWN)) {
			down = true;
		}
		
		// 移動しながら回転可能
		if(CheckHitKey(KEY_INPUT_UP)) {
			deleteBrock(cur);
			cur.r++;
			if(!putBrock(cur)) {
				cur.r--;
				putBrock(cur);
			}
		}

		// 自動落下
		if(down || counter % DOWN_RATE == 0) {
			brockDown(cur);
		}
		counter++;
		showBoard();
	}
	WaitKey();

	// 終了処理
	DxLib_End();
	return 0;
}
