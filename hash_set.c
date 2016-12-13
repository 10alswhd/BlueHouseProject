/*
 * hash_set.c
 *
 *  Created on: Sep 28, 2014
 *      Author: jinxing
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <resolv.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

char __pause_buf[8] = {0};
#define PAUSE() { printf("Press Enter to continue ...");\
				fflush(stdin);fgets(__pause_buf, 8, stdin);}

#define HASH_TO_INDEX(hash, size) ((hash) % (size))

#define BUF_LEN	128
char buf[BUF_LEN] = {0};

unsigned long sdbm_hash(const char *str){
	unsigned long hash = 0;
	int c;
	while((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return hash;
}

size_t g_calloc_cnt = 0;
size_t g_calloc_total = 0;
void *my_calloc(size_t n, size_t size){
	void *r = calloc(n, size);
	if(!r){
		perror("malloc failed");
		exit(1);
	}
	g_calloc_cnt += 1;
	g_calloc_total += size * n;
	return r;
}

long g_free_cnt = 0;
void my_free(void *block){
	free(block);
	g_free_cnt += 1;
}

int get_prime(size_t num){
	size_t i = 0, c = 0;
	while(1){
		c = (size_t)sqrt(num);
		for(i=2; i<=c && num % i != 0; i++);
		if(i > c) break;
		num++;
	}
	return num;
}

double my_time(void){
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (double)tv.tv_sec + tv.tv_usec/1000000.0;
}

typedef struct elem_t_ {
	char *key;
	struct elem_t_ *next;
}elem_t;

void free_elem_deep(elem_t *elem){
	if(elem->key)
		my_free(elem->key);
	my_free(elem);
}

typedef struct set_t_ {
	size_t size;
	size_t count;
	elem_t *elems;
} set_t;

set_t* set_create(size_t size){
	set_t *nt = my_calloc(1, sizeof(set_t));
	elem_t *elems = my_calloc(size, sizeof(elem_t));
	nt->size = size;
	nt->count = 0;
	nt->elems = elems;
	return nt;
}

size_t set_add_elem(set_t *t, elem_t *elem){
	size_t new_size = 0;
	size_t index = 0;
	size_t deep = 0;
	elem_t tmp_elem;
	elem_t *p = 0;
	unsigned long hash = sdbm_hash(elem->key);

	elem->next = NULL;
	index = HASH_TO_INDEX(hash, t->size);
	p = t->elems + index;
	while(p && p->key){
		if(strcmp(p->key, elem->key) == 0){
			free_elem_deep(elem);
			return index;
		}
		deep += 1;
		p = p->next;
	}
	if(deep > log2(t->size)){
		size_t new_size = get_prime(t->size*2);
		set_expand(t, new_size);
		return set_add_elem(t, elem);
	}
//	printf("add %s to %ld\n", str, index);
	if(deep){
		tmp_elem.key = t->elems[index].key;
		tmp_elem.next = t->elems[index].next;
		t->elems[index].key = elem->key;
		t->elems[index].next = elem;
		elem->key = tmp_elem.key;
		elem->next = tmp_elem.next;
	}else{
		t->elems[index].key = elem->key;
		t->elems[index].next = elem->next;
		my_free(elem);
	}
	t->count++;

	return index;
}

size_t set_add_key(set_t *t, char *str, char nocopy){
	elem_t *elem = my_calloc(1, sizeof(elem_t));
	elem->next = NULL;
	if(nocopy){
		elem->key = str;
	}else{
		elem->key = my_calloc(strlen(str)+1, sizeof(char));
		strcpy(elem->key, str);
	}
	return set_add_elem(t, elem);
}

int set_expand(set_t *t, size_t size){
	size_t i=0, idx=0, cfct_cnt = 0;
	size_t max_depth = 0, curr_depth =0;
	elem_t *p = NULL, *q = NULL;
	set_t *nt = set_create(size);

	printf("expand to %ld\n", size);
	for (i = 0; i < t->size; i++){
		curr_depth = 0;
		if(t->elems[i].key){
			set_add_key(nt, t->elems[i].key, 1);
			curr_depth++;
		}
		p = t->elems[i].next;
		while(p){
			q = p;
			p = p->next;
			set_add_elem(nt, q);
//			set_add_key(&nt, q->key);
//			free_elem_deep(q);
			curr_depth++;
		}
		if(curr_depth){
			cfct_cnt++;
			max_depth = MAX(max_depth, curr_depth);
		}
	}
	printf("table count: %6ld/%-6ld, conflict rate: %-3.2lf%, usage: %-3.2lf%, "
			"max depth: %-2ld, expand to: %-6ld\n",
			t->count, t->size, cfct_cnt*100.0/t->size, t->count*100.0/t->size, max_depth, size);

	t->size = nt->size;
	t->count = nt->count;
	my_free(t->elems);
	t->elems = nt->elems;
	my_free(nt);
	return 0;
}

elem_t* set_search(set_t *t, char *key){
	elem_t *p = 0;
	p = t->elems + HASH_TO_INDEX(sdbm_hash(key), t->size);
	while(p && p->key){
		if(strcmp(p->key, key) == 0){
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void set_print(set_t *t){
	elem_t *p = 0;
	size_t i = 0;
	size_t cfct_cnt = 0;
	size_t max_depth = 0, curr_depth =0;
	char *max_depth_key = NULL, *curr_key = NULL;
	for (i = 0; i < t->size; i++){
		p = t->elems+i;
		curr_depth = 0;
		while(p && p->key){
//			printf("key: %s, index: %d\n", p->key, i);
			curr_key = p->key;
			curr_depth++;
			p = p->next;
		}
		if(curr_depth){
			cfct_cnt++;
			if( curr_depth > max_depth){
				max_depth = curr_depth;
				max_depth_key = curr_key;
			}
		}
	}
	printf("table count: %6ld/%-6ld, conflict rate: %-3.2lf%, usage: %-3.2lf%, "
			"max depth: %-2ld(key: %s)\n",
			t->count, t->size, cfct_cnt*100.0/t->size, t->count*100.0/t->size, max_depth, max_depth_key);
	printf("table count: %ld, table size: %ld, mem: %.2lfK\n",
			t->count, t->size, sizeof(elem_t)*t->count/1024.0);
}

void test(const char* infile, char no_free){
	char buf[BUF_LEN] = {0};
	set_t *table = set_create(2);
	size_t str_calloc_cnt = 0, i = 0;
	printf("created\n");
	FILE *fp = fopen(infile, "rb");
	size_t cnt = 0;

	while(fgets(buf, BUF_LEN, fp)){
	    char *sp_pos;
	    if((sp_pos = strchr(buf, '\r')))
	    	*sp_pos = 0;
	    if((sp_pos = strchr(buf, '\n')))
	    	*sp_pos = 0;
		set_add_key(table, buf, 0);
		cnt++;
	}
	fclose(fp);

	set_print(table);

	double st = my_time();
	for(i=0; i<10000*100; i++){
		set_search(table, "a8zLX");
	}
	printf("search return: %ld, cost: %lf\n",
				set_search(table, "a8zLX"), my_time()-st);

	printf("fread count: %ld\n", cnt++);
	printf("g_calloct_cnt: %ld\n", g_calloc_cnt);
	printf("g_calloc_total: %ld\n", g_calloc_total);
	if(no_free)
		return ;

	size_t free_str_cnt = 0;
	set_t *t = table;
	elem_t *p, *q;
	fgets(buf, BUF_LEN, stdin);
	for (i = 0; i < t->size; i++){
		if(t->elems[i].key){
//			printf("free string: %s\n", t->elems[i].key);
			my_free(t->elems[i].key);
		}
		p = t->elems[i].next;
		while(p){
			q = p;
			p = p->next;
//			printf("free string: %s\n", q->key);
			free_elem_deep(q);
		}
	}
	my_free(t->elems);
	my_free(t);
	printf("g_free_cnt: %ld\n", g_free_cnt);
}

int main(int argc, char *argv[]){
	if (argc < 2){
		perror("args error");
		exit(1);
	}

	test(argv[1], 0);
	fgets(buf, BUF_LEN, stdin);
//	test(argv[1], 0);
//	fgets(buf, BUF_LEN, stdin);
//	test(argv[1], 0);
//	fgets(buf, BUF_LEN, stdin);
//	return 7205207877725613306%4;
}
