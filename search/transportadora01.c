#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó genérico usado para Pilha e Fila
struct Node {
	int val;
	struct Node *next;
};

// Estrutura de Pilha com length de itens e weight
struct Stack {
	int length;
	int weight;
	struct Node *top;

	void (*push)(struct Stack *self, int value);
	int (*pop)(struct Stack *self);
};

// Nó específico para caminhão, contendo uma Pilha de storage
struct Node_Truck {
	int max;
	struct Stack *storage;
	struct Node_Truck *next;
};

// Estrutura de Lista com length e Nó de caminhão
struct List {
	int length;
	struct Node_Truck *head;

	void (*insert)(struct List *self, struct Node_Truck *prev, int value);
	int (*delete)(struct List *self);
	struct Node_Truck *(*find)(struct List *self, int value);
};

// Estrutura de Fila com length de itens e weight
struct Queue {
	int length;
	int weight;
	struct Node *head;
	struct Node *tail;

	void (*queue)(struct Queue *self, int value);
	int (*dequeue)(struct Queue *self);	
};

// Função para checar alocação
void *ec_malloc(unsigned int size);

// Funções de inicialização, destruição e limpeza para Lista, Pilha e Fila
struct List *new_node_list();
void list_free(struct List *self);
void list_clear(struct List *self);

struct Stack *new_node_stack();
void stack_free(struct Stack *self);
void stack_clear(struct Stack *self);

struct Queue *new_node_queue();
void queue_free(struct Queue *self);
void queue_clear(struct Queue *self);

// Operações básicas de Lista
void insert_list(struct List *self, struct Node_Truck *prev, int value);
int delete_list(struct List *self);
struct Node_Truck *find_list(struct List *self, int value);

// Operações básicas de Pilha
void push_stack(struct Stack *self, int value);
int pop_stack(struct Stack *self);

// Operações básicas de Fila
void queue_queue(struct Queue *self, int value);
int dequeue_queue(struct Queue *self);

int main()
{
	int n;
	char opt[10];
	int value;
	char caso = 1;
	char loop = 1;

	// Inicializa estruturas
	struct List *list = new_node_list();
	struct Queue *queue = new_node_queue();
	
	scanf("%d", &n);
	while (caso) {
		caso = 0;
		int i;
		for (i = 0; i < n; ++i) {
			scanf("%d", &value);
			if (i == 0) {
				list->head = malloc(sizeof(struct Node_Truck));
				memset(list->head, 0, sizeof(struct Node_Truck));
				list->head->max = value;
				list->head->storage = new_node_stack();
				list->length++;
			} else {
				list->insert(list, list->find(list, i - 1), value);
			}
		}
		loop = 1;
		getchar();
		struct Node_Truck *tmp;

		while (loop == 1) {
			if (scanf("%s", opt) == EOF) {
					loop = 0;
			} else if (opt[0] > 59) { // maior que 59 significa que não é nem um algarismo ou \n
				scanf("%d", &value);
				switch (opt[0]) {
					case 'A':
						queue->queue(queue, value);
						printf("%d %d\n", queue->length, queue->weight);
						break;
					case 'L':
						tmp = list->find(list, value);
						while (queue->head != NULL && queue->head->val + tmp->storage->weight <= tmp->max && queue->length > 0)
							tmp->storage->push(tmp->storage, queue->dequeue(queue));
						printf("%d %d\n", value, tmp->storage->length);
						break;
					case 'D':
						tmp = list->find(list, value);
						if (tmp != NULL && tmp->storage->length != 0)
							tmp->storage->pop(tmp->storage);
						printf("%d %d\n", value, tmp->storage->length);
						break;
					case 'I':
						tmp = list->find(list, value);
						if (tmp != NULL)
							printf("%d %d %d\n", value, tmp->storage->length, tmp->storage->weight);
						else
							printf("NULL\n");
						break;
				}
				getchar();
			} else {
				loop = 0;
				n = atoi(opt);
				caso++;
				printf("\n");
			}
		}
		list_clear(list);
		queue_clear(queue);
	}
	list_free(list);
	queue_free(queue);

	return 0;
}

