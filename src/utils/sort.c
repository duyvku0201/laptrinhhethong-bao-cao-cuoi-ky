#include "../../include/utils.h"
#include "../../include/process.h"
#include <stdio.h>

void sort_by_arrival(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // PascalCase: ArrivalTime
            if (processes[j].ArrivalTime > processes[j + 1].ArrivalTime) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sort_by_priority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // PascalCase: Priority
            if (processes[j].Priority > processes[j + 1].Priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
            // Nếu priority bằng nhau thì xét ArrivalTime
            else if (processes[j].Priority == processes[j + 1].Priority) {
                if (processes[j].ArrivalTime > processes[j + 1].ArrivalTime) {
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }
}

void sort_by_pid(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // PascalCase: ProcessId
            if (processes[j].ProcessId > processes[j + 1].ProcessId) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}