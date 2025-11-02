#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "process.h"

void fcfs(Process p[], int n);
void sjf(Process p[], int n);
void srtf(Process p[], int n);
void priority_non_preemptive(Process p[], int n);
void priority_preemptive(Process p[], int n);
void round_robin(Process p[], int n, int tq);

#endif
