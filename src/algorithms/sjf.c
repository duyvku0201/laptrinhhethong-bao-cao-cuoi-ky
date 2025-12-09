#include "../../include/algorithms.h"
#include "../../include/process.h"
#include "../../include/metrics.h"
#include "../../include/display.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

void sjf(Process Processes[], int ProcessCount) {
    int CurrentTime = 0;
    int CompletedCount = 0;

    // Init
    for (int i = 0; i < ProcessCount; i++) {
        Processes[i].RemainingTime = Processes[i].BurstTime;
        Processes[i].IsCompleted = false;
        Processes[i].StartTime = -1;
    }

    while (CompletedCount != ProcessCount) {
        int MinBurstTime = INT_MAX;
        int ShortestIndex = -1;
        bool HasProcess = false;

        for (int i = 0; i < ProcessCount; i++) {
            if (Processes[i].ArrivalTime <= CurrentTime && !Processes[i].IsCompleted) {
                if (Processes[i].BurstTime < MinBurstTime) {
                    MinBurstTime = Processes[i].BurstTime;
                    ShortestIndex = i;
                    HasProcess = true;
                }
                else if (Processes[i].BurstTime == MinBurstTime) {
                    if (ShortestIndex == -1 || Processes[i].ArrivalTime < Processes[ShortestIndex].ArrivalTime) {
                        ShortestIndex = i;
                        HasProcess = true;
                    }
                }
            }
        }

        if (!HasProcess) {
            CurrentTime++;
            continue;
        }

        Processes[ShortestIndex].StartTime = CurrentTime;
        log_gantt_event(Processes[ShortestIndex].ProcessId, CurrentTime, CurrentTime + Processes[ShortestIndex].BurstTime);

        CurrentTime += Processes[ShortestIndex].BurstTime;
        Processes[ShortestIndex].CompletionTime = CurrentTime;
        Processes[ShortestIndex].IsCompleted = true;
        CompletedCount++;
    }
    CalculateAllMetrics(Processes, ProcessCount);
}