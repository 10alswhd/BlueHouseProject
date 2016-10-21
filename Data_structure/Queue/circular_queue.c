#include <stdio.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 15
#define ITEM_LENGTH 32

typedef char queue_element_t [ITEM_LENGTH];

typedef struct circular_queue_t {
	int front;
	int rear;
	int count;
	queue_element_t contents[MAX_QUEUE_SIZE];
} circular_queue_t;

void queue_init(circular_queue_t * queue) {
	int i, k;
	queue->front = 0;
	queue->rear = 0;
	queue->count = 0;
	for(i = 0; i < MAX_QUEUE_SIZE; ++i) {
		queue->contents[i][0] = '\0';
	}
}

void queue_dump(circular_queue_t * queue) {
	int front, count;
	front = queue->front;
	count = queue->count;
	while (count > 0) {
		printf("Element #%3d = %s\n", front, queue->contents[front]);
		front = (front + 1) % MAX_QUEUE_SIZE;
		count--;
	}
	return;
}

bool queue_has_contents(circular_queue_t * queue) {
	return (queue->count > 0);
}

bool queue_is_empty(circular_queue_t * queue) {
	return (queue->count == 0);
}

void queue_advance(circular_queue_t * queue) {
	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
}

int queue_enqueue(circular_queue_t * queue, queue_element_t value) {
	if (queue->count < MAX_QUEUE_SIZE) {
		int i;
		queue->count++;
		for (i = 0; i < ITEM_LENGTH; ++i) {
			queue->contents[queue->rear][i] = value[i];
		}
		queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	} else {
		printf("No space in the queue!\n");
	}
	return -1;
}

int queue_dequeue(circular_queue_t * queue, queue_element_t value) {
	if (!queue_is_empty(queue)) {
		int i;
		for (i = 0; i < ITEM_LENGTH; ++i) {
			value[i] = queue->contents[queue->front][i];
		}
		queue_advance(queue);
		queue->count--;
		return 0;
	} else {
		return -1;
	}
}

int queue_peek(circular_queue_t * queue, queue_element_t value) {
	if (!queue_is_empty(queue)) {
		int i;
		for (i = 0; i < ITEM_LENGTH; ++i) {
			value[i] = queue->contents[queue->front][i];
		}
		return 0;
	} else {
		return -1;
	}
}

int main(void) {
	circular_queue_t event_queue;

	queue_init(&event_queue);
	queue_element_t a1 = "something amazing";
	queue_element_t a2 = "brap";
	queue_element_t a3 = "monty";
	queue_enqueue(&event_queue, a1);
	queue_enqueue(&event_queue, a1);
	queue_enqueue(&event_queue, a1);
	queue_enqueue(&event_queue, a2);
	queue_enqueue(&event_queue, a3);

	queue_dump(&event_queue);

	queue_element_t b;
	queue_dequeue(&event_queue, b);
	printf("LALA_%s_\n", b);
	queue_dequeue(&event_queue, b);
	printf("LALA_%s_\n", b);
	queue_dequeue(&event_queue, b);
	printf("LALA_%s_\n", b);
	queue_dequeue(&event_queue, b);
	printf("LALA_%s_\n", b);
}
