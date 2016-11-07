#include <Windows.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <synchapi.h>

//defines
#define TERM_HEIGHT 20
#define TERM_WIDTH 20
#define FIELD_HEIGHT 20
#define FIELD_WIDTH 20
const char possible_tets[7] = { 'i', 'o', 't', 'l', 'j', 'z', 's' }; //b-but this isn't a define ;~;

//declarations
struct block;
void handle_input();
void handle_blocks();
void clear_array();
void rotate(int direction);
void render();
void clear_area(int height, int width);
void print_block(block * tet);
void remove_tet();
bool check_collision(block * coltet, int newx, int newy);
block * create_tetromino(char tettype);

//global variable definitions and initialization
long tick = 0;
char input = ' ';
int fall_delay = 40;
int lines_cleared;
int field[FIELD_HEIGHT][FIELD_WIDTH];
block * tet = nullptr;
//block * queuedtet = nullptr;
//WINDOW * field_window;

template <int height, int width>
void clear_array(int inputarr[][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			inputarr[i][j] = 0;
		}
	}
}

template <int height, int width>
void copy_array(int from[][width], int to[][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}

struct block
{
	int piece[5][5];
	bool rotateable = true;
	int x = 8;
	int y = 1;
};

int main()
{
	clear_array<FIELD_HEIGHT, FIELD_WIDTH>(field);
	tet = create_tetromino(possible_tets[rand() % 6]);
	initscr();
	noecho();
	resize_window(stdscr, FIELD_HEIGHT, FIELD_WIDTH);
	resize_term(FIELD_HEIGHT + 3,FIELD_WIDTH);
	cbreak();


	render();
	while (true)
	{
		handle_input();
		if (tick % fall_delay == 0)
		{
			handle_blocks();
		}
		tick++;
		render();
		refresh();
	}
}

void handle_input()
{
	input = getch();
	switch(input)
	{
	case 'f':
		throw 1;
		break;
	case 'q':
		rotate(1);
		break;
	case 'e':
		rotate(-1);
		break;
	case 'a':
		if (check_collision(tet, tet->x - 1, tet->y))
		{
			tet->x = max(tet->x - 1, 0);
		}
		break;
	case 'd':
		if (check_collision(tet, tet->x + 1, tet->y))
		{
			tet->x = min(tet->x + 1, FIELD_WIDTH - 1);
		}
		break;
	case 's':
		if (check_collision(tet, tet->x, tet->y + 1))
		{
			tet->y = min(tet->y + 1, FIELD_HEIGHT - 1);
		}
		else
		{
			remove_tet();
		}
		break;
	case 'w': //debug
		delete tet;
		tet = nullptr;
		break;
	}
}

void handle_blocks()
{
	if (!check_collision(tet, tet->x, tet->y + 1))
	{
		remove_tet();
		return;
	}
	tet->y = min(tet->y + 1, FIELD_HEIGHT - 1);
	return;
}

void rotate(int direction)
{
	if (!tet->rotateable) //prevents you from rotating the square tetromino, because that looks ugly.
	{
		return;
	}
	int newpiece[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int jpos = direction * (2 - i);
			int ipos = -direction * (2 - j);
			newpiece[i][j] = tet->piece[ipos + 2][jpos + 2];
		}
	}
	copy_array<5, 5>(newpiece, tet->piece);
}

void render()
{
	move(0, 0);
	clear_area(FIELD_HEIGHT + 3, FIELD_WIDTH);
	addch(input);
	if (tet == nullptr)
	{
		tet = create_tetromino(possible_tets[rand() % 6]);
	}
	move(tet->y, tet->x);
	print_block(tet);

	move(0, 0);
	int startrow;
	int startcol;
	getyx(stdscr, startrow, startcol);
	int currow = startrow;
	int curcol = startcol;
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int j = 0; j < FIELD_WIDTH; j++)
		{
			if (field[i][j] != 0)
			{
				addch('o');
			}
			move(currow, ++curcol);
		}
		curcol = startcol;
		move(++currow, curcol);
	}
	move(startrow, startcol);
	move(0, 0);
}

void print_block(block * tet) //prints tet at the current cursor position. returns the cursor to the starting position.
{
	int startrow;
	int startcol;
	getyx(stdscr, startrow, startcol);
	int currow = startrow;
	int curcol = startcol;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((tet->piece)[i][j] != 0)
			{
				addch('o');
			}
			move(currow, ++curcol);
		}
		curcol = startcol;
		move(++currow, curcol);
	}
	move(startrow, startcol);
}

void clear_area(int height, int width) //clears an area of height height and width width at the current cursor position.
{
	int startrow;
	int startcol;
	getyx(stdscr, startrow, startcol);
	int currow = startrow;
	int curcol = startcol;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			addch(' ');
			move(currow, ++curcol);
		}
		curcol = startcol;
		move(++currow, curcol);
	}
	move(startrow, startcol);
}

//Returns true if the tet can be in the defined position, false otherwise
bool check_collision(block * coltet, int newx, int newy)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			bool blockpresent = coltet->piece[i][j] != 0;
			if (!blockpresent)
			{
				continue;
			}
			else if ((newx + j) >= FIELD_WIDTH  || (newx + j) < 0)
			{
				return false;
			}
			else if ((newy + i) >= FIELD_HEIGHT)
			{
				return false;
			}
			else if (field[newy + i][newx + j] != 0)
			{
				return false;
			}
		}
	}
	return true;
}

void remove_tet()
{
	bool breakout = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (tet->y + i >= FIELD_HEIGHT)
			{
				breakout = true;
				break; //we're going left to right and then down, so if we're below the field, there's no point in going on.
			}
			else if (tet->x + j >= FIELD_WIDTH)
			{
				continue; //here we may actually have lower lines to loop through, so keep going.
			}
			else if (tet->piece[i][j] != 0)
			{
				field[tet->y + i][tet->x + j] = tet->piece[i][j];
			}
		}
		if (breakout)
		{
			break;
		}
	}
	delete tet;
	tet = nullptr;
}

//at the bottom because it's obnoxious
block * create_tetromino(char tettype)
{
	block * newtet = new block;
	if (tettype == 'i') //not a switch because that causes duplicate definition errors.
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
	}
	else if (tettype == 'o')
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
		newtet->rotateable = false;
	}
	else if (tettype == 't')
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
	}
	else if (tettype == 'j')
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
	}
	else if (tettype == 'l')
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
	}
	else if (tettype == 's')
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
	}
	else if (tettype == 'z')
	{
		int piece[5][5] = {
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		};
		copy_array<5, 5>(piece, newtet->piece);
	}
	return newtet;
}
