#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 200100
#define MAXL 18

typedef struct {
	int key, height;
	int next[MAXL];
} elem;

elem skip[MAXN];
int nextElem = 2; // 0 -> NIL, 1 -> start

void initskip(){
	skip[0].key = 1<<30;
	skip[0].height = MAXL;
	skip[1].height = MAXL;
}

int newHeight(void){
	int h = 1, x;
	for (x = rand(); h < MAXL && x % 2; x /= 2)
		h++;
	return h;
}

int newElem(int key){
	skip[nextElem].key = key;
	skip[nextElem].height = newHeight();
	return nextElem++;
}

int search(int key){
	int curr = 1, i;

	for (i = MAXL-1; i >= 0; i--)
		while(key > skip[skip[curr].next[i]].key)
			curr = skip[curr].next[i];

	curr = skip[curr].next[0];

	return skip[curr].key == key ? curr : 0;
}

bool isInside(int key){
	return search(key) != 0;
}

void insert(int key){
	int curr = 1, i;
	int e = newElem(key);

	if (isInside(key)) return;

	for (i = MAXL-1; i >= 0; i--){
		while(key > skip[skip[curr].next[i]].key)
			curr = skip[curr].next[i];

		if (i < skip[e].height){
			skip[e].next[i] = skip[curr].next[i];
			skip[curr].next[i] = e;
		}
	}
}

void delete(int key){
	int curr = 1, i;

	for (i = MAXL-1; i >= 0; i--){
		while(key > skip[skip[curr].next[i]].key)
			curr = skip[curr].next[i];

		if (skip[skip[curr].next[i]].key == key)
			skip[curr].next[i] = skip[skip[curr].next[i]].next[i];
	}
}

int main(void){
	initskip();
	
	insert(1);
	printf("%d\n", isInside(1));
	delete(1);
	printf("%d\n", isInside(1));

	return 0;
}
