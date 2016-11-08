#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RankingManager.h"
#include "Util.h"
#include "Constant.h"

#define RANKINGS_CAPACITY 100

#define RANKING_POSITION_X_TO_PRINT 5
#define RANKING_POSITION_Y_TO_PRINT 5

#define TIMESTAMP_FOR_PRINT_SIZE 100

#define RANKING_FILE ".\\..\\res\\tetrisRanking.dat"

static int _RankingManager_GetLength(RankingManager* rankingManager);
static int _RankingManager_GetCapacity(RankingManager* rankingManager);
static int _RankingManager_IsFull(RankingManager* rankingManager);
static Ranking _RankingManager_GetAt(RankingManager* rankingManager, int index);
static void _RankingManager_SortOrderByScore(RankingManager* rankingManager, int** indexes);
static int _CompareRankings(const void* one, const void* other);

void RankingManager_Create(RankingManager* rankingManager){
	Array_Create(&rankingManager->rankings, RANKINGS_CAPACITY, sizeof(Ranking));
}

void RankingManager_Add(RankingManager* rankingManager, Ranking ranking){
	if (!_RankingManager_IsFull(rankingManager)){
		Array_Store(&rankingManager->rankings, rankingManager->rankings.length, &ranking, sizeof(Ranking));
	}
	else{
		Array_AppendFromRear(&rankingManager->rankings, &ranking, sizeof(Ranking));
	}
}

int RankingManager_Load(RankingManager* rankingManager){
	FILE* file = fopen(RANKING_FILE, "rb");
	Ranking ranking;
	int readSize;
	if (file){
		while (!feof(file)){
			readSize = fread(&ranking, 1, sizeof(Ranking), file);
			if (readSize < sizeof(Ranking)){
				break;
			}
			RankingManager_Add(rankingManager, ranking);
		}
		fclose(file);
		return True;
	}
	else{
		return False;
	}
}

int RankingManager_Save(RankingManager* rankingManager){
	FILE* file = fopen(RANKING_FILE, "wb");
	Ranking ranking;
	int i;
	if (file){
		for (i = 0; i < _RankingManager_GetLength(rankingManager); i++){
			ranking = _RankingManager_GetAt(rankingManager, i);
			fwrite(&ranking, sizeof(Ranking), 1, file);
		}
		fclose(file);
		return True;
	}
	else{
		return False;
	}
}

void RankingManager_Print(RankingManager* rankingManager){
	int i;
	char timestampForPrint[TIMESTAMP_FOR_PRINT_SIZE];
	struct tm* pTm;
	int x = RANKING_POSITION_X_TO_PRINT;
	int y = RANKING_POSITION_Y_TO_PRINT;
	int* indexes = (int*)calloc(_RankingManager_GetLength(rankingManager), sizeof(int));
	system("cls");
	CursorUtil_GotoXY(x, y++);
	printf("-------------------------- R A N K I N G -----------------------------");
	CursorUtil_GotoXY(x, y++);
	printf("======================================================================");
	CursorUtil_GotoXY(x, y++);
	printf("%5s%10s%10s%10s%10s%25s", "No", "ID", "SCORE", "LEVEL", "LINES", "DATE AND TIME");
	CursorUtil_GotoXY(x, y++);
	printf("----------------------------------------------------------------------");
	CursorUtil_GotoXY(x, y++);
	_RankingManager_SortOrderByScore(rankingManager, &indexes);
	for (i = 0; i < _RankingManager_GetLength(rankingManager); i++){
		Ranking ranking;
		Array_GetAt(&rankingManager->rankings, indexes[i], &ranking, sizeof(Ranking));
		pTm = localtime(&ranking.timestamp);
		strftime(timestampForPrint, sizeof(timestampForPrint), "%Y-%m-%d %H:%M:%S", pTm);
		printf("%5d%10s%10d%10d%10d%25s", i + 1, ranking.id, ranking.score, ranking.level, ranking.deletedLineCount, timestampForPrint);
		CursorUtil_GotoXY(x, y++);
	}
	printf("======================================================================");
	if (indexes){
		free(indexes);
		indexes = NULL;
	}
	getchar();
}

void RankingManager_Destroy(RankingManager* rankingManager){
	Array_Destroy(&rankingManager->rankings);
}

static int _RankingManager_GetLength(RankingManager* rankingManager){
	return rankingManager->rankings.length;
}

static int _RankingManager_GetCapacity(RankingManager* rankingManager){
	return rankingManager->rankings.capacity;
}

static int _RankingManager_IsFull(RankingManager* rankingManager){
	return (_RankingManager_GetCapacity(rankingManager) == _RankingManager_GetLength(rankingManager));
}

static Ranking _RankingManager_GetAt(RankingManager* rankingManager, int index){
	Ranking ranking;
	Array_GetAt(&rankingManager->rankings, index, &ranking, sizeof(Ranking));
	return ranking;
}

static void _RankingManager_SortOrderByScore(RankingManager* rankingManager, int** indexes){
	Array_Indirect_InsertionSort(&rankingManager->rankings, indexes, sizeof(Ranking), _CompareRankings);
}

static int _CompareRankings(const void* one, const void* other){
	return ((Ranking*)other)->score - ((Ranking*)one)->score;
}
