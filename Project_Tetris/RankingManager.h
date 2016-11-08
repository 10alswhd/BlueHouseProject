#ifndef _RANKING_H
#define _RANKING_H

#include <time.h>
#include "Array.h"

#define ID_SIZE 10

typedef struct _ranking{
	char id[ID_SIZE + 1];
	int score;
	int level;
	int deletedLineCount;
	time_t timestamp;
}Ranking;

typedef struct _rankingManager{
	Array rankings;
}RankingManager;

void RankingManager_Create(RankingManager* rankingManager);
void RankingManager_Add(RankingManager* rankingManager, Ranking ranking);
int RankingManager_Load(RankingManager* rankingManager);
int RankingManager_Save(RankingManager* rankingManager);
void RankingManager_Print(RankingManager* rankingManager);
void RankingManager_Destroy(RankingManager* rankingManager);

#endif
