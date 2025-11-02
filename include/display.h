#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

void display_results(Process p[], int n, const char* algo);
void display_gantt_chart(Process p[], int n);
void display_comparison(Process p[], int n);

#endif
