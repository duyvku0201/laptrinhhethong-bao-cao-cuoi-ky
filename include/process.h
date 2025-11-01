#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_PROCESS_ID_LENGTH 20

// Cấu trúc lưu thông tin process
typedef struct {
    char ProcessId[MAX_PROCESS_ID_LENGTH];
    int ArrivalTime;
    int BurstTime;
    int Priority;
    int RemainingTime;
    int WaitingTime;
    int TurnaroundTime;
    int ResponseTime;
    int CompletionTime;
    bool IsCompleted;
} Process;

#endif#pragma once
