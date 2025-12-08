/**
 * @file srtf.c
 * @brief SRTF (Shortest Remaining Time First) Scheduling Algorithm
 * Preemptive: Chọn process có remaining time nhỏ nhất, có ngắt
 */
#include "algorithms.h"
#include "metrics.h"
#include <limits.h>

void srtf(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    // Khởi tạo
    for (int i = 0; i < n; i++) {
        processes[i].RemainingTime = processes[i].BurstTime;
        processes[i].IsCompleted = false;
        processes[i].StartTime = -1;
    }

    while (completed < n) {
        int shortest_idx = -1;
        int min_remaining = INT_MAX;

        // Tìm process có remaining time nhỏ nhất đã đến
        for (int i = 0; i < n; i++) {
            if (processes[i].ArrivalTime <= current_time && 
                !processes[i].IsCompleted &&
                processes[i].RemainingTime < min_remaining) {
                min_remaining = processes[i].RemainingTime;
                shortest_idx = i;
            }
        }

        if (shortest_idx == -1) {
            current_time++;
            continue;
        }

        // Ghi nhận lần đầu chạy
        if (processes[shortest_idx].StartTime == -1) {
            processes[shortest_idx].StartTime = current_time;
        }

        // Thực thi 1 đơn vị thời gian
        processes[shortest_idx].RemainingTime--;
        current_time++;

        // Process hoàn thành
        if (processes[shortest_idx].RemainingTime == 0) {
            processes[shortest_idx].CompletionTime = current_time;
            processes[shortest_idx].IsCompleted = true;
            completed++;
        }
    }

    CalculateAllMetrics(processes, n);
}