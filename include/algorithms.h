#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

void fcfs(Process processes[], int n);
void sjf(Process processes[], int n);
void srtf(Process processes[], int n);
void priority_non_preemptive(Process processes[], int n);
void priority_preemptive(Process processes[], int n);
void round_robin(Process processes[], int n, int time_quantum);

#endif // ALGORITHMS_H