void *ec_malloc(unsigned int size)
{
	void *ptr;
	ptr = malloc(size);
	if (ptr == NULL) {
		printf("Erro ao alocar memoria\n");
		exit(-1);
	}

	return ptr;
}
			
struct List *new_node_list()
{
	struct List *tmp = ec_malloc(sizeof(struct List));
	tmp->length = 0;
	tmp->head = NULL;

	tmp->insert = insert_list;
	tmp->delete = delete_list;
	tmp->find = find_list;

	return tmp;
}

void list_free(struct List *self)
{
	free(self->head);
	free(self);
}

void list_clear(struct List *self)
{
	while (self->length != 0) 
		self->delete(self);
}

struct Stack *new_node_stack()
{
	struct Stack *tmp = ec_malloc(sizeof(struct Stack));
	tmp->length = 0;
	tmp->weight = 0;
	tmp->top = NULL;

	tmp->pop = pop_stack;
	tmp->push = push_stack;

	return tmp;
}

void stack_free(struct Stack *self)
{
	free(self->top);
	free(self);
}

void stack_clear(struct Stack *self)
{
	while (self->length != 0)
		self->pop(self);
}

struct Queue *new_node_queue()
{
	struct Queue *tmp = ec_malloc(sizeof(struct Queue));
	tmp->length = 0;
	tmp->weight = 0;
	tmp->head = NULL;
	tmp->tail = NULL;

	tmp->queue = queue_queue;
	tmp->dequeue = dequeue_queue;

	return tmp;
}

void queue_free(struct Queue *self)
{
	free(self->head);
	if (self->tail != NULL)
		free(self->tail);
	free(self);
}

void queue_clear(struct Queue *self)
{
	while (self->length != 0)
		self->dequeue(self);
}

void insert_list(struct List *self, struct Node_Truck *prev, int value)
{
	self->length++;
	struct Node_Truck *tmp = ec_malloc(sizeof(struct Node_Truck));
	struct Stack *tmp_stack = new_node_stack();
	tmp->max = value;
	tmp->storage = tmp_stack;
	tmp->next = NULL;

	if (prev->next != NULL) {
		struct Node_Truck *swp = prev->next;
		prev->next = tmp;
		tmp->next = swp;
	} else {
		prev->next = tmp;
	}
}	

int delete_list(struct List *self)
{
	struct Node_Truck *tmp = self->head;
	if (self->head->next == NULL) {
		self->head = NULL;
	} else {
		self->head = tmp->next;
	}	
	stack_clear(tmp->storage);
	stack_free(tmp->storage);
	int value = tmp->max;
	self->length--;
	free(tmp);
	return value;

}

struct Node_Truck *find_list(struct List *self, int value)
{
	if (value == 0)
		return self->head;
	else {
		struct Node_Truck *tmp = self->head;
		int i;
		for (i = 1, tmp = tmp->next; i < value; ++i, tmp = tmp->next);
	       	return tmp;
	}	
}

void push_stack(struct Stack *self, int value)
{
	struct Node *tmp = ec_malloc(sizeof(struct Node));
	tmp->val = value;
	self->length++;
	self->weight += value;
	if (self->top != NULL) {
		tmp->next = self->top;
		self->top = tmp;
	} else {
		tmp->next = NULL;
		self->top = tmp;
	}
}

int pop_stack(struct Stack *self)
{
	if (self->length == 0)
		return 0;
	struct Node *tmp = self->top;
	int value = tmp->val;
	self->length--;
	self->weight -= value;
	self->top = tmp->next;
	free(tmp);
	return value;
}

void queue_queue(struct Queue *self, int value)
{
	struct Node *tmp = ec_malloc(sizeof(struct Node));
	tmp->val = value;
	self->length++;
	self->weight += value;
	if (self->tail != NULL) {
		self->tail->next = tmp;
		self->tail = tmp;	
	} else {
		tmp->next = NULL;
		self->head = tmp;
		self->tail = tmp;
	}
}

