#include "../../include/algorithms.h"
#include "../../include/process.h"
#include "../../include/metrics.h"
#include "../../include/display.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

void srtf(Process Processes[], int ProcessCount) {
    int CurrentTime = 0;
    int CompletedCount = 0;

    for (int i = 0; i < ProcessCount; i++) {
        Processes[i].RemainingTime = Processes[i].BurstTime;
        Processes[i].IsCompleted = false;
        Processes[i].StartTime = -1;
    }

    while (CompletedCount != ProcessCount) {
        int MinRemainingTime = INT_MAX;
        int ShortestIndex = -1;
        bool HasProcess = false;

        for (int i = 0; i < ProcessCount; i++) {
            if (Processes[i].ArrivalTime <= CurrentTime && !Processes[i].IsCompleted && Processes[i].RemainingTime < MinRemainingTime) {
                MinRemainingTime = Processes[i].RemainingTime;
                ShortestIndex = i;
                HasProcess = true;
            }
        }

        if (!HasProcess) {
            CurrentTime++;
            continue;
        }

        if (Processes[ShortestIndex].StartTime == -1) Processes[ShortestIndex].StartTime = CurrentTime;

        log_gantt_event(Processes[ShortestIndex].ProcessId, CurrentTime, CurrentTime + 1);

        Processes[ShortestIndex].RemainingTime--;
        CurrentTime++;

        if (Processes[ShortestIndex].RemainingTime == 0) {
            CompletedCount++;
            Processes[ShortestIndex].IsCompleted = true;
            Processes[ShortestIndex].CompletionTime = CurrentTime;
        }
    }
    CalculateAllMetrics(Processes, ProcessCount);
}