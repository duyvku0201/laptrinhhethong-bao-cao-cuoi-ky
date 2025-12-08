#define _CRT_SECURE_NO_WARNINGS
#ifndef IO_H
#define IO_H

#include "process.h"
#include <stdbool.h>

#define MAX_LINE_LENGTH 256
#define MAX_FILENAME_LENGTH 100

// Đọc processes từ console
bool ReadProcessesFromConsole(Process *Processes, int *ProcessCount);

// Đọc processes từ file
bool LoadProcessesFromFile(const char *Filename, Process *Processes, int *ProcessCount);

// Wrapper functions for main.c
int read_from_file(const char *filename, Process p[], int *n);
int read_from_keyboard(Process p[], int *n);

// Ghi kết quả vào file
bool SaveResultsToFile(const char *Filename, const char *AlgorithmName,
                       Process *Processes, int ProcessCount,
                       float AvgWaitingTime, float AvgTurnaroundTime);

// Hiển thị bảng kết quả
void DisplayResults(const char *AlgorithmName, Process *Processes,
                    int ProcessCount, float AvgWaitingTime, float AvgTurnaroundTime);

// Kiểm tra file tồn tại
bool FileExists(const char *Filename);

// Validate dữ liệu process
bool ValidateProcessData(Process *ProcessData);

// Xóa buffer
void ClearInputBuffer(void);

#endif
