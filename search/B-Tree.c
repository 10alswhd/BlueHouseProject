#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum { FALSE, TRUE } boolean;
#define MAX_KEY 3 //511
#define B_TREE_T 2 //256

typedef struct Key
{
	int value;
	long f_p;
} Key;

typedef struct Node
{
	int n;
	Key *k; // because index is from 1 not 0
	boolean isLeaf;
	struct Node **children; // because index is from 1 not 0
	struct Node *root;
} Node;


typedef struct SearchResult
{
	Node *resultNode;
	int index;
} SearchResult;

SearchResult b_tree_search(Node *node, Key key);
void b_tree_create(Node *node);
void b_tree_split_child(Node *node, int index);
void b_tree_insert(Node *root, Key k);
void b_tree_insert_nonfull(Node *node, Key k);
void b_tree_delete(void);

void create_b_tree_from_file(FILE *f_seq);

void b_tree_print(Node *T);
void check_file(FILE *f);
void print_record_at_ptr_in_file(FILE *f, long ptr);

int max_key;
int find_key;
int b_t;
Node *T;
FILE *f_seq, *f_out;

int main()
{
	
	char file_name[100];

	printf("Input [FILE_NAME] [NODE_SIZE] [KEY]: ");
	scanf_s("%s", file_name, 100);
	scanf_s("%d", &max_key);
	scanf_s("%d", &find_key);
	b_t = max_key / 2;
	max_key--;


	T = malloc(sizeof(Node));
	b_tree_create(T);

	fopen_s(&f_seq, file_name, "r+b");
	check_file(f_seq);

	// open file to write
	fopen_s(&f_out, "test.txt", "w");

	create_b_tree_from_file(f_seq);
	fclose(f_seq);



	Key K;
	K.value = find_key;

	fopen_s(&f_seq, file_name, "r+b");
	SearchResult sr = b_tree_search(T->root, K);

	if (sr.resultNode) {

	}
	else {
		fprintf(f_out, "[%d]%s|", find_key, "This key cannot be found!\n");
		printf("[%d]%s", find_key, "This key cannot be found!\n");
	}
	//printf("\n%d %d", sr.index, 0);

	fclose(f_seq);
	fclose(f_out);

}

void check_file(FILE *f)
{
	if (!f) {
		printf("%s\n", "Cannot open file!\n");
		exit(-1);
	}
}

void b_tree_print(Node *T)
{
	if (T == NULL)
		return;
	int i = 0;
	for (i = 1; i <= T->n; i++) {
		printf("%d ", T->k[i].value);
	}
	printf(" / ");
	if (!T->isLeaf) {
		for (i = 1; i <= T->n + 1; i++)
			b_tree_print(T->children[i]);
	}
}

void b_tree_create(Node *T)
{
	Node *x = malloc(sizeof(Node));
	x->k = malloc(sizeof(Key)* (max_key + 1));
	x->children = malloc(sizeof(Node *)* (max_key + 1 + 1));
	x->isLeaf = TRUE;
	x->n = 0;
	T->root = x;
}

SearchResult b_tree_search(Node *x, Key k)
{
	// NULL result
	SearchResult *sr = malloc(sizeof(SearchResult));
	sr->index = -1;
	sr->resultNode = NULL;

	int i = 1;
	while (i <= x->n && k.value > x->k[i].value)
		i++;
	if (i <= x->n && k.value == x->k[i].value) {
		print_record_at_ptr_in_file(f_seq, x->k[i].f_p);
		sr->resultNode = x;
		sr->index = i;
		return *sr;
	}
	else if (x->isLeaf) {
		return *sr;
	}
	else {
		print_record_at_ptr_in_file(f_seq, x->k[1].f_p);
		return b_tree_search(x->children[i], k);
	}
}

void b_tree_split_child(Node *x, int i)
{
	int t = b_t;
	int j = 0;

	Node *z = malloc(sizeof(Node));
	z->k = malloc(sizeof(Key)* (max_key + 1));
	z->children = malloc(sizeof(Node *)* (max_key + 1 + 1));

	Node *y = x->children[i];
	z->isLeaf = y->isLeaf;
	z->n = t - 1;

	for (int j = 1; j <= t - 1; j++) {
		z->k[j] = y->k[j + t];
	}

	if (!y->isLeaf) {
		for (j = 1; j <= t; j++) {
			z->children[j] = y->children[j + t];
		}
	}

	y->n = t - 1;
	// Move all children 1 pos to the right and insert z
	for (j = x->n + 1; j >= i + 1; j--) {
		x->children[j + 1] = x->children[j];
	}
	x->children[i + 1] = z;

	// Move all key 1 pos to the right and insert medium value
	for (j = x->n; j >= i; j--) {
		x->k[j + 1] = x->k[j];
	}
	x->k[i] = y->k[t];
	x->n++;
}

void b_tree_insert(Node *T, Key k)
{
	int t = b_t;
	Node *r = T->root;
	if (r->n == 2 * t - 1) {
		Node *s = malloc(sizeof(Node));
		s->k = malloc(sizeof(Key)* (max_key + 1));
		s->children = malloc(sizeof(Node *)* (max_key + 1 + 1));

		T->root = s;
		s->isLeaf = FALSE;
		s->n = 0;
		s->children[1] = r;
		b_tree_split_child(s, 1);
		b_tree_insert_nonfull(s, k);
	}
	else {
		b_tree_insert_nonfull(r, k);
	}
}

void b_tree_insert_nonfull(Node *x, Key k)
{
	int t = b_t;
	int i = x->n;
	int j = 0;

	if (x->isLeaf) {
		while (i >= 1 && k.value <= x->k[i].value) {
			x->k[i + 1] = x->k[i];
			i--;
		}
		x->k[i + 1] = k;
		x->n++;
	}
	else {
		while (i >= 1 && k.value < x->k[i].value) {
			i--;
		}
		i++;
		if (x->children[i]->n == 2 * t - 1) {
			b_tree_split_child(x, i);
			if (k.value > x->k[i].value) {
				i++;
			}
		}

		b_tree_insert_nonfull(x->children[i], k);
	}
}


void create_b_tree_from_file(FILE *f_seq)
{
	long f_p;
	float student_grade;
	char student_sex;
	int16_t fixed_size;
	int16_t student_name_len;
	int student_id;

	char c;
	char *buffer = (char *)malloc(sizeof(char)* 100);
	int i, offset, field_num;

	fseek(f_seq, 0, SEEK_SET);
	while (1) {
		// pointer in file of this record
		//fflush(f_seq);
		f_p = ftell(f_seq);
		if (!fread(&fixed_size, sizeof(int16_t), 1, f_seq)) {
			break;
		}

		fread(&student_id, sizeof(int), 1, f_seq);

		fread(&student_name_len, sizeof(int16_t), 1, f_seq);
		fread(buffer, sizeof(char), student_name_len, f_seq);
		buffer[student_name_len] = NULL; // clear last buffer

		fread(&student_grade, sizeof(float), 1, f_seq);

		fread(&student_sex, sizeof(char), 1, f_seq);


		if (fixed_size > 0) {
			Key new_key;
			new_key.f_p = f_p;
			new_key.value = student_id;

			b_tree_insert(T, new_key);
		}
	}

	free(buffer);
}

void print_record_at_ptr_in_file(FILE *f_seq, long ptr)
{
	long f_p;
	float student_grade;
	char student_sex;
	int16_t fixed_size;
	int16_t student_name_len;
	int student_id;

	char c;
	char *buffer = (char *)malloc(sizeof(char)* 100);
	int i, offset, field_num;

	fseek(f_seq, ptr, SEEK_SET);
	while (1) {
		if (!fread(&fixed_size, sizeof(int16_t), 1, f_seq)) {
			break;
		}

		fread(&student_id, sizeof(int), 1, f_seq);

		fread(&student_name_len, sizeof(int16_t), 1, f_seq);
		fread(buffer, sizeof(char), student_name_len, f_seq);
		buffer[student_name_len] = NULL; // clear last buffer

		fread(&student_grade, sizeof(float), 1, f_seq);

		fread(&student_sex, sizeof(char), 1, f_seq);


		if (fixed_size > 0) {
			//fprintf(f_out, "%d|", fixed_size);
			fprintf(f_out, "%d|", student_id);
			fprintf(f_out, "%s|", buffer);
			fprintf(f_out, "%f|", student_grade);
			fprintf(f_out, "%c\n", student_sex);

			//printf("%d|", fixed_size);
			printf("%d|", student_id);
			printf("%s|", buffer);
			printf("%f|", student_grade);
			printf("%c\n", student_sex);
		}
		break;
	}

	free(buffer);
}

/* test
/*
Key K;
K.value = 1;
b_tree_insert(T, K);
K.value = 2;
b_tree_insert(T, K);
K.value = 3;
b_tree_insert(T, K);
K.value = 4;
b_tree_insert(T, K);
K.value = 5;
b_tree_insert(T, K);
K.value = 6;
b_tree_insert(T, K);
K.value = 7;
b_tree_insert(T, K);
K.value = 8;
b_tree_insert(T, K);
K.value = 9;
b_tree_insert(T, K);
K.value = 10;
b_tree_insert(T, K);
K.value = 11;
b_tree_insert(T, K);
K.value = 12;
b_tree_insert(T, K);
K.value = 13;
b_tree_insert(T, K);
K.value = 14;
b_tree_insert(T, K);
b_tree_print(T->root);
K.value = 5;
SearchResult sr = b_tree_search(T->root, K);
printf("\n%d %d", sr.index, 0);
*/
