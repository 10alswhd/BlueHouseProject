#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>

#define WIDTH 4
#define HEIGHT 4

typedef int boolean;
#define true 1
#define false 0

enum Direction { NONE,UP,DOWN,LEFT,RIGHT};
typedef enum Direction Direction;
Direction last_move = NONE;

uint16_t field[HEIGHT][WIDTH];
uint16_t pazzle_count;
uint16_t pazzle_score;
/* ======================================= */
//list
typedef uint16_t list_value_t;
typedef struct _Node{
	list_value_t value;
	struct _Node* next;
	struct _Node* prev;
} Node;

Node node_head,node_tail;
uint16_t list_size;

Node* list_create_node(list_value_t v){
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = v;
	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;
}
uint16_t list_get_size() {
	return list_size;
}

void list_init() {
	list_size = 0;
	node_head.prev = NULL;
	node_head.next = &node_tail;
	node_tail.prev = &node_head;
	node_tail.next = NULL;
}
void list_clear() {
	if(list_size) {
		Node* dp;
		Node* np = node_head.next;
		while(np->next != &node_tail) {
			dp = np;
			np = np->next;
			free(dp);
		}
	}
	list_init();
} 
void list_add_head(list_value_t v) {
	Node* new_node = list_create_node(v);
	//[head]<->[head->next]
	node_head.next->prev = new_node;//[new_node]<-[head->next]
	new_node->next = node_head.next;//[new_node]<->[head->next]
	new_node->prev = &node_head;//[head]<=[new_node]<->[head->next]
	node_head.next = new_node;//[head]<=>[new_node]<->[head->next]

	++list_size;
}
void list_add_tail(list_value_t v) {
	Node* new_node = list_create_node(v);
	//[tail->prev]<->[tail]
	node_tail.prev->next = new_node;//[tail->prev]->[new_node]
	new_node->prev = node_tail.prev;//[tail->prev]<->[new_node]
	new_node->next = &node_tail;//[tail->prev]<->[new_node]->[tail]
	node_tail.prev = new_node;//[tail->prev]<->[new_node]<->[tail]

	++list_size;
}
list_value_t list_get_head(uint16_t index) {
	assert(index < list_size);
	uint16_t i;
	Node* np = node_head.next;
	for(i = 0 ; i != index ; ++i) {
		assert(np != NULL);
		np = np->next;
	}
	return np->value;
}
list_value_t list_get_tail(uint16_t index_of_head) {
	uint16_t index = list_get_size() - index_of_head - 1;
	assert(index < list_size);
	uint16_t i;
	Node* np = node_tail.prev;
	for(i = 0 ; i != index ; ++i) {
		assert(np != NULL);
		np = np->prev;
	}
	return np->value;
}
list_value_t list_get(uint16_t index) {
	return (index < list_get_size() / 2) ? list_get_head(index) : list_get_tail(index);
}
void list_print() {
	int i = 0;
	Node* np = node_head.next;
	while(np != &node_tail) {
		printf("%x ",np->value);
		np = np->next;
	}
	printf("\n");
}
/* ======================================= */
//private functions
uint16_t convert(uint8_t x,uint8_t y) {
	return (x << 8) | y;
}

