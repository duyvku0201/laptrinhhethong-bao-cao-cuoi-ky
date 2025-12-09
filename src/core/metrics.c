#include "../../include/metrics.h"
#include <stdio.h>
#include <stdbool.h>

void CalculateWaitingTime(Process* ProcessData) {
    if (ProcessData == NULL) return;
    ProcessData->WaitingTime = ProcessData->TurnaroundTime - ProcessData->BurstTime;
}

void CalculateTurnaroundTime(Process* ProcessData) {
    if (ProcessData == NULL) return;
    ProcessData->TurnaroundTime = ProcessData->CompletionTime - ProcessData->ArrivalTime;
}

void CalculateResponseTime(Process* ProcessData, int FirstResponseTime) {
    if (ProcessData == NULL) return;
    ProcessData->ResponseTime = FirstResponseTime - ProcessData->ArrivalTime;
}

float CalculateAverageWaitingTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) return 0.0f;
    float TotalWaitingTime = 0.0f;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalWaitingTime += Processes[Index].WaitingTime;
    }
    return TotalWaitingTime / ProcessCount;
}

float CalculateAverageTurnaroundTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) return 0.0f;
    float TotalTurnaroundTime = 0.0f;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalTurnaroundTime += Processes[Index].TurnaroundTime;
    }
    return TotalTurnaroundTime / ProcessCount;
}

float CalculateAverageResponseTime(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) return 0.0f;
    float TotalResponseTime = 0.0f;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalResponseTime += Processes[Index].ResponseTime;
    }
    return TotalResponseTime / ProcessCount;
}

void CalculateProcessMetrics(Process* ProcessData, int FirstResponseTime) {
    if (ProcessData == NULL) return;
    CalculateTurnaroundTime(ProcessData);
    CalculateWaitingTime(ProcessData);
    CalculateResponseTime(ProcessData, FirstResponseTime);
}

void CalculateAllMetrics(Process* Processes, int ProcessCount) {
    if (Processes == NULL || ProcessCount <= 0) return;
    for (int Index = 0; Index < ProcessCount; Index++) {
        CalculateProcessMetrics(&Processes[Index], Processes[Index].StartTime);
    }
}

float CalculateCpuUtilization(Process* Processes, int ProcessCount, int TotalTime) {
    if (Processes == NULL || ProcessCount <= 0 || TotalTime <= 0) return 0.0f;
    int TotalBurstTime = 0;
    for (int Index = 0; Index < ProcessCount; Index++) {
        TotalBurstTime += Processes[Index].BurstTime;
    }
    // Đã sửa lỗi "100. 0f" thành "100.0f"
    return ((float)TotalBurstTime / TotalTime) * 100.0f;
}

float CalculateThroughput(int ProcessCount, int TotalTime) {
    if (ProcessCount <= 0 || TotalTime <= 0) return 0.0f;
    return (float)ProcessCount / TotalTime;
}


bool ValidateMetrics(Process* ProcessData) {
    if (ProcessData == NULL) return false;
    if (ProcessData->WaitingTime < 0 || ProcessData->TurnaroundTime < 0 || ProcessData->ResponseTime < 0) return false;
    return true;
}