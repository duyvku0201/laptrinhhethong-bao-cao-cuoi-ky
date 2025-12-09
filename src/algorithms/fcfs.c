#include "../../include/algorithms.h"
#include "../../include/utils.h"
#include "../../include/metrics.h"
#include "../../include/display.h"
#include <stdio.h>

void fcfs(Process processes[], int n) {
    sort_by_arrival(processes, n);
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].ArrivalTime) current_time = processes[i].ArrivalTime;
        processes[i].StartTime = current_time;

        log_gantt_event(processes[i].ProcessId, current_time, current_time + processes[i].BurstTime);

        current_time += processes[i].BurstTime;
        processes[i].CompletionTime = current_time;
        processes[i].IsCompleted = true;
    }
    CalculateAllMetrics(processes, n);
}