int dequeue_queue(struct Queue *self)
{
	if (self->length == 0)
		return 0;
	struct Node *tmp = self->head;
	int value = tmp->val;	
	self->length--;
	self->weight -= value;
	if (self->tail == self->head) {
		self->tail = self->head = NULL;
		free(tmp);
	} else {
		self->head = tmp->next;
		free(tmp);
	}

	return value;
}
Raw
 transportadora02.c
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int element;
	struct Sentinel *storage;
	struct Node *next;
};

struct Sentinel {
	struct Node *head;
	struct Node *tail;
	int length;
	int weight;

	void (*insert)(struct Sentinel *self, struct Node *t, struct Node *x);
	int (*del)(struct Sentinel *self, struct Node *x);
	struct Node *(*search)(struct Sentinel *self, int pos);

	void (*push)(struct Sentinel *self, struct Node *t);
	int (*pop)(struct Sentinel *self);

	void (*enqueue)(struct Sentinel *self, struct Node *t);
	int (*dequeue)(struct Sentinel *self);
};

struct Sentinel *init();
struct Node *node_list(int);
struct Node *node_stack(int);
struct Node *node_queue(int);

void *ec_malloc(unsigned int);
void free_struct(struct Sentinel *sentinel);

void insert(struct Sentinel *self, struct Node *t, struct Node *x);
int del(struct Sentinel *self, struct Node *x);
struct Node *search(struct Sentinel *self, int pos);

void push(struct Sentinel *self, struct Node *t);
int pop(struct Sentinel *self);

void enqueue(struct Sentinel *self, struct Node *t);
int dequeue(struct Sentinel *self);

int main()
{
	int n;
	char opt[10];
	int value;
	char caso = 1;
	char loop = 1;

	struct Sentinel *list = init();
	struct Sentinel *queue = init();
	
	scanf("%d", &n);
	while (caso) {
		caso = 0;
		int i;
		for (i = 0; i < n; ++i) {
			scanf("%d", &value);
			list->insert(list, node_list(value), list->tail);
		}
		loop = 1;
		getchar();
		struct Node *t;
		while (loop == 1) {
			if (scanf("%s", opt) == EOF) {
				loop = 0;
			} else if (opt[0] > 59) {
				scanf ("%d", &value);
				switch (opt[0]) {
					case 'A':
						queue->enqueue(queue, node_queue(value));
						printf("%d %d\n", queue->length, queue->weight);
						break;
					case 'L':
						t = list->search(list, value);
						while (queue->head->next != NULL && queue->head->next->element + t->storage->weight <= t->element && queue->length > 0)
							t->storage->push(t->storage, node_stack(queue->dequeue(queue)));
						printf("%d %d\n", value, t->storage->length);
						break;
					case 'D':
						t = list->search(list, value);
						if (t != NULL && t->storage->length != 0)
							t->storage->pop(t->storage);
						printf("%d %d\n", value, t->storage->length);
						break;
					case 'I':
						t = list->search(list, value);
						if (t != NULL)
							printf("%d %d %d\n", value, t->storage->length, t->storage->weight);
						break;
				}
				getchar();
			} else {
				loop = 0;
				n = atoi(opt);
				caso++;
				printf("\n");
			}
		}
		while(list->length > 0) list->del(list, list->head);
		while(queue->length > 0) queue->dequeue(queue);
	}
	free_struct(list);
	free_struct(queue);
	return 0;
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (ptr == NULL) 
		exit(-1);
	return ptr;
}

void free_struct(struct Sentinel *sentinel)
{
	free(sentinel->head);
	free(sentinel->tail);
	free(sentinel);
}

struct Sentinel *init()
{
	struct Sentinel *t = (struct Sentinel *) ec_malloc(sizeof(struct Sentinel));
	t->head = (struct Node *) ec_malloc(sizeof(struct Node));
	t->tail = (struct Node *) ec_malloc(sizeof(struct Node));
	t->head->next = t->tail->next = NULL;
	t->length = 0;
	t->weight = 0;

	t->insert = insert;
	t->del = del;
	t->search = search;
	t->push = push;
	t->pop = pop;
	t->enqueue = enqueue;
	t->dequeue = dequeue;

	return t;
}

struct Node *node_list(int element)
{
	struct Node *t = (struct Node *) ec_malloc(sizeof(struct Node));
	t->element = element;
	t->storage = init();
	t->next = NULL;