void move_up(){
	for(uint8_t i = 0 ; i < WIDTH ; ++i) {
		uint8_t dst_p = 0;
		for(uint8_t j = dst_p ; j < HEIGHT ; ++j){
			if(!field[j][i]) continue;
			if(j == dst_p) {
			} else if(field[dst_p][i] == field[j][i]) {
				field[dst_p][i] += field[j][i];
				field[j][i] = 0;
				++dst_p;
			} else {
				if(field[dst_p][i]) ++dst_p;
				uint16_t tmp = field[j][i];
				field[j][i] = 0;
				field[dst_p][i] = tmp;
			}
		}
	}
}
void move_down(){
	for(uint8_t i = 0 ; i < WIDTH ; ++i) {
		uint8_t dst_p = HEIGHT - 1;
		for(uint8_t j = dst_p ; j < HEIGHT ; --j){
			if(!field[j][i]) continue;
			if(j == dst_p) {
			} else if(field[dst_p][i] == field[j][i]) {
				field[dst_p][i] += field[j][i];
				field[j][i] = 0;
				--dst_p;
			} else {
				if(field[dst_p][i]) --dst_p;
				uint16_t tmp = field[j][i];
				field[j][i] = 0;
				field[dst_p][i] = tmp;
			}
		}
	}
}
void move_left(){
	for(uint8_t j = 0 ; j < HEIGHT ; ++j){
		uint8_t dst_p = 0;
		for(uint8_t i = dst_p ; i < WIDTH ; ++i) {
			if(!field[j][i]) continue;
			if(i == dst_p) {
			} else if(field[j][dst_p] == field[j][i]) {
				field[j][dst_p] += field[j][i];
				field[j][i] = 0;
				++dst_p;
			} else {
				if(field[j][dst_p]) ++dst_p;
				uint16_t tmp = field[j][i]; 
				field[j][i] = 0;
				field[j][dst_p] = tmp;
			}
		}
	}
}
void move_right(){
	for(uint8_t j = 0 ; j < HEIGHT ; ++j){
		uint8_t dst_p = WIDTH - 1;
		for(uint8_t i = dst_p; i < WIDTH ; --i) {
			if(!field[j][i]) continue;
			if(i == dst_p) {
			} else if(field[j][dst_p] == field[j][i]) {
				field[j][dst_p] += field[j][i];
				field[j][i] = 0;
				--dst_p;
			} else {
				if(field[j][dst_p]) --dst_p;
				uint16_t tmp = field[j][i];
				field[j][i] = 0;
				field[j][dst_p] = tmp;
			}
		}
	}
}
/* ======================================= */
//private functions
void pazzle_init(){
	for(uint8_t j = 0 ; j < HEIGHT ; ++j) {
		for(uint8_t i = 0 ; i < WIDTH ; ++i) {
			field[j][i] = 0; 
		}
	}
	last_move = NONE;
	pazzle_count = 0;
	pazzle_score = 0;
}
boolean pazzle_move(Direction dir){
	if(dir == last_move) return false;
	switch(dir) {
		case UP:
			move_up();
			break;
		case DOWN:
			move_down();
			break;
		case LEFT:
			move_left();
			break;
		case RIGHT:
			move_right();
			break;
		default:
			return false;
	}
	last_move = dir;
} 
boolean pazzle_update(){
	//配置可能リスト
	list_clear();
	for(uint8_t j = 0 ; j < HEIGHT ; ++j) {
		for(uint8_t i = 0 ; i < WIDTH ; ++i) {
			if(!field[j][i]) list_add_tail(convert(i,j));
		}
	}
	//ゲームオーバー
	if(!list_get_size()) {
		//get maximum
		pazzle_score = 0;
		for(int j = 0 ; j < HEIGHT ; ++j) {
			for(int i = 0 ; i < WIDTH ; ++i) {
				if(pazzle_score < field[j][i]) pazzle_score = field[j][i];
			}
		}
		return false;
	}

	uint16_t index = list_get(rand() % list_get_size());
	uint8_t val = ((rand() % 2) + 1) << 1;
	printf("[create]\t(%d,%d) -> %d\n",index >> 8,index & 0xff,val);

	field[index & 0xff][index >> 8] = val;
	++pazzle_count;
}
void pazzle_print(){
	printf("======== %4d ========\n",pazzle_count);
	for(uint8_t j = 0 ; j < HEIGHT ; ++j) {
		for(uint8_t i = 0 ; i < WIDTH ; ++i) {
			if(!field[j][i]) printf("____ ");
			else printf("%4x ",field[j][i]);
		}
		printf("\n");
	}
}
/* ======================================= */
int main(void) {
	char c;
	Direction next = NONE;
	srand(time(NULL));
	pazzle_init();

	while(true) {
		printf("W,S,A,D>");
		scanf("%c*c",&c);
		switch(c) {
			case 'w':
				next = UP;
				break;
			case 's':
				next = DOWN;
				break;
			case 'a':
				next = LEFT;
				break;
			case 'd':
				next = RIGHT;
				break;
			case 'q':
				return 0;
			case 'n':
				pazzle_init();
				break;
		}
		if(!pazzle_move(next)) continue;
		if(!pazzle_update()) {
			printf("\n\n\n++++++++++++ GAME OVER ++++++++++\nmaximum = %x\n\n\n\n",pazzle_score);
			pazzle_init();
		}
		pazzle_print();
	}
	return 0;
}
