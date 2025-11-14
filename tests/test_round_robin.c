/**
 * @file test_round_robin.c
 * @brief Test program for Round Robin algorithm
 */

#include "../include/process.h"
#include "../include/algorithms.h"
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
    
    printf("Testing Round Robin with %d processes and time quantum = %d\n", n, time_quantum);
    printf("Input file: %s\n\n", argv[1]);
    
    // Print input
    printf("Input Processes:\n");
    printf("PID\tAT\tBT\tPriority\n");
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
    
    return 0;
}
