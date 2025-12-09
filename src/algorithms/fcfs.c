/**
 * @file fcfs.c
 * @brief FCFS (First-Come First-Served) Scheduling Algorithm
 * Non-preemptive: Process đến trước phục vụ trước, không ngắt
 */
#include "algorithms.h"
#include "utils.h"
#include "metrics.h"

void fcfs(Process processes[], int n) {
    // Reset timeline
    reset_timeline();
    
    sort_by_arrival(processes, n);
    
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        // CPU idle nếu process chưa đến
        if (current_time < processes[i].ArrivalTime) {
            current_time = processes[i].ArrivalTime;
        }
        
        processes[i].StartTime = current_time;
        int start = current_time;
        current_time += processes[i].BurstTime;
        processes[i].CompletionTime = current_time;
        processes[i].IsCompleted = true;
        
        // Add to timeline
        add_timeline_entry(processes[i].ProcessId, start, current_time);
    }
    
    CalculateAllMetrics(processes, n);
}