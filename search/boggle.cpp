#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "fileio.h"
#define TRUE (1)
#define FALSE (0)
#define MAX_BSIZE 1000

typedef struct _relativeCoordinate
{
	int x;
	int y;
}RCoordinate;

int initBoard(FILE *fp);
int boggleGame(const char *searchWord);
int hasWord(int y, int x, const char *word);
int inRange(int y, int x);

int maxX;
int maxY;

RCoordinate RCXY[8] = { {-1,-1}, {-1,0}, {-1,1}, {1,-1}, {1,0}, {1,1}, {0,-1}, {0,1} };

char board[MAX_BSIZE][MAX_BSIZE + 2];

int main()
{
	FILE *fp;
	int res;
	char *searchWord[] = { "RABBIT", "LGE", "ASDVX" };
	int count = 0;
	fp = fileOpen("C://Users//YongWhan//Desktop//boggleGame.txt", "rt");
	assert(fp != NULL);

	while (initBoard(fp))
	{
		res = boggleGame(searchWord[count]);
		if (res != NULL)
			printf("+ Existence!!(%s)\n", searchWord[count]);
		else
			printf("- Nonexistence!!(%s)\n", searchWord[count]);
		++count;
	}
	fclose(fp);

	return 0;
}

int initBoard(FILE *fp)
{
	int i;
	fscanf(fp, "%d %d\n", &maxY, &maxX);
	if (maxY == 0 || maxX == 0) return FALSE;

	for (i = 0; i < maxY; ++i)
	{
		fgets(board[i], maxX + 2, fp);
		board[i][maxX] = '\0';
		puts(board[i]);
	}
	return TRUE;
}

int boggleGame(const char *searchWord)
{
	int i, j;
	int res;
	for (i = 0; i < maxY; i++)
	{
		for (j = 0; j < maxX; j++)
		{
			res = hasWord(i, j, searchWord);

			if (res == TRUE)
				return TRUE;
		}
	}
	return FALSE;
}

int inRange(int y, int x)
{
	if (y >= 0 && y < maxY && x >= 0 && x < maxX)
		return TRUE;
	else
		return FALSE;
}

int hasWord(int y, int x, const char *word)
{
	if (*word == '\0')
		return TRUE;
	if (inRange(y, x) == TRUE) {
		if (*word == board[y][x]) {
			for (int i = 0; i < 8; i++) {
				if (hasWord(y + RCXY[i].y, x + RCXY[i].x, word + 1) == TRUE) {
					return TRUE;
				}
			}
		}
		else
			return FALSE;
	}
	else
		return FALSE;
	return FALSE;
}
Raw
 bogglegame.txt
5 5
URLPM
XPRET
GIAET
XTNZY
XOQRS
5 5
GGGGS
NELEN
NELEN
NELEN
TLLLL
3 10
QWERTYUIOP
ASDFGHJKLL
ZXCVBNMMMM
0 0
