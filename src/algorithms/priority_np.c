#include "../../include/algorithms.h"
#include "../../include/utils.h"
#include "../../include/metrics.h"
#include "../../include/display.h"
#include <stdio.h>

void priority_non_preemptive(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int is_completed[100] = { 0 };

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (processes[i].ArrivalTime <= current_time && !is_completed[i]) {
                if (processes[i].Priority < highest_priority) {
                    highest_priority = processes[i].Priority;
                    idx = i;
                }
                else if (processes[i].Priority == highest_priority) {
                    if (processes[i].ArrivalTime < processes[idx].ArrivalTime) idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].StartTime = current_time;
            log_gantt_event(processes[idx].ProcessId, current_time, current_time + processes[idx].BurstTime);

            current_time += processes[idx].BurstTime;
            processes[idx].CompletionTime = current_time;
            processes[idx].IsCompleted = true;
            is_completed[idx] = 1;
            completed++;
        }
        else {
            current_time++;
        }
    }
    CalculateAllMetrics(processes, n);
}