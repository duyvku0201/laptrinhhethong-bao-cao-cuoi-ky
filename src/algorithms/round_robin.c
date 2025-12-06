/**
 * @file round_robin.c
 * @brief Round Robin (RR) scheduling algorithm implementation
 * @author Team CPU Scheduling
 * 
 * Round Robin là thuật toán lập lịch có ưu tiên (preemptive) với time quantum cố định.
 * Mỗi process được cấp CPU trong một khoảng thời gian time_quantum.
 * Nếu process chưa hoàn thành sau quantum, nó được đưa về cuối hàng đợi.
 * 
 * Độ phức tạp: O(n × T / TQ) với T = tổng thời gian, TQ = time quantum
 */

#include "algorithms.h"
#include "process.h"
#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Thuật toán Round Robin
 * @param processes Mảng các process
 * @param n Số lượng process
 * @param time_quantum Khoảng thời gian CPU cấp cho mỗi process (TQ)
 * 
 * Thuật toán:
 * 1. Khởi tạo queue rỗng và current_time = 0
 * 2. Thêm tất cả process có arrival_time = 0 vào queue
 * 3. Lặp cho đến khi tất cả process hoàn thành:
 *    a. Lấy process từ đầu queue
 *    b. Chạy process trong thời gian min(remaining_time, time_quantum)
 *    c. Cập nhật thời gian
 *    d. Thêm các process mới đến vào queue
 *    e. Nếu process chưa xong, đưa về cuối queue
 * 4. Tính toán các metrics (WT, TAT, RT)
 */
void round_robin(Process processes[], int n, int time_quantum) {
    if (!processes || n <= 0 || time_quantum <= 0) {
        printf("Error: Invalid input parameters\n");
        return;
    }

    // Khởi tạo
    Queue ready_queue;
    queue_init(&ready_queue);
    
    int current_time = 0;
    int completed = 0;
    bool in_queue[MAX_PROCESSES] = {false}; // Đánh dấu process đã vào queue chưa
    
    // Khởi tạo remaining time và đánh dấu chưa hoàn thành
    for (int i = 0; i < n; i++) {
        processes[i].RemainingTime = processes[i].BurstTime;
        processes[i].IsCompleted = false;
        processes[i].StartTime = -1; // Chưa bắt đầu
        processes[i].ResponseTime = -1;
    }
    
    // Thêm các process có arrival time = 0 vào queue
    for (int i = 0; i < n; i++) {
        if (processes[i].ArrivalTime == 0) {
            enqueue(&ready_queue, i);
            in_queue[i] = true;
        }
    }
    
    // Nếu không có process nào tại thời điểm 0, tìm process đến sớm nhất
    if (queue_is_empty(&ready_queue)) {
        int earliest = 0;
        for (int i = 1; i < n; i++) {
            if (processes[i].ArrivalTime < processes[earliest].ArrivalTime) {
                earliest = i;
            }
        }
        current_time = processes[earliest].ArrivalTime;
        enqueue(&ready_queue, earliest);
        in_queue[earliest] = true;
    }
    
    // Main Round Robin loop
    while (completed < n) {
        if (queue_is_empty(&ready_queue)) {
            // Nếu queue rỗng, tìm process tiếp theo sẽ đến
            int next = -1;
            int min_arrival = __INT_MAX__;
            for (int i = 0; i < n; i++) {
                if (!processes[i].IsCompleted && 
                    processes[i].ArrivalTime > current_time &&
                    processes[i].ArrivalTime < min_arrival) {
                    min_arrival = processes[i].ArrivalTime;
                    next = i;
                }
            }
            
            if (next != -1) {
                current_time = processes[next].ArrivalTime;
                enqueue(&ready_queue, next);
                in_queue[next] = true;
            } else {
                break; // Không còn process nào
            }
        }
        
        // Lấy process từ đầu queue
        int current_process = dequeue(&ready_queue);
        
        if (current_process == -1) {
            break; // Queue rỗng
        }
        
        // Ghi nhận thời điểm bắt đầu (lần đầu tiên process được CPU)
        if (processes[current_process].StartTime == -1) {
            processes[current_process].StartTime = current_time;
            processes[current_process].ResponseTime = 
                current_time - processes[current_process].ArrivalTime;
        }
        
        // Tính thời gian chạy trong lượt này
        int execution_time = (processes[current_process].RemainingTime < time_quantum) 
                            ? processes[current_process].RemainingTime 
                            : time_quantum;
        
        // Chạy process
        processes[current_process].RemainingTime -= execution_time;
        current_time += execution_time;
        
        // Thêm các process mới đến vào queue (trong khoảng vừa chạy)
        for (int i = 0; i < n; i++) {
            if (!processes[i].IsCompleted && 
                !in_queue[i] &&
                processes[i].ArrivalTime <= current_time &&
                i != current_process) {
                enqueue(&ready_queue, i);
                in_queue[i] = true;
            }
        }
        
        // Kiểm tra process hiện tại đã xong chưa
        if (processes[current_process].RemainingTime == 0) {
            // Process hoàn thành
            processes[current_process].IsCompleted = true;
            processes[current_process].CompletionTime = current_time;
            processes[current_process].TurnaroundTime = 
                processes[current_process].CompletionTime - 
                processes[current_process].ArrivalTime;
            processes[current_process].WaitingTime = 
                processes[current_process].TurnaroundTime - 
                processes[current_process].BurstTime;
            completed++;
        } else {
            // Process chưa xong, đưa về cuối queue
            enqueue(&ready_queue, current_process);
        }
    }
    
    // In kết quả (có thể comment lại nếu không cần)
    printf("\n=== Round Robin (Time Quantum = %d) ===\n", time_quantum);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].ProcessId,
               processes[i].ArrivalTime,
               processes[i].BurstTime,
               processes[i].CompletionTime,
               processes[i].TurnaroundTime,
               processes[i].WaitingTime,
               processes[i].ResponseTime);
    }
    
    // Tính trung bình
    float avg_tat = 0, avg_wt = 0, avg_rt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += processes[i].TurnaroundTime;
        avg_wt += processes[i].WaitingTime;
        avg_rt += processes[i].ResponseTime;
    }
    avg_tat /= n;
    avg_wt /= n;
    avg_rt /= n;
    
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Response Time: %.2f\n", avg_rt);
}
