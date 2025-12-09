#ifndef IO_H
#define IO_H

#include "process.h"
#include <stdbool.h>

#define MAX_LINE_LENGTH 256
#define MAX_FILENAME_LENGTH 100

// Đọc processes từ console
bool ReadProcessesFromConsole(Process* Processes, int* ProcessCount);

// Đọc processes từ file
bool LoadProcessesFromFile(const char* Filename, Process* Processes, int* ProcessCount);

// Ghi kết quả vào file
bool SaveResultsToFile(const char* Filename, const char* AlgorithmName,
    Process* Processes, int ProcessCount,
    float AvgWaitingTime, float AvgTurnaroundTime);

// Validate dữ liệu process
bool ValidateProcessData(Process* ProcessData);

// Xóa buffer (có thể không dùng tới nếu dùng get_int_input_with_esc, nhưng giữ lại cho tương thích ngược)
void ClearInputBuffer(void);

#endif // IO_H