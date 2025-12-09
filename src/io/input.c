#include "../../include/io.h"
#include "../../include/utils.h" // Cần include cái này để dùng ESC_CANCEL
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void ClearInputBuffer(void) {
    // Không còn dùng nhiều vì get_int_input_with_esc tự xử lý
}

bool ValidateProcessData(Process* ProcessData) {
    if (ProcessData->ProcessId <= 0) { printf("Error: Process ID > 0\n"); return false; }
    if (ProcessData->ArrivalTime < 0) { printf("Error: Arrival Time >= 0\n"); return false; }
    if (ProcessData->BurstTime <= 0) { printf("Error: Burst Time > 0\n"); return false; }
    if (ProcessData->Priority < 0) { printf("Error: Priority >= 0\n"); return false; }
    return true;
}

static void InitializeProcessDefaults(Process* ProcessData) {
    ProcessData->RemainingTime = ProcessData->BurstTime;
    ProcessData->WaitingTime = 0;
    ProcessData->TurnaroundTime = 0;
    ProcessData->ResponseTime = -1;
    ProcessData->CompletionTime = 0;
    ProcessData->IsCompleted = false;
    ProcessData->StartTime = -1;
}

// Hàm nhập process đơn lẻ có hỗ trợ ESC
static int ReadSingleProcess(Process* ProcessData, int Index) {
    printf("\nProcess #%d (Press Esc to cancel):\n", Index);

    int val;

    // Nhập ID
    val = get_int_input_with_esc("Process ID: ");
    if (val == ESC_CANCEL) return ESC_CANCEL;
    ProcessData->ProcessId = val;

    // Nhập Arrival
    val = get_int_input_with_esc("Arrival Time: ");
    if (val == ESC_CANCEL) return ESC_CANCEL;
    ProcessData->ArrivalTime = val;

    // Nhập Burst
    val = get_int_input_with_esc("Burst Time: ");
    if (val == ESC_CANCEL) return ESC_CANCEL;
    ProcessData->BurstTime = val;

    // Nhập Priority
    val = get_int_input_with_esc("Priority: ");
    if (val == ESC_CANCEL) return ESC_CANCEL;
    ProcessData->Priority = val;

    InitializeProcessDefaults(ProcessData);

    if (!ValidateProcessData(ProcessData)) return 0; // 0 = Lỗi dữ liệu

    printf("Process %d added successfully\n", ProcessData->ProcessId);
    return 1; // 1 = Thành công
}

bool ReadProcessesFromConsole(Process* Processes, int* ProcessCount) {
    int count = get_int_input_with_esc("\nEnter number of processes (1-100): ");

    if (count == ESC_CANCEL) return false;

    if (count < 1 || count > MAX_PROCESSES) {
        printf("Error: Number of processes must be between 1 and %d\n", MAX_PROCESSES);
        return false;
    }

    *ProcessCount = count;

    for (int i = 0; i < *ProcessCount; i++) {
        int result = ReadSingleProcess(&Processes[i], i + 1);

        if (result == ESC_CANCEL) return false; // Người dùng hủy nhập

        if (result == 0) { // Lỗi dữ liệu
            printf("Error reading Process #%d. Please try again.\n", i + 1);
            i--;
            continue;
        }
    }

    printf("\nSuccessfully read %d processes\n", *ProcessCount);
    return true;
}