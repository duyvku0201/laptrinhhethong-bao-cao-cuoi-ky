#ifndef METRICS_H
#define METRICS_H

#include "process.h"
#include <stdbool.h>

// Tính metrics cho một process
void CalculateWaitingTime(Process* ProcessData);
void CalculateTurnaroundTime(Process* ProcessData);
void CalculateResponseTime(Process* ProcessData, int FirstResponseTime);
void CalculateProcessMetrics(Process* ProcessData, int FirstResponseTime);

// Tính metrics cho tất cả processes
void CalculateAllMetrics(Process* Processes, int ProcessCount);

// Tính average metrics
float CalculateAverageWaitingTime(Process* Processes, int ProcessCount);
float CalculateAverageTurnaroundTime(Process* Processes, int ProcessCount);
float CalculateAverageResponseTime(Process* Processes, int ProcessCount);

// Tính system metrics
float CalculateCpuUtilization(Process* Processes, int ProcessCount, int TotalTime);
float CalculateThroughput(int ProcessCount, int TotalTime);

// Display và validation
void DisplayAllMetrics(Process* Processes, int ProcessCount, int TotalTime);
bool ValidateMetrics(Process* ProcessData);

#endif