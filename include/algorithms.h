#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

// FCFS (First Come First Serve) - Non-preemptive
void fcfs(Process processes[], int n);

// SJF (Shortest Job First) - Non-preemptive
void sjf(Process processes[], int n);

// SRTF (Shortest Remaining Time First) - Preemptive SJF
void srtf(Process processes[], int n);

// Priority Scheduling - Non-preemptive
void priority_non_preemptive(Process processes[], int n);

// Priority Scheduling - Preemptive
void priority_preemptive(Process processes[], int n);

// Round Robin with time quantum
void round_robin(Process processes[], int n, int time_quantum);

#endif // ALGORITHMS_H
