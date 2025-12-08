#define _CRT_SECURE_NO_WARNINGS
#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Xóa buffer stdin
void ClearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Kiểm tra Process ID hợp lệ
static bool IsValidProcessId(int ProcessId) {
    if (ProcessId <= 0) {
        printf("Error: Process ID must be > 0\n");
        return false;
    }
    return true;
}

// Kiểm tra Arrival Time hợp lệ
static bool IsValidArrivalTime(int ArrivalTime) {
    if (ArrivalTime < 0) {
        printf("Error: Arrival Time must be >= 0\n");
        return false;
    }
    return true;
}

// Kiểm tra Burst Time hợp lệ
static bool IsValidBurstTime(int BurstTime) {
    if (BurstTime <= 0) {
        printf("Error: Burst Time must be > 0\n");
        return false;
    }
    return true;
}

// Kiểm tra Priority hợp lệ
static bool IsValidPriority(int Priority) {
    if (Priority < 0) {
        printf("Error: Priority must be >= 0\n");
        return false;
    }
    return true;
}

// Kiểm tra dữ liệu process hợp lệ (sử dụng early return)
bool ValidateProcessData(Process* ProcessData) {
    if (!IsValidProcessId(ProcessData->ProcessId)) return false;
    if (!IsValidArrivalTime(ProcessData->ArrivalTime)) return false;
    if (!IsValidBurstTime(ProcessData->BurstTime)) return false;
    if (!IsValidPriority(ProcessData->Priority)) return false;

    return true;
}

// Khởi tạo giá trị mặc định cho process
static void InitializeProcessDefaults(Process* ProcessData) {
    ProcessData->RemainingTime = ProcessData->BurstTime;
    ProcessData->WaitingTime = 0;
    ProcessData->TurnaroundTime = 0;
    ProcessData->ResponseTime = -1;
    ProcessData->CompletionTime = 0;
    ProcessData->IsCompleted = false;
}

// Đọc Process ID
static bool ReadProcessId(Process* ProcessData) {
    printf("Process ID: ");
    if (scanf("%d", &ProcessData->ProcessId) != 1) {
        ClearInputBuffer();
        return false;
    }
    return true;
}

// Đọc Arrival Time
static bool ReadArrivalTime(Process* ProcessData) {
    printf("Arrival Time: ");
    if (scanf("%d", &ProcessData->ArrivalTime) != 1) {
        ClearInputBuffer();
        return false;
    }
    return true;
}

// Đọc Burst Time
static bool ReadBurstTime(Process* ProcessData) {
    printf("Burst Time: ");
    if (scanf("%d", &ProcessData->BurstTime) != 1) {
        ClearInputBuffer();
        return false;
    }
    return true;
}

// Đọc Priority
static bool ReadPriority(Process* ProcessData) {
    printf("Priority: ");
    if (scanf("%d", &ProcessData->Priority) != 1) {
        ClearInputBuffer();
        return false;
    }
    return true;
}

// Đọc một process từ console (sử dụng early return)
static bool ReadSingleProcess(Process* ProcessData, int Index) {
    printf("\nProcess #%d:\n", Index);

    if (!ReadProcessId(ProcessData)) return false;
    if (!ReadArrivalTime(ProcessData)) return false;
    if (!ReadBurstTime(ProcessData)) return false;
    if (!ReadPriority(ProcessData)) return false;

    ClearInputBuffer();

    InitializeProcessDefaults(ProcessData);

    if (!ValidateProcessData(ProcessData)) return false;

    printf("Process %d added successfully\n", ProcessData->ProcessId);
    return true;
}

// Kiểm tra số lượng process hợp lệ
static bool IsValidProcessCount(int ProcessCount) {
    if (ProcessCount < 1 || ProcessCount > MAX_PROCESSES) {
        printf("Error: Number of processes must be between 1 and %d\n", MAX_PROCESSES);
        return false;
    }
    return true;
}

// Đọc số lượng processes
static bool ReadProcessCount(int* ProcessCount) {
    printf("\nEnter number of processes (1-%d): ", MAX_PROCESSES);
    if (scanf("%d", ProcessCount) != 1) {
        ClearInputBuffer();
        return false;
    }

    if (!IsValidProcessCount(*ProcessCount)) {
        ClearInputBuffer();
        return false;
    }

    ClearInputBuffer();
    return true;
}

// Đọc danh sách processes từ console
bool ReadProcessesFromConsole(Process* Processes, int* ProcessCount) {
    if (!ReadProcessCount(ProcessCount)) return false;

    for (int i = 0; i < *ProcessCount; i++) {
        bool Success = ReadSingleProcess(&Processes[i], i + 1);

        if (!Success) {
            printf("Error reading Process #%d. Please try again.\n", i + 1);
            i--;
            continue;
        }
    }

    printf("\nSuccessfully read %d processes\n", *ProcessCount);
    return true;
}