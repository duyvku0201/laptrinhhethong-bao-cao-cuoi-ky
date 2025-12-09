#include "../../include/process.h"
#include "../../include/utils.h" // <--- THÊM DÒNG NÀY ĐỂ SỬA LỖI min_int
#include <stdio.h>
#include <stdlib.h>

void InitProcess(Process* ProcessData) {
    if (!ProcessData) return;
    ProcessData->ProcessId = 0;
    ProcessData->ArrivalTime = 0;
    ProcessData->BurstTime = 0;
    ProcessData->Priority = 0;
    ProcessData->RemainingTime = 0;
    ProcessData->WaitingTime = 0;
    ProcessData->TurnaroundTime = 0;
    ProcessData->ResponseTime = -1;
    ProcessData->CompletionTime = 0;
    ProcessData->StartTime = -1;
    ProcessData->IsCompleted = false;
}

Process CreateProcess(int Id, int Arrival, int Burst, int Priority) {
    Process NewProcess;
    InitProcess(&NewProcess);
    NewProcess.ProcessId = Id;
    NewProcess.ArrivalTime = Arrival;
    NewProcess.BurstTime = Burst;
    NewProcess.Priority = Priority;
    NewProcess.RemainingTime = Burst;
    return NewProcess;
}

void ResetProcess(Process* ProcessData) {
    if (!ProcessData) return;
    ProcessData->RemainingTime = ProcessData->BurstTime;
    ProcessData->WaitingTime = 0;
    ProcessData->TurnaroundTime = 0;
    ProcessData->ResponseTime = -1;
    ProcessData->CompletionTime = 0;
    ProcessData->StartTime = -1;
    ProcessData->IsCompleted = false;
}

void CopyProcess(Process* Destination, const Process* Source) {
    if (!Destination || !Source) return;
    *Destination = *Source;
}

bool IsProcessCompleted(const Process* ProcessData) {
    if (!ProcessData) return true;
    return ProcessData->IsCompleted || ProcessData->RemainingTime <= 0;
}

bool HasProcessStarted(const Process* ProcessData) {
    if (!ProcessData) return false;
    return ProcessData->StartTime >= 0;
}

void StartProcess(Process* ProcessData, int CurrentTime) {
    if (!ProcessData) return;
    if (ProcessData->StartTime < 0) {
        ProcessData->StartTime = CurrentTime;
        ProcessData->ResponseTime = CurrentTime - ProcessData->ArrivalTime;
    }
}

int ExecuteProcess(Process* ProcessData, int TimeUnits) {
    if (!ProcessData || ProcessData->IsCompleted || ProcessData->RemainingTime <= 0) {
        return 0;
    }
    // min_int lấy từ utils.h
    int ExecutedTime = min_int(TimeUnits, ProcessData->RemainingTime);
    ProcessData->RemainingTime -= ExecutedTime;

    if (ProcessData->RemainingTime <= 0) {
        ProcessData->RemainingTime = 0;
        ProcessData->IsCompleted = true;
    }
    return ExecutedTime;
}

void CompleteProcess(Process* ProcessData, int CurrentTime) {
    if (!ProcessData) return;
    ProcessData->IsCompleted = true;
    ProcessData->RemainingTime = 0;
    ProcessData->CompletionTime = CurrentTime;
    ProcessData->TurnaroundTime = ProcessData->CompletionTime - ProcessData->ArrivalTime;
    ProcessData->WaitingTime = ProcessData->TurnaroundTime - ProcessData->BurstTime;
    if (ProcessData->WaitingTime < 0) ProcessData->WaitingTime = 0;
}

// Comparators
int CompareProcessByArrival(const void* First, const void* Second) {
    const Process* P1 = (const Process*)First;
    const Process* P2 = (const Process*)Second;
    if (P1->ArrivalTime != P2->ArrivalTime) return P1->ArrivalTime - P2->ArrivalTime;
    return P1->ProcessId - P2->ProcessId;
}

int CompareProcessByBurst(const void* First, const void* Second) {
    const Process* P1 = (const Process*)First;
    const Process* P2 = (const Process*)Second;
    if (P1->BurstTime != P2->BurstTime) return P1->BurstTime - P2->BurstTime;
    return P1->ArrivalTime - P2->ArrivalTime;
}

int CompareProcessByRemaining(const void* First, const void* Second) {
    const Process* P1 = (const Process*)First;
    const Process* P2 = (const Process*)Second;
    if (P1->RemainingTime != P2->RemainingTime) return P1->RemainingTime - P2->RemainingTime;
    return P1->ArrivalTime - P2->ArrivalTime;
}

int CompareProcessByPriority(const void* First, const void* Second) {
    const Process* P1 = (const Process*)First;
    const Process* P2 = (const Process*)Second;
    if (P1->Priority != P2->Priority) return P1->Priority - P2->Priority;
    return P1->ArrivalTime - P2->ArrivalTime;
}

int CompareProcessById(const void* First, const void* Second) {
    const Process* P1 = (const Process*)First;
    const Process* P2 = (const Process*)Second;
    return P1->ProcessId - P2->ProcessId;
}

// Display & Validation
bool ValidateProcess(const Process* ProcessData) {
    if (!ProcessData) return false;
    if (ProcessData->ProcessId < 0) return false;
    if (ProcessData->ArrivalTime < 0) return false;
    if (ProcessData->BurstTime <= 0) return false;
    return true;
}

void PrintProcess(const Process* ProcessData) {
    if (!ProcessData) return;
    printf("Process P%d: AT=%d, BT=%d, Pri=%d, RT=%d, Status=%s\n",
        ProcessData->ProcessId, ProcessData->ArrivalTime, ProcessData->BurstTime,
        ProcessData->Priority, ProcessData->RemainingTime,
        ProcessData->IsCompleted ? "Done" : "Pending");
}

void PrintProcessShort(const Process* ProcessData) {
    if (!ProcessData) { printf("NULL\n"); return; }
    printf("P%d [AT:%d BT:%d RT:%d Pri:%d %s]\n",
        ProcessData->ProcessId,
        ProcessData->ArrivalTime,
        ProcessData->BurstTime,
        ProcessData->RemainingTime,
        ProcessData->Priority,
        ProcessData->IsCompleted ? "[x]" : "[ ]");
}