	return t;
}

struct Node *node_stack(int element)
{
	struct Node *t = (struct Node *) ec_malloc(sizeof(struct Node));
	t->element = element;
	t->storage = NULL;
	t->next = NULL;

	return t;
}

struct Node *node_queue(int element)
{
	return node_stack(element);
}

void insert(struct Sentinel *self, struct Node *t, struct Node *x)
{
	if (self->head->next == NULL)
		self->head->next = self->tail->next = t;
	else if (x == self->tail) {
		self->tail->next->next = t;
		self->tail->next = t;
	} else {
		t->next = x->next;
		x->next = t;
	}

	self->length++;
	self->weight += t->element;
}

int del(struct Sentinel *self, struct Node *x)
{
	struct Node *t;
	if (self->head->next == NULL || x->next == NULL)
		return 0;
	else {
		t = x->next;
		if (t->next == NULL) {
			self->tail->next = x;
			x->next = NULL;
		} else {
			x->next = t->next;
		}
		self->length--;
		self->weight -= t->element;
	}
	int value = t->element;
	if (t->storage != NULL)
		while (t->storage->length > 0) t->storage->pop(t->storage);
	free(t);
	return value;
}

struct Node *search(struct Sentinel *self, int pos)
{
	int i = 0;
	struct Node *cur = self->head->next;
	if (cur == NULL)
		return NULL;
	while (i != pos && cur->next != NULL) {
		cur = cur->next;
		i++;
	}
	if (i == pos)
		return cur;
	else
		return NULL;
}

void push(struct Sentinel *self, struct Node *t)
{
	self->insert(self, t, self->head);
}

int pop(struct Sentinel *self)
{
	return self->del(self, self->head);
}

void enqueue(struct Sentinel *self, struct Node *t)
{
	self->insert(self, t, self->tail);
}

int dequeue(struct Sentinel *self)
{
	return self->del(self, self->head);
}
Raw
 transportadora03.c
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int element;
	struct Node *next;
};

struct Cam {
	int max;
	int cur;
};

struct Sentinel {
	struct Node *head;
	struct Node *tail;
	int length;
	int weight;

	void (*insert)(struct Sentinel *self, struct Node *t, struct Node *x);
	int (*del)(struct Sentinel *self, struct Node *x);
	struct Node *(*search)(struct Sentinel *self, int pos);

	void (*push)(struct Sentinel *self, struct Node *t);
	int (*pop)(struct Sentinel *self);

	void (*enqueue)(struct Sentinel *self, struct Node *t);
	int (*dequeue)(struct Sentinel *self);
};

struct Sentinel *init();
struct Node *node_stack(int);
struct Node *node_queue(int);

void *ec_malloc(unsigned int);
void free_struct(struct Sentinel *sentinel);

void insert(struct Sentinel *self, struct Node *t, struct Node *x);
int del(struct Sentinel *self, struct Node *x);
struct Node *search(struct Sentinel *self, int pos);

void push(struct Sentinel *self, struct Node *t);
int pop(struct Sentinel *self);

void enqueue(struct Sentinel *self, struct Node *t);
int dequeue(struct Sentinel *self);

