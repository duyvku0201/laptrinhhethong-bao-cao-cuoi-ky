/**
 * @file test_round_robin.c
 * @brief Test program for Round Robin algorithm
 */

#include "../include/process.h"
#include "../include/algorithms.h"
#include "../include/display.h"
#include "../include/metrics.h"
#include <stdio.h>
#include <stdlib.h>

// Function to read processes from file
int read_processes_from_file(const char *filename, Process processes[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    int n;
    if (fscanf(file, "%d", &n) != 1) {
        printf("Error: Cannot read number of processes\n");
        fclose(file);
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d %d %d %d", 
                   &processes[i].ProcessId,
                   &processes[i].ArrivalTime,
                   &processes[i].BurstTime,
                   &processes[i].Priority) != 4) {
            printf("Error: Cannot read process %d\n", i);
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return n;
}

// Calculate average metrics
void calculate_avg_metrics(Process processes[], int n, 
                          float *avg_wt, float *avg_tat, float *avg_rt) {
    if (n <= 0) {
        *avg_wt = *avg_tat = *avg_rt = 0;
        return;
    }
    
    long sum_wt = 0, sum_tat = 0, sum_rt = 0;
    int counted_rt = 0;
    
    for (int i = 0; i < n; i++) {
        sum_wt += processes[i].WaitingTime;
        sum_tat += processes[i].TurnaroundTime;
        if (processes[i].ResponseTime >= 0) {
            sum_rt += processes[i].ResponseTime;
            counted_rt++;
        }
    }
    
    *avg_wt = (float)sum_wt / n;
    *avg_tat = (float)sum_tat / n;
    *avg_rt = counted_rt > 0 ? (float)sum_rt / counted_rt : 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file> [time_quantum]\n", argv[0]);
        printf("Example: %s tests/test_cases/test_rr_main.txt 3\n", argv[0]);
        return 1;
    }
    
    Process processes[MAX_PROCESSES];
    int n = read_processes_from_file(argv[1], processes);
    
    if (n <= 0) {
        printf("Error reading processes from file\n");
        return 1;
    }
    
    int time_quantum = 3; // Default
    if (argc >= 3) {
        time_quantum = atoi(argv[2]);
        if (time_quantum <= 0) {
            printf("Error: Invalid time quantum\n");
            return 1;
        }
    }
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║         ROUND ROBIN TEST PROGRAM                   ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    printf("\nInput file: %s\n", argv[1]);
    printf("Time Quantum: %d\n", time_quantum);
    printf("\nInput Processes:\n");
    printf("PID\tAT\tBT\tPriority\n");
    printf("────────────────────────\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               processes[i].ProcessId,
               processes[i].ArrivalTime,
               processes[i].BurstTime,
               processes[i].Priority);
    }
    printf("\n");
    
    // Run Round Robin
    round_robin(processes, n, time_quantum);
    
    // Display results
    float avg_wt, avg_tat, avg_rt;
    calculate_avg_metrics(processes, n, &avg_wt, &avg_tat, &avg_rt);
    
    char title[100];
    snprintf(title, sizeof(title), "Round Robin (Time Quantum = %d)", time_quantum);
    display_results(processes, n, title);
    
    // Display Gantt chart
    display_gantt_chart(processes, n);
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║         TEST COMPLETED SUCCESSFULLY                ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    
    return 0;
}