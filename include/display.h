#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

// Show result table with basic metrics (WT/TAT/RT if available)
void display_results(Process p[], int n, const char *algo);

// Show result table with colored output
void display_results_colored(Process p[], int n, const char *algo);

// Simple Gantt-like visualization using pid in order of completion/start
void display_gantt_chart(Process p[], int n);

// Gantt chart with colored output
void display_gantt_chart_colored(Process p[], int n);

// Compare all algorithms
void display_comparison(Process original[], int n, int time_quantum);

// Compare all algorithms with colored output
void display_comparison_colored(Process original[], int n, int time_quantum);

#endif // DISPLAY_H
