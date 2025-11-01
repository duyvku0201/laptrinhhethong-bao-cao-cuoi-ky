#include "../include/io.h"
#include <stdio.h>

// Simulate scheduling results cho test
static void SimulateSchedulingResults(Process* Processes, int ProcessCount) {
    for (int i = 0; i < ProcessCount; i++) {
        Processes[i].WaitingTime = i * 2;
        Processes[i].TurnaroundTime = Processes[i].BurstTime + Processes[i].WaitingTime;
        Processes[i].ResponseTime = Processes[i].WaitingTime;
    }
}

// Test đọc từ file
static void TestReadFromFile(Process* Processes, int* ProcessCount) {
    char Filename[MAX_FILENAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", Filename);
    ClearInputBuffer();

    if (LoadProcessesFromFile(Filename, Processes, ProcessCount)) {
        printf("Read %d processes from file\n", *ProcessCount);
    }
}

// Test đọc từ console
static void TestReadFromConsole(Process* Processes, int* ProcessCount) {
    if (ReadProcessesFromConsole(Processes, ProcessCount)) {
        printf("Read %d processes from console\n", *ProcessCount);
    }
}

// Test hiển thị kết quả
static void TestDisplayResults(Process* Processes, int ProcessCount) {
    if (ProcessCount == 0) {
        printf("No data. Please read data first.\n");
        return;
    }

    SimulateSchedulingResults(Processes, ProcessCount);
    DisplayResults("TEST", Processes, ProcessCount, 5.5, 12.3);
}

// Test lưu vào file
static void TestSaveToFile(Process* Processes, int ProcessCount) {
    if (ProcessCount == 0) {
        printf("No data. Please read data first.\n");
        return;
    }

    char OutputFile[MAX_FILENAME_LENGTH];
    printf("Enter output filename: ");
    scanf("%s", OutputFile);
    ClearInputBuffer();

    SaveResultsToFile(OutputFile, "TEST", Processes, ProcessCount, 5.5, 12.3);
}

// In menu
static void PrintMenu(void) {
    printf("\n1. Read from file\n");
    printf("2. Read from console\n");
    printf("3. Display results\n");
    printf("4. Save to file\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

// Đọc lựa chọn
static bool ReadChoice(int* Choice) {
    if (scanf("%d", Choice) != 1) {
        ClearInputBuffer();
        return false;
    }
    ClearInputBuffer();
    return true;
}

// Xử lý lựa chọn (sử dụng early return)
static bool HandleChoice(int Choice, Process* Processes, int* ProcessCount) {
    if (Choice == 0) return false;

    switch (Choice) {
    case 1:
        TestReadFromFile(Processes, ProcessCount);
        break;
    case 2:
        TestReadFromConsole(Processes, ProcessCount);
        break;
    case 3:
        TestDisplayResults(Processes, *ProcessCount);
        break;
    case 4:
        TestSaveToFile(Processes, *ProcessCount);
        break;
    default:
        printf("Invalid choice\n");
    }

    return true;
}

int main() {
    Process Processes[MAX_PROCESSES];
    int ProcessCount = 0;
    int Choice;

    printf("=== IO Module Test ===\n");

    while (1) {
        PrintMenu();

        if (!ReadChoice(&Choice)) continue;

        if (!HandleChoice(Choice, Processes, &ProcessCount)) {
            printf("Exit\n");
            break;
        }
    }

    return 0;
}