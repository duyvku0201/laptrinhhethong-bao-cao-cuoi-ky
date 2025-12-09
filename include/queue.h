#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

void queue_init(Queue* q);
bool queue_is_empty(Queue* q);
bool queue_is_full(Queue* q);
bool enqueue(Queue* q, int process_index);
int dequeue(Queue* q);
int queue_peek(Queue* q);
bool queue_contains(Queue* q, int process_index);

#endif // QUEUE_H