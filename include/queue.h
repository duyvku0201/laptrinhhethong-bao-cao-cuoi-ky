#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define MAX_QUEUE_SIZE 100

/**
 * @brief Cấu trúc Queue để lưu chỉ số của các process
 * Sử dụng circular queue để tối ưu
 */
typedef struct {
    int items[MAX_QUEUE_SIZE];  // Mảng lưu index của các process
    int front;                   // Vị trí đầu queue
    int rear;                    // Vị trí cuối queue
    int size;                    // Số lượng phần tử hiện tại
} Queue;

// Queue operations
void queue_init(Queue *q);
bool queue_is_empty(Queue *q);
bool queue_is_full(Queue *q);
bool enqueue(Queue *q, int process_index);
int dequeue(Queue *q);
int queue_peek(Queue *q);
bool queue_contains(Queue *q, int process_index);

#endif // QUEUE_H
