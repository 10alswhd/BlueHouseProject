#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "go.h"
#include "board.h"
#include "types.h"
#include "minimax.h"
#include "pee.h"

#define MAX_MM_DEPTH 10
static board boards[MAX_MM_DEPTH];
static int max_depth;

static int rate(int depth){
	int r = 0;
	int i;
	int j;
	for(i = 0; i < BOARD_SIZ; ++i){
		for(j = 0; j < BOARD_SIZ; ++j){
			switch(boards[depth].p[i][j]){
				case BLACK_STONE:
					r++;
					break;
				case WHITE_STONE:
					r--;
					break;
			}
		}
	}
	return r;
}

static void noplay(int depth){
	memcpy(&boards[depth + 1], &boards[depth], sizeof(boards[depth]));
}

static int max(int a, int b){
	return a > b ? a : b;
}

static int min(int a, int b){
	return a > b ? b : a;
}

static int minimax2(int depth, int alpha, int beta, bool is_black, bool passed_last){
	if(depth == max_depth)
		return rate(depth - 1);
	int i;
	int j;
	if(is_black){
		for(i = 0; i < BOARD_SIZ; ++i){
			for(j = 0; j < BOARD_SIZ; ++j){
				if(boards[depth].p[i][j] == EMPTY){
					if(!play((board *)&boards[depth], (board *)&boards[depth - 1], (board *)&boards[depth + 1], i, j, TRUE))
						continue; /* ko or suicide caught */
					alpha = max(alpha, minimax2(depth + 1, alpha, beta, FALSE, FALSE));
					if(beta <= alpha)
						break;
				}
			}
		}
		if(passed_last)
			return rate(depth);
		noplay(depth);
		return max(alpha, minimax2(depth + 1, alpha, beta, FALSE, TRUE));
	}else{
		for(i = 0; i < BOARD_SIZ; ++i){
			for(j = 0; j < BOARD_SIZ; ++j){
				if(boards[depth].p[i][j] == EMPTY){
					if(!play((board *)&boards[depth], (board *)&boards[depth - 1], (board *)&boards[depth + 1], i, j, FALSE))
						continue; /* ko or suicide caught */
					beta = min(beta, minimax2(depth + 1, alpha, beta, TRUE, FALSE));
					if(beta <= alpha)
						break;
				}
			}
		}
		if(passed_last)
			return rate(depth);
		noplay(depth);
		return min(beta, minimax2(depth + 1, alpha, beta, TRUE, TRUE));
	}
}

void minimax(const in_board * in_b, out_board * out_b, unsigned char pliers){
	max_depth = (pliers * 2 - 1);
	if(MAX_MM_DEPTH < max_depth){
		fprintf(stderr, "minimax: warning: search too deep; aborting\n");
		exit(EXIT_FAILURE);
	}

	printf("minimax: search (%d pliers) starting\n", pliers);

	int i;
	int j;
	for(i = 0; i < BOARD_SIZ; ++i)
		for(j = 0; j < BOARD_SIZ; ++j)
			boards[0].p[i][j] = in_b->pos.p[i][j];

	if(in_b->black_to_play){
		int best = MIN_VALUE;
		for(i = 0; i < BOARD_SIZ; ++i)
			for(j = 0; j < BOARD_SIZ; ++j){
				if(boards[0].p[i][j] == EMPTY){
					if(!play_no_ko((board *)&boards[0], (board *)&boards[1], i, j, TRUE))
						continue; /* ko or suicide caught */
					out_b->value[i][j] = minimax2(1, best, MAX_VALUE, FALSE, FALSE);
				}
			}
		if(in_b->passed_last){
			out_b->pass = rate(0);
		}else{
			noplay(0);
			out_b->pass = minimax2(1, best, MAX_VALUE, FALSE, TRUE);
		}
	}else{
		int best = MAX_VALUE;
		for(i = 0; i < BOARD_SIZ; ++i)
			for(j = 0; j < BOARD_SIZ; ++j){
				if(boards[0].p[i][j] == EMPTY){
					if(!play_no_ko((board *)&boards[0], (board *)&boards[1], i, j, FALSE))
						continue; /* ko or suicide caught */
					out_b->value[i][j] = minimax2(1, MIN_VALUE, best, TRUE, FALSE);
				}
			}
		if(in_b->passed_last){
			out_b->pass = rate(0);
		}else{
			noplay(0);
			out_b->pass = minimax2(1, MIN_VALUE, best, TRUE, TRUE);
		}
	}
	printf("minimax: search (%d pliers) finished\n", pliers);
}
