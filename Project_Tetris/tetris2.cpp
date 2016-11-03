#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { UP, DOWN, LEFT, RIGHT };
typedef unsigned color;

struct vector { int x, y; };
struct tetris { vector v[4]; };

enum { WIDTH = 10, HEIGHT = 20 };
typedef int board[WIDTH * HEIGHT];

struct game
{
	board b;      // cell == 0 is empty else solid
	tetris t;     // shape of block
	int r, x, y;  // rotation and position of block
	int gravtime; // time until next drop
	int gravinit; // time between drops
	int score;    // scoring is by squared number of cleared rows
};

const tetris shapes[] =
{
	{{{-1, 0}, {0,  0}, {1, 0}, {2, 0}}}, // I
	{{{-1, 0}, {0,  0}, {1, 0}, {1, 1}}}, // L
	{{{-1, 1}, {-1, 0}, {0, 0}, {1, 0}}}, // J
	{{{ 0, 0}, {0,  1}, {1, 0}, {1, 1}}}, // O
	{{{-1, 0}, {0,  0}, {0, 1}, {1, 1}}}, // Z
	{{{-1, 1}, {0,  1}, {0, 0}, {0, 1}}}, // S
	{{{-1, 0}, {0,  0}, {1, 0}, {0, 1}}}  // T
};

const vector rotations[][2] =
{
	{{ 1, 0}, {0,  1}}, {{0,  1}, {-1, 0}}, // 0, 90
	{{-1, 0}, {0, -1}}, {{0, -1}, { 1, 0}}  // 180, 270
};

tetris transform(tetris t, int r, int x, int y)
{
	for (vector *v = t.v; v < t.v + 4; v++) {
		const vector *m = rotations[r];
		int vx = v->x, vy = v->y;
		v->x = m[0].x * vx + m[0].y * vy + x;
		v->y = m[1].x * vx + m[1].y * vy + y;
	}
	return t;
}

#define CELL(b, x, y) ((b)[(x) + (y) * WIDTH])

int cell(board b, int x, int y)
{
	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)
		return CELL(b, x, y);
	else
		return 1;
}

int hits(board b, tetris t, int r, int x, int y)
{
	t = transform(t, r, x, y);
	for (vector *v = t.v; v < t.v + 4; v++)
		if (cell(b, v->x, v->y))
			return 1;
	return 0;
}

void put(board b, tetris t)
{
	for (vector *v = t.v; v < t.v + 4; v++)
		CELL(b, v->x, v->y) = 1;
}

void gameover(game *g)
{
	printf("score: %d\n", g->score);
	exit(0);
}

void newblock(game *g)
{
	g->t = shapes[rand() % (sizeof(shapes) / sizeof(*shapes))];
	g->r = 0;
	g->x = WIDTH / 2;
	g->y = 0;

	if (hits(g->b, g->t, g->r, g->x, g->y))
		gameover(g);
}

void newgame(game *g)
{
	bzero(g->b, sizeof(g->b));
	newblock(g);
	g->gravtime = g->gravinit;
	g->score = 0;
}

void checkrows(game *g)
{
	const int rowsize = WIDTH * sizeof(*g->b);
	int cleared = 0;
	for (int y = 0; y < HEIGHT; y++) {
		int x;
		for (x = 0; x < WIDTH && cell(g->b, x, y); x++) {}
		if (x == WIDTH) {
			cleared++;
			memmove(g->b + rowsize, g->b, y * rowsize);
			bzero(g->b, rowsize);
		}
	}
	g->score += cleared * cleared;
}

void drop(game *g)
{
	if (hits(g->b, g->t, g->r, g->x, ++g->y)) {
		put(g->b, transform(g->t, g->r, g->x, g->y - 1));
		checkrows(g);
		newblock(g);
	}
}

void input(game *g, int key)
{
	int dr = 0, dx = 0;
	switch (key) {
	case DOWN:  drop(g); return;
	case UP:    dr = +1; break;
	case LEFT:  dx = -1; break;
	case RIGHT: dx = +1; break;
	}

	int r = (g->r + dr) % 4, x = g->x + dx;
	if (!hits(g->b, g->t, r, x, g->y)) {
		g->r = r; g->x = x;
	}
}

void tick(game *g)
{
	if (--g->gravtime == 0) {
		g->gravtime = g->gravinit;
		drop(g);
	}
}

void rect(color *fb, int pitch, int x, int y, int w, int h, color c)
{
	for (fb += x + y * pitch, y = 0; y < h; y++, fb += pitch)
		for (x = 0; x < w; x++, fb++)
			*fb = c;
}

void draw(game *g, color *fb, int size, int pitch, int cellwidth, int cellheight)
{
	int w = cellwidth, h = cellheight;

	bzero(fb, size);

	tetris t = transform(g->t, g->r, g->x, g->y);
	for (vector *v = t.v; v < t.v + 4; v++)
		rect(fb, pitch, v->x * w, v->y * h, w, h, 0x00FF00);

	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++) {
			color c = cell(g->b, x, y) ? 0x0000FF : 0x000000;
			rect(fb, pitch, x * w, y * h, w, h, c);
		}
}

int main()
{
	extern int getkey(), getfbsize(), getfbpitch();
	extern color *getfb();

	game g;
	g.gravinit = 100;
	newgame(&g);

	while (1) {
		input(&g, getkey());
		tick(&g);
		draw(&g, getfb(), getfbsize(), getfbpitch(), 10, 10);
	}
	return 0;
}
