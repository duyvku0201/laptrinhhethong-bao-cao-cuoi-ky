#ifndef METRICS_H
#define METRICS_H

#include "process.h"
#include <stdbool.h>

// Tính Waiting Time cho một process
// WT = TAT - BT
void CalculateWaitingTime(Process* ProcessData);

// Tính Turnaround Time cho một process
// TAT = CT - AT
void CalculateTurnaroundTime(Process* ProcessData);

// Tính Response Time cho một process
// RT = Thời điểm bắt đầu thực thi lần đầu - AT
void CalculateResponseTime(Process* ProcessData, int FirstResponseTime);

// Tính Average Waiting Time cho tất cả processes
float CalculateAverageWaitingTime(Process* Processes, int ProcessCount);

// Tính Average Turnaround Time cho tất cả processes
float CalculateAverageTurnaroundTime(Process* Processes, int ProcessCount);

// Tính Average Response Time cho tất cả processes
float CalculateAverageResponseTime(Process* Processes, int ProcessCount);

// Tính tất cả metrics cho một process
void CalculateProcessMetrics(Process* ProcessData, int FirstResponseTime);

// Tính tất cả metrics cho danh sách processes
void CalculateAllMetrics(Process* Processes, int ProcessCount);

// Tính CPU Utilization
// CPU Utilization = (Total Burst Time / Total Time) * 100
float CalculateCpuUtilization(Process* Processes, int ProcessCount, int TotalTime);

// Tính Throughput
// Throughput = Số process hoàn thành / Total Time
float CalculateThroughput(int ProcessCount, int TotalTime);

// In tất cả metrics
void DisplayAllMetrics(Process* Processes, int ProcessCount, int TotalTime);

// Kiểm tra tính hợp lệ của metrics
bool ValidateMetrics(Process* ProcessData);

#endif