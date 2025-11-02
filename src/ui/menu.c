#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "process.h"
#include "algorithms.h"
#include "display.h"
#include "io.h"
#include "utils.h"

void show_menu() {
    printf("\n");
    printf("=========================================\n");
    printf("      CPU SCHEDULING ALGORITHMS         \n");
    printf("=========================================\n");
    printf("  1. FCFS (First Come First Serve)\n");
    printf("  2. SJF (Shortest Job First)\n");
    printf("  3. SRTF (Shortest Remaining Time First)\n");
    printf("  4. Priority - Non-preemptive\n");
    printf("  5. Priority - Preemptive\n");
    printf("  6. Round Robin\n");
    printf("-----------------------------------------\n");
    printf("  7. Compare All Algorithms\n");
    printf("  8. Save Results to File\n");
    printf("-----------------------------------------\n");
    printf("  0. Exit\n");
    printf("=========================================\n");
    printf("Enter your choice: ");
}

void run_scheduling(int choice, Process p[], int n) {
    Process temp[100];
    int tq;
    char filename[100];

    for (int i = 0; i < n; i++) temp[i] = p[i];

    switch (choice) {
    case 1:
        printf("\n========== FCFS Algorithm ==========\n");
        fcfs(temp, n);
        display_results(temp, n, "FCFS");
        display_gantt_chart(temp, n);
        break;

    case 2:
        printf("\n========== SJF Algorithm ==========\n");
        sjf(temp, n);
        display_results(temp, n, "SJF");
        display_gantt_chart(temp, n);
        break;

    case 3:
        printf("\n========== SRTF Algorithm ==========\n");
        srtf(temp, n);
        display_results(temp, n, "SRTF");
        break;

    case 4:
        printf("\n====== Priority Non-Preemptive ======\n");
        priority_non_preemptive(temp, n);
        display_results(temp, n, "Priority NP");
        display_gantt_chart(temp, n);
        break;

    case 5:
        printf("\n======== Priority Preemptive ========\n");
        priority_preemptive(temp, n);
        display_results(temp, n, "Priority P");
        break;

    case 6:
        printf("\n========= Round Robin Algorithm =====\n");
        printf("Enter time quantum: ");
        scanf("%d", &tq);
        if (tq <= 0) {
            printf("Error: Time quantum must be positive!\n");
            return;
        }
        round_robin(temp, n, tq);
        display_results(temp, n, "Round Robin");
        break;

    case 7:
        printf("\n======= Algorithm Comparison =========\n");
        display_comparison(p, n);
        break;

    case 8:
        printf("\nEnter filename to save results: ");
        scanf("%s", filename);
        write_to_file(filename, p, n, "Custom Save");
        break;

    default:
        printf("Invalid choice! Please try again.\n");
    }
}
