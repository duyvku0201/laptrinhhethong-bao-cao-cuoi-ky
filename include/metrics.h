#ifndef METRICS_H
#define METRICS_H

#include "process.h"
#include <stdbool.h>

void CalculateWaitingTime(Process* ProcessData);
void CalculateTurnaroundTime(Process* ProcessData);
void CalculateResponseTime(Process* ProcessData, int FirstResponseTime);

float CalculateAverageWaitingTime(Process* Processes, int ProcessCount);
float CalculateAverageTurnaroundTime(Process* Processes, int ProcessCount);
float CalculateAverageResponseTime(Process* Processes, int ProcessCount);

void CalculateProcessMetrics(Process* ProcessData, int FirstResponseTime);
void CalculateAllMetrics(Process* Processes, int ProcessCount);

float CalculateCpuUtilization(Process* Processes, int ProcessCount, int TotalTime);
float CalculateThroughput(int ProcessCount, int TotalTime);

void DisplayAllMetrics(Process* Processes, int ProcessCount, int TotalTime);
bool ValidateMetrics(Process* ProcessData);

#endif // METRICS_H