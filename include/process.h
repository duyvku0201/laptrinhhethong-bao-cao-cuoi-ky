
#pragma once
#ifndef PROCESS_H
#define PROCESS_H

// typedef struct để có thể dùng Process trực tiếp
typedef struct Process {
    int pid;           // Process ID
    int arrival_time;  // Arrival Time
    int burst_time;    // CPU Burst Time
    int priority;      // Priority
} Process;

#endif
