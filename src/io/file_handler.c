#define _CRT_SECURE_NO_WARNINGS
#include "io.h"
#include <stdio.h>

// Kiểm tra file tồn tại
bool FileExists(const char* Filename) {
    FILE* File = fopen(Filename, "r");
    if (File == NULL) return false;

    fclose(File);
    return true;
}

// Mở file để đọc
static FILE* OpenFileForReading(const char* Filename) {
    FILE* File = fopen(Filename, "r");
    if (File == NULL) {
        printf("Error: Cannot open file '%s'\n", Filename);
    }
    return File;
}

// Đọc số lượng processes từ file
static bool ReadProcessCountFromFile(FILE* File, int* ProcessCount) {
    if (fscanf(File, "%d", ProcessCount) != 1) {
        printf("Error: Cannot read process count\n");
        return false;
    }

    if (*ProcessCount < 1 || *ProcessCount > MAX_PROCESSES) {
        printf("Error: Invalid process count: %d\n", *ProcessCount);
        return false;
    }

    printf("Number of processes: %d\n", *ProcessCount);
    return true;
}

// Đọc một process từ file
static bool ReadSingleProcessFromFile(FILE* File, Process* P, int Index) {
    int ReadItems = fscanf(File, "%d %d %d %d",
        &P->ProcessId,
        &P->ArrivalTime,
        &P->BurstTime,
        &P->Priority);

    if (ReadItems != 4) {
        printf("Error reading Process #%d\n", Index);
        return false;
    }

    P->RemainingTime = P->BurstTime;
    P->WaitingTime = 0;
    P->TurnaroundTime = 0;
    P->ResponseTime = -1;
    P->CompletionTime = 0;
    P->StartTime = -1;
    P->IsCompleted = false;

    if (!ValidateProcessData(P)) {
        printf("Error: Invalid data for Process #%d\n", Index);
        return false;
    }

    printf("Process %d: AT=%d, BT=%d, Priority=%d\n",
        P->ProcessId, P->ArrivalTime, P->BurstTime, P->Priority);

    return true;
}

// Đọc tất cả processes từ file
static bool ReadAllProcessesFromFile(FILE* File, Process* Processes, int ProcessCount) {
    for (int i = 0; i < ProcessCount; i++) {
        if (!ReadSingleProcessFromFile(File, &Processes[i], i + 1)) {
            return false;
        }
    }
    return true;
}

// Đọc processes từ file (sử dụng early return và extract functions)
bool LoadProcessesFromFile(const char* Filename, Process* Processes, int* ProcessCount) {
    printf("Reading file: %s\n", Filename);

    FILE* File = OpenFileForReading(Filename);
    if (File == NULL) return false;

    if (!ReadProcessCountFromFile(File, ProcessCount)) {
        fclose(File);
        return false;
    }

    if (!ReadAllProcessesFromFile(File, Processes, *ProcessCount)) {
        fclose(File);
        return false;
    }

    fclose(File);
    printf("File read successfully\n\n");
    return true;
}

// Mở file để ghi
static FILE* OpenFileForWriting(const char* Filename) {
    FILE* File = fopen(Filename, "w");
    if (File == NULL) {
        printf("Error: Cannot create file '%s'\n", Filename);
    }
    return File;
}

// Ghi header vào file
static void WriteHeader(FILE* File, const char* AlgorithmName) {
    fprintf(File, "=== %s Scheduling Results ===\n\n", AlgorithmName);
    fprintf(File, "Process | Arrival | Burst | Waiting | Turnaround | Response\n");
    fprintf(File, "--------|---------|-------|---------|------------|----------\n");
}

// Ghi một process vào file
static void WriteSingleProcess(FILE* File, const Process* P) {
    fprintf(File, "%-7d | %7d | %5d | %7d | %10d | %8d\n",
        P->ProcessId, P->ArrivalTime, P->BurstTime,
        P->WaitingTime, P->TurnaroundTime, P->ResponseTime);
}

// Ghi tất cả processes vào file
static void WriteAllProcesses(FILE* File, const Process* Processes, int ProcessCount) {
    for (int i = 0; i < ProcessCount; i++) {
        WriteSingleProcess(File, &Processes[i]);
    }
}

// Ghi metrics vào file
static void WriteMetrics(FILE* File, float AvgWaitingTime, float AvgTurnaroundTime) {
    fprintf(File, "\nAverage Waiting Time: %.2f\n", AvgWaitingTime);
    fprintf(File, "Average Turnaround Time: %.2f\n", AvgTurnaroundTime);
}

// Ghi kết quả vào file (sử dụng early return và extract functions)
bool SaveResultsToFile(const char* Filename, const char* AlgorithmName,
    Process* Processes, int ProcessCount,
    float AvgWaitingTime, float AvgTurnaroundTime) {
    FILE* File = OpenFileForWriting(Filename);
    if (File == NULL) return false;

    WriteHeader(File, AlgorithmName);
    WriteAllProcesses(File, Processes, ProcessCount);
    WriteMetrics(File, AvgWaitingTime, AvgTurnaroundTime);

    fclose(File);
    printf("Results saved to: %s\n", Filename);
    return true;
}