#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

// Show result table with metrics (WT/TAT/RT/CPU Utilization/Throughput)
void display_results(Process p[], int n, const char *algo);

// Simple Gantt-like visualization using pid in order of completion/start
void display_gantt_chart(Process p[], int n);

// Compare all algorithms and display comparison table
void display_comparison(Process original[], int n, int time_quantum);

#endif // DISPLAY_H
