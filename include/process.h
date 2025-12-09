#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_PROCESS_ID_LENGTH 20
#define DEFAULT_TIME_QUANTUM 2

// Cấu trúc lưu thông tin process
typedef struct
{
    int ProcessId;         // ID tiến trình
    int ArrivalTime;       // Thời điểm đến
    int BurstTime;         // Thời gian xử lý
    int Priority;          // Mức độ ưu tiên
    int RemainingTime;     // Thời gian còn lại
    int WaitingTime;       // Thời gian chờ
    int TurnaroundTime;    // Thời gian hoàn thành vòng đời
    int ResponseTime;      // Thời gian phản hồi
    int CompletionTime;    // Thời điểm hoàn thành
    int StartTime;         // Thời điểm bắt đầu chạy
    bool IsCompleted;      // Trạng thái hoàn thành
} Process;

// Function prototypes
void InitProcess(Process* ProcessData);
Process CreateProcess(int Id, int Arrival, int Burst, int Priority);
void ResetProcess(Process* ProcessData);
void CopyProcess(Process* Destination, const Process* Source);

// Process State Checks
bool IsProcessCompleted(const Process* ProcessData);
bool HasProcessStarted(const Process* ProcessData);

// Processing Functions
void StartProcess(Process* ProcessData, int CurrentTime);
int ExecuteProcess(Process* ProcessData, int TimeUnits);
void CompleteProcess(Process* ProcessData, int CurrentTime);

// Comparators (for sorting)
int CompareProcessByArrival(const void* First, const void* Second);
int CompareProcessByBurst(const void* First, const void* Second);
int CompareProcessByRemaining(const void* First, const void* Second);
int CompareProcessByPriority(const void* First, const void* Second);
int CompareProcessById(const void* First, const void* Second);

// Validation & Display
bool ValidateProcess(const Process* ProcessData);
void PrintProcess(const Process* ProcessData);
void PrintProcessShort(const Process* ProcessData);

#endif // PROCESS_H