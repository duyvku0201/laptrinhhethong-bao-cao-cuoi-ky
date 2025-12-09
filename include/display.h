#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

// Show result table with basic metrics
void display_results(Process p[], int n, const char* algo);
void display_results_colored(Process p[], int n, const char* algo);

// Gantt Chart functions
void display_gantt_chart(Process p[], int n);
void display_gantt_chart_colored(Process p[], int n);

// Gantt Logging Functions (New)
void reset_gantt_log(void);
void log_gantt_event(int pid, int start, int end);

// Comparison
void display_comparison(Process original[], int n, int time_quantum);

#endif // DISPLAY_H