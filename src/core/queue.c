/**
 * @file queue.c
 * @brief Queue implementation for Round Robin algorithm
 * @author Team CPU Scheduling
 */

#include "process.h"
#include <stdio.h>
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

/**
 * @brief Khởi tạo queue rỗng
 * @param q Con trỏ tới queue cần khởi tạo
 */
void queue_init(Queue *q) {
    if (q) {
        q->front = 0;
        q->rear = -1;
        q->size = 0;
    }
}

/**
 * @brief Kiểm tra queue có rỗng không
 * @param q Con trỏ tới queue
 * @return true nếu queue rỗng, false nếu không
 */
bool queue_is_empty(Queue *q) {
    return (q && q->size == 0);
}

/**
 * @brief Kiểm tra queue có đầy không
 * @param q Con trỏ tới queue
 * @return true nếu queue đầy, false nếu không
 */
bool queue_is_full(Queue *q) {
    return (q && q->size >= MAX_QUEUE_SIZE);
}

/**
 * @brief Thêm một phần tử vào cuối queue
 * @param q Con trỏ tới queue
 * @param process_index Index của process cần thêm vào
 * @return true nếu thêm thành công, false nếu queue đầy
 */
bool enqueue(Queue *q, int process_index) {
    if (!q || queue_is_full(q)) {
        return false;
    }
    
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->items[q->rear] = process_index;
    q->size++;
    return true;
}

/**
 * @brief Lấy phần tử từ đầu queue và xóa nó khỏi queue
 * @param q Con trỏ tới queue
 * @return Index của process, hoặc -1 nếu queue rỗng
 */
int dequeue(Queue *q) {
    if (!q || queue_is_empty(q)) {
        return -1;
    }
    
    int item = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return item;
}

/**
 * @brief Xem phần tử đầu queue mà không xóa nó
 * @param q Con trỏ tới queue
 * @return Index của process ở đầu queue, hoặc -1 nếu queue rỗng
 */
int queue_peek(Queue *q) {
    if (!q || queue_is_empty(q)) {
        return -1;
    }
    return q->items[q->front];
}

/**
 * @brief Kiểm tra xem một process có trong queue không
 * @param q Con trỏ tới queue
 * @param process_index Index của process cần kiểm tra
 * @return true nếu process có trong queue, false nếu không
 */
bool queue_contains(Queue *q, int process_index) {
    if (!q || queue_is_empty(q)) {
        return false;
    }
    
    int current = q->front;
    for (int i = 0; i < q->size; i++) {
        if (q->items[current] == process_index) {
            return true;
        }
        current = (current + 1) % MAX_QUEUE_SIZE;
    }
    return false;
}