int main()
{
	int n, i;
	char opt[10];
	int value;
	char caso = 1;
	char loop = 1;

	struct Sentinel *queue = init();

	scanf("%d", &n);
	while (caso) {
		caso = 0;
		struct Cam *list = (struct Cam *) ec_malloc(sizeof(struct Cam) * n);
		struct Sentinel *stack = (struct Sentinel *) ec_malloc(sizeof(struct Sentinel) * n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &value);
			list[i].max = value;
			list[i].cur = 0;
			stack[i].head = (struct Node *) ec_malloc(sizeof(struct Node));
			stack[i].tail = (struct Node *) ec_malloc(sizeof(struct Node));
			stack[i].head->next = stack[i].tail->next = NULL;
			stack[i].length = 0;
			stack[i].weight = 0;

			stack[i].insert = insert;
			stack[i].del = del;
			stack[i].search = search;
			stack[i].push = push;
			stack[i].pop = pop;
			stack[i].enqueue = enqueue;
			stack[i].dequeue = dequeue;

		}
		loop = 1;
		getchar();
		while (loop == 1) {
			if (scanf("%s", opt) == EOF) {
				loop = 0;
			} else if (opt[0] > 59) {
				scanf ("%d", &value);
				switch (opt[0]) {
					case 'A':
						queue->enqueue(queue, node_queue(value));
						printf("%d %d\n", queue->length, queue->weight);
						break;
					case 'L':
						while (queue->head->next != NULL && queue->head->next->element + stack[value].weight <= list[value].max && queue->length > 0)
							stack[value].push(&stack[value], node_stack(queue->dequeue(queue)));
						printf("%d %d\n", value, stack[value].length);
						break;
					case 'D':
						if (stack[value].length != 0)
							stack[value].pop(&stack[value]);
						printf("%d %d\n", value, stack[value].length);
						break;
					case 'I':
						printf("%d %d %d\n", value, stack[value].length, stack[value].weight);
						break;
				}
				getchar();
			} else {
				loop = 0;
				for (i = 0; i < n; i++) {
					while (stack[i].length != 0) stack[i].pop(&stack[i]);
					free(stack[i].head);
					free(stack[i].tail);
				}
				n = atoi(opt);
				caso++;
				printf("\n");
			}
		}
		free(list);	
		free(stack);
		while(queue->length > 0) queue->dequeue(queue);
	}
	free_struct(queue);
	return 0;
}

void *ec_malloc(unsigned int size)
{
	void *ptr = malloc(size);
	if (ptr == NULL) 
		exit(-1);
	return ptr;
}

void free_struct(struct Sentinel *sentinel)
{
	free(sentinel->head);
	free(sentinel->tail);
	free(sentinel);
}

struct Sentinel *init()
{
	struct Sentinel *t = (struct Sentinel *) ec_malloc(sizeof(struct Sentinel));
	t->head = (struct Node *) ec_malloc(sizeof(struct Node));
	t->tail = (struct Node *) ec_malloc(sizeof(struct Node));
	t->head->next = t->tail->next = NULL;
	t->length = 0;
	t->weight = 0;

	t->insert = insert;
	t->del = del;
	t->search = search;
	t->push = push;
	t->pop = pop;
	t->enqueue = enqueue;
	t->dequeue = dequeue;

	return t;
}

struct Node *node_stack(int element)
{
	struct Node *t = (struct Node *) ec_malloc(sizeof(struct Node));
	t->element = element;
	t->next = NULL;

	return t;
}

struct Node *node_queue(int element)
{
	return node_stack(element);
}

void insert(struct Sentinel *self, struct Node *t, struct Node *x)
{
	if (self->head->next == NULL)
		self->head->next = self->tail->next = t;
	else if (x == self->tail) {
		self->tail->next->next = t;
		self->tail->next = t;
	} else {
		t->next = x->next;
		x->next = t;
	}

	self->length++;
	self->weight += t->element;
}

int del(struct Sentinel *self, struct Node *x)
{
	struct Node *t;
	if (self->head->next == NULL || x->next == NULL)
		return 0;
	else {
		t = x->next;
		if (t->next == NULL) {
			self->tail->next = x;
			x->next = NULL;
		} else {
			x->next = t->next;
		}
		self->length--;
		self->weight -= t->element;
	}
	int value = t->element;
	free(t);
	return value;
}

struct Node *search(struct Sentinel *self, int pos)
{
	int i = 0;
	struct Node *cur = self->head->next;
	if (cur == NULL)
		return NULL;
	while (i != pos && cur->next != NULL) {
		cur = cur->next;
		i++;
	}
	if (i == pos)
		return cur;
	else
		return NULL;
}

void push(struct Sentinel *self, struct Node *t)
{
	self->insert(self, t, self->head);
}

int pop(struct Sentinel *self)
{
	return self->del(self, self->head);
}

void enqueue(struct Sentinel *self, struct Node *t)
{
	self->insert(self, t, self->tail);
}

int dequeue(struct Sentinel *self)
{
	return self->del(self, self->head);
}
