/**
 * @file sjf.c
 * @brief SJF (Shortest Job First) Scheduling Algorithm
 * Non-preemptive: Chọn process có burst time nhỏ nhất
 */
#include "algorithms.h"
#include "metrics.h"
#include <limits.h>

void sjf(Process processes[], int n) {
    // Reset timeline
    reset_timeline();
    
    int current_time = 0;
    int completed = 0;

    // Khởi tạo
    for (int i = 0; i < n; i++) {
        processes[i].IsCompleted = false;
        processes[i].StartTime = -1;
    }

    while (completed < n) {
        int shortest_idx = -1;
        int min_burst = INT_MAX;

        // Tìm process có burst time nhỏ nhất đã đến
        for (int i = 0; i < n; i++) {
            if (processes[i].ArrivalTime <= current_time && !processes[i].IsCompleted) {
                if (processes[i].BurstTime < min_burst ||
                    (processes[i].BurstTime == min_burst && 
                     processes[i].ArrivalTime < processes[shortest_idx].ArrivalTime)) {
                    min_burst = processes[i].BurstTime;
                    shortest_idx = i;
                }
            }
        }

        if (shortest_idx == -1) {
            current_time++;
            continue;
        }

        processes[shortest_idx].StartTime = current_time;
        int start = current_time;
        current_time += processes[shortest_idx].BurstTime;
        processes[shortest_idx].CompletionTime = current_time;
        processes[shortest_idx].IsCompleted = true;
        completed++;
        
        // Add to timeline
        add_timeline_entry(processes[shortest_idx].ProcessId, start, current_time);
    }

    CalculateAllMetrics(processes, n);
}