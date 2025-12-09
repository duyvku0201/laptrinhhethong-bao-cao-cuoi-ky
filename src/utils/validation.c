#include "../../include/utils.h"
#include "../../include/process.h"
#include <stdio.h>

int check_duplicate_pids(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // PascalCase: ProcessId
            if (processes[i].ProcessId == processes[j].ProcessId) {
                printf("Error: Duplicate PID %d\n", processes[i].ProcessId);
                return 1;
            }
        }
    }
    return 0;
}

int validate_input(Process processes[], int n) {
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Error: Process count must be 1-%d.\n", MAX_PROCESSES);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        // PascalCase hết các thuộc tính
        if (processes[i].ProcessId <= 0) return 0;
        if (processes[i].ArrivalTime < 0) return 0;
        if (processes[i].BurstTime <= 0) return 0;
        if (processes[i].Priority < 0) return 0;
    }
    if (check_duplicate_pids(processes, n)) return 0;
    return 1;
}

int validate_time_quantum(int time_quantum) {
    if (time_quantum <= 0) {
        printf("Error: Time quantum must be > 0.\n");
        return 0;
    }
    return 1;
}

void copy_processes(Process dest[], Process src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}