#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

// Show result table with basic metrics (WT/TAT/RT if available)
void display_results(Process p[], int n, const char *algo);

// Simple Gantt-like visualization using pid in order of completion/start
void display_gantt_chart(Process p[], int n);

// Compare algorithms placeholder (can be enhanced later)
void display_comparison(Process p[], int n);

#endif // DISPLAY_H
