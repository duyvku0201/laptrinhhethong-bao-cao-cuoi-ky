#define _CRT_SECURE_NO_WARNINGS
#include "io.h"
#include <stdio.h>

// In header của bảng
static void PrintTableHeader(void) {
    printf("Process | Arrival | Burst | Waiting | Turnaround | Response\n");
    printf("--------|---------|-------|---------|------------|----------\n");
}

// In một process
static void PrintSingleProcess(const Process* P) {
    printf("%-7s | %7d | %5d | %7d | %10d | %8d\n",
        P->ProcessId, P->ArrivalTime, P->BurstTime,
        P->WaitingTime, P->TurnaroundTime, P->ResponseTime);
}

// In tất cả processes
static void PrintAllProcesses(const Process* Processes, int ProcessCount) {
    for (int i = 0; i < ProcessCount; i++) {
        PrintSingleProcess(&Processes[i]);
    }
}

// In metrics
static void PrintMetrics(float AvgWaitingTime, float AvgTurnaroundTime) {
    printf("\nAverage Waiting Time: %.2f\n", AvgWaitingTime);
    printf("Average Turnaround Time: %.2f\n\n", AvgTurnaroundTime);
}

// Hiển thị kết quả scheduling (sử dụng extract functions)
void DisplayResults(const char* AlgorithmName, Process* Processes,
    int ProcessCount, float AvgWaitingTime, float AvgTurnaroundTime) {
    printf("\n=== %s Scheduling Results ===\n\n", AlgorithmName);

    PrintTableHeader();
    PrintAllProcesses(Processes, ProcessCount);
    PrintMetrics(AvgWaitingTime, AvgTurnaroundTime);
}