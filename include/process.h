#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>

#define MAX_PROCESSES 100
#define DEFAULT_TIME_QUANTUM 2
#define MAX_TIMELINE_ENTRIES 1000

// Struct để lưu execution timeline của process
typedef struct {
    int process_id;
    int start_time;
    int end_time;
} TimelineEntry;

// Global timeline để lưu lại execution history
extern TimelineEntry global_timeline[MAX_TIMELINE_ENTRIES];
extern int global_timeline_count;

// Cấu trúc Process
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

// ==============================
// Khởi tạo và tạo Process
// ==============================
void InitProcess(Process* ProcessData);
Process CreateProcess(int Id, int Arrival, int Burst, int Priority);
void ResetProcess(Process* ProcessData);
void CopyProcess(Process* Destination, const Process* Source);

// ==============================
// Quản lý trạng thái Process
// ==============================
bool IsProcessCompleted(const Process* ProcessData);
bool HasProcessStarted(const Process* ProcessData);
void StartProcess(Process* ProcessData, int CurrentTime);
int ExecuteProcess(Process* ProcessData, int TimeUnits);
void CompleteProcess(Process* ProcessData, int CurrentTime);

// ==============================
// So sánh Processes (dùng cho qsort)
// ==============================
int CompareProcessByArrival(const void* First, const void* Second);
int CompareProcessByBurst(const void* First, const void* Second);
int CompareProcessByRemaining(const void* First, const void* Second);
int CompareProcessByPriority(const void* First, const void* Second);
int CompareProcessById(const void* First, const void* Second);

// ==============================
// Validation và Display
// ==============================
bool ValidateProcess(const Process* ProcessData);
void PrintProcess(const Process* ProcessData);
void PrintProcessShort(const Process* ProcessData);

// ==============================
// Timeline tracking
// ==============================
void reset_timeline(void);
void add_timeline_entry(int process_id, int start_time, int end_time);

#endif // PROCESS_H