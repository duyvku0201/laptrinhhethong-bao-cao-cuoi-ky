#include "../../include/algorithms.h"
#include "../../include/process.h"
#include "../../include/metrics.h"
#include "../../include/display.h"
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void priority_preemptive(Process processes[], int n) {
    if (!processes || n <= 0) return;

    int remaining_time[MAX_PROCESSES];
    bool is_completed[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].BurstTime;
        is_completed[i] = false;
        processes[i].StartTime = -1;
    }

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].ArrivalTime <= current_time && !is_completed[i] && remaining_time[i] > 0) {
                if (processes[i].Priority < highest_priority) {
                    highest_priority = processes[i].Priority;
                    idx = i;
                }
                else if (processes[i].Priority == highest_priority) {
                    if (idx == -1 || processes[i].ArrivalTime < processes[idx].ArrivalTime) idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        if (processes[idx].StartTime == -1) processes[idx].StartTime = current_time;

        log_gantt_event(processes[idx].ProcessId, current_time, current_time + 1);

        remaining_time[idx]--;
        current_time++;

        if (remaining_time[idx] == 0) {
            is_completed[idx] = true;
            processes[idx].IsCompleted = true;
            processes[idx].CompletionTime = current_time;
            completed++;
        }
    }
    CalculateAllMetrics(processes, n);
}