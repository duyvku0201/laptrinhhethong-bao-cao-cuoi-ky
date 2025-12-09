/**
 * @file priority_p.c
 * @brief Priority Scheduling (Preemptive) algorithm implementation
 * @author Team CPU Scheduling
 * 
 * Priority Preemptive là thuật toán lập lịch có ưu tiên (preemptive).
 * CPU luôn chọn process có độ ưu tiên cao nhất (số nhỏ nhất = ưu tiên cao nhất).
 * Nếu có process mới đến với độ ưu tiên cao hơn, process đang chạy sẽ bị ngắt.
 * 
 * Độ phức tạp: O(n × T) với T = tổng thời gian
 */

#include "algorithms.h"
#include "process.h"
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Thuật toán Priority Preemptive
 * @param processes Mảng các process
 * @param n Số lượng process
 * 
 * Thuật toán:
 * 1. Khởi tạo remaining_time[], current_time = 0
 * 2. While chưa hoàn thành hết:
 *    a. Tìm process có highest priority (lowest number) đã đến và chưa xong
 *    b. Execute process đó 1 time unit
 *    c. Giảm remaining_time
 *    d. Kiểm tra completed
 *    e. Cập nhật current_time
 * 3. Tính toán các metrics (WT, TAT, RT)
 */
void priority_preemptive(Process processes[], int n) {
    if (!processes || n <= 0) {
        printf("Error: Invalid input parameters\n");
        return;
    }

    // Reset timeline
    reset_timeline();
    
    // Khởi tạo
    int remaining_time[MAX_PROCESSES];
    bool is_completed[MAX_PROCESSES];
    int start_time[MAX_PROCESSES];
    
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].BurstTime;
        is_completed[i] = false;
        start_time[i] = -1; // Chưa bắt đầu
        processes[i].StartTime = -1;
        processes[i].ResponseTime = -1;
    }
    
    int current_time = 0;
    int completed = 0;
    
    // Main scheduling loop
    while (completed < n) {
        int highest_priority_idx = -1;
        int highest_priority = INT_MAX; // Số nhỏ nhất = ưu tiên cao nhất
        
        // Tìm process có highest priority (lowest priority number) đã đến
        for (int i = 0; i < n; i++) {
            if (processes[i].ArrivalTime <= current_time && 
                !is_completed[i] &&
                remaining_time[i] > 0) {
                
                // So sánh priority (số nhỏ hơn = ưu tiên cao hơn)
                if (processes[i].Priority < highest_priority) {
                    highest_priority = processes[i].Priority;
                    highest_priority_idx = i;
                }
                // Nếu priority bằng nhau, chọn process đến trước (FCFS)
                else if (processes[i].Priority == highest_priority) {
                    if (highest_priority_idx == -1 || 
                        processes[i].ArrivalTime < processes[highest_priority_idx].ArrivalTime) {
                        highest_priority_idx = i;
                    }
                }
            }
        }
        
        // Nếu không tìm thấy process nào sẵn sàng
        if (highest_priority_idx == -1) {
            // Tìm process tiếp theo sẽ đến
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!is_completed[i] && processes[i].ArrivalTime > current_time) {
                    if (processes[i].ArrivalTime < next_arrival) {
                        next_arrival = processes[i].ArrivalTime;
                    }
                }
            }
            
            if (next_arrival == INT_MAX) {
                break; // Không còn process nào
            }
            current_time = next_arrival;
            continue;
        }
        
        // Ghi nhận thời điểm bắt đầu (lần đầu tiên process được CPU)
        if (start_time[highest_priority_idx] == -1) {
            start_time[highest_priority_idx] = current_time;
            processes[highest_priority_idx].StartTime = current_time;
            processes[highest_priority_idx].ResponseTime = 
                current_time - processes[highest_priority_idx].ArrivalTime;
        }
        
        // Execute process trong 1 time unit
        int start = current_time;
        remaining_time[highest_priority_idx]--;
        current_time++;
        
        // Add to timeline (will be merged if same process)
        add_timeline_entry(processes[highest_priority_idx].ProcessId, start, current_time);
        
        // Kiểm tra process có hoàn thành không
        if (remaining_time[highest_priority_idx] == 0) {
            is_completed[highest_priority_idx] = true;
            processes[highest_priority_idx].IsCompleted = true;
            processes[highest_priority_idx].CompletionTime = current_time;
            processes[highest_priority_idx].TurnaroundTime = 
                processes[highest_priority_idx].CompletionTime - 
                processes[highest_priority_idx].ArrivalTime;
            processes[highest_priority_idx].WaitingTime = 
                processes[highest_priority_idx].TurnaroundTime - 
                processes[highest_priority_idx].BurstTime;
            completed++;
        }
    }
}
