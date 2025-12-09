#include "../../include/algorithms.h"
#include "../../include/process.h"
#include "../../include/queue.h"
#include "../../include/metrics.h"
#include "../../include/display.h"
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void round_robin(Process processes[], int n, int time_quantum) {
    if (!processes || n <= 0) return;
    Queue ready_queue;
    queue_init(&ready_queue);
    int current_time = 0;
    int completed = 0;
    bool in_queue[MAX_PROCESSES] = { false };

    for (int i = 0; i < n; i++) {
        processes[i].RemainingTime = processes[i].BurstTime;
        processes[i].IsCompleted = false;
        processes[i].StartTime = -1;
    }

    // Add processes at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].ArrivalTime == 0) {
            enqueue(&ready_queue, i);
            in_queue[i] = true;
        }
    }
    if (queue_is_empty(&ready_queue)) {
        int earliest = 0;
        int min_at = INT_MAX;
        for (int i = 0; i < n; i++) if (processes[i].ArrivalTime < min_at) { min_at = processes[i].ArrivalTime; earliest = i; }
        current_time = min_at;
        enqueue(&ready_queue, earliest);
        in_queue[earliest] = true;
    }

    while (completed < n) {
        if (queue_is_empty(&ready_queue)) {
            int next = -1, min_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!processes[i].IsCompleted && processes[i].ArrivalTime > current_time && processes[i].ArrivalTime < min_arrival) {
                    min_arrival = processes[i].ArrivalTime;
                    next = i;
                }
            }
            if (next != -1) {
                current_time = processes[next].ArrivalTime;
                enqueue(&ready_queue, next);
                in_queue[next] = true;
            }
            else break;
        }

        int curr = dequeue(&ready_queue);
        if (curr == -1) break;

        if (processes[curr].StartTime == -1) processes[curr].StartTime = current_time;

        int exec = (processes[curr].RemainingTime < time_quantum) ? processes[curr].RemainingTime : time_quantum;
        log_gantt_event(processes[curr].ProcessId, current_time, current_time + exec);

        processes[curr].RemainingTime -= exec;
        current_time += exec;

        for (int i = 0; i < n; i++) {
            if (!processes[i].IsCompleted && !in_queue[i] && processes[i].ArrivalTime <= current_time && i != curr) {
                enqueue(&ready_queue, i);
                in_queue[i] = true;
            }
        }

        if (processes[curr].RemainingTime == 0) {
            processes[curr].IsCompleted = true;
            processes[curr].CompletionTime = current_time;
            completed++;
        }
        else {
            enqueue(&ready_queue, curr);
        }
    }
    CalculateAllMetrics(processes, n);
}