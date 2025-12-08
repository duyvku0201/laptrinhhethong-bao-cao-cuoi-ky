/**
 * @file priority_np.c
 * @brief Priority Scheduling (Non-Preemptive)
 * Non-preemptive: Chọn process có priority cao nhất (số nhỏ nhất)
 */
#include "algorithms.h"
#include "metrics.h"
#include <limits.h>

void priority_non_preemptive(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    // Khởi tạo
    for (int i = 0; i < n; i++) {
        processes[i].IsCompleted = false;
    }

    while (completed < n) {
        int highest_idx = -1;
        int highest_priority = INT_MAX;

        // Tìm process có priority cao nhất (số nhỏ nhất) đã đến
        for (int i = 0; i < n; i++) {
            if (processes[i].ArrivalTime <= current_time && !processes[i].IsCompleted) {
                if (processes[i].Priority < highest_priority ||
                    (processes[i].Priority == highest_priority && 
                     processes[i].ArrivalTime < processes[highest_idx].ArrivalTime)) {
                    highest_priority = processes[i].Priority;
                    highest_idx = i;
                }
            }
        }

        if (highest_idx == -1) {
            current_time++;
            continue;
        }

        processes[highest_idx].StartTime = current_time;
        current_time += processes[highest_idx].BurstTime;
        processes[highest_idx].CompletionTime = current_time;
        processes[highest_idx].IsCompleted = true;
        completed++;
    }

    CalculateAllMetrics(processes, n);
}