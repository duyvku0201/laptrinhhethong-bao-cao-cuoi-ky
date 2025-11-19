#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "process.h"
#include "display.h"
#include "utils.h"

static void print_table_header(void) {
    printf("\n================================================================================\n");
    printf("%s%40s%s\n", ANSI_BOLD, "Scheduling Results", ANSI_RESET);
    printf("================================================================================\n");
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
    printf("| PID |  AT |  BT | Priority |  CT | TAT |  WT |  RT |\n");
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
}

static void print_row(const Process *pr) {
    // Prefer numeric fields when available (pid/arrival_time/etc.)
    int pid = pr->ProcessId ? pr->ProcessId : 0;
    int at = pr->ArrivalTime ? pr->ArrivalTime : pr->ArrivalTime;
    int bt = pr->BurstTime ? pr->BurstTime : pr->BurstTime;
    int pri = pr->Priority ? pr->Priority : pr->Priority;

    int ct = pr->CompletionTime ? pr->CompletionTime : pr->CompletionTime;
    int tat = pr->TurnaroundTime ? pr->TurnaroundTime : pr->TurnaroundTime;
    int wt = pr->WaitingTime ? pr->WaitingTime : pr->WaitingTime;
    int rt = pr->ResponseTime ? pr->ResponseTime : pr->ResponseTime;

    printf("| %3d | %3d | %3d | %8d | %3d | %3d | %3d | %3d |\n",
           pid, at, bt, pri, ct, tat, wt, rt);
}

static void print_table_footer(void) {
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
}

void display_results(Process p[], int n, const char *algo) {
    if (!p || n <= 0) return;
    
    printf("\n%s=== %s Scheduling Results ===%s\n", ANSI_CYAN, algo, ANSI_RESET);
    print_table_header();

    long sum_wt = 0, sum_tat = 0, sum_rt = 0; 
    int counted_rt = 0;
    int min_wt = INT_MAX, max_wt = 0;
    int min_tat = INT_MAX, max_tat = 0;
    
    for (int i = 0; i < n; ++i) {
        print_row(&p[i]);
        
        int wt = p[i].WaitingTime;
        int tat = p[i].TurnaroundTime;
        int rt = p[i].ResponseTime;
        
        sum_wt += wt; 
        sum_tat += tat;
        
        if (wt < min_wt) min_wt = wt;
        if (wt > max_wt) max_wt = wt;
        if (tat < min_tat) min_tat = tat;
        if (tat > max_tat) max_tat = tat;
        
        if (rt >= 0) { 
            sum_rt += rt; 
            counted_rt++; 
        }
    }

    print_table_footer();

    double avg_wt = n ? (double)sum_wt / n : 0.0;
    double avg_tat = n ? (double)sum_tat / n : 0.0;
    double avg_rt = counted_rt ? (double)sum_rt / counted_rt : 0.0;

    printf("Average Waiting Time    : %.2f\n", avg_wt);
    printf("Average Turnaround Time : %.2f\n", avg_tat);
    printf("Average Response Time   : %.2f\n", avg_rt);
    printf("Min/Max Waiting Time    : %d / %d\n", min_wt, max_wt);
    printf("Min/Max Turnaround Time : %d / %d\n", min_tat, max_tat);
    
    // Calculate CPU Utilization and Throughput
    if (n > 0) {
        int max_ct = 0;
        int total_bt = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].CompletionTime > max_ct) max_ct = p[i].CompletionTime;
            total_bt += p[i].BurstTime;
        }
        double cpu_util = max_ct > 0 ? (double)total_bt / max_ct * 100.0 : 0.0;
        double throughput = max_ct > 0 ? (double)n / max_ct : 0.0;
        
        printf("CPU Utilization         : %.2f%%\n", cpu_util);
        printf("Throughput              : %.4f processes/unit time\n", throughput);
    }
}

/**
 * @brief Display results with colored output for better visualization
 */
void display_results_colored(Process p[], int n, const char *algo) {
    if (!p || n <= 0) return;
    
    printf("\n%s%s=== %s Scheduling Results ===%s\n", 
           ANSI_BOLD, ANSI_CYAN, algo, ANSI_RESET);
    print_table_header();

    long sum_wt = 0, sum_tat = 0, sum_rt = 0; 
    int counted_rt = 0;
    int min_wt = INT_MAX, max_wt = 0;
    int min_tat = INT_MAX, max_tat = 0;
    
    for (int i = 0; i < n; ++i) {
        print_row(&p[i]);
        
        int wt = p[i].WaitingTime;
        int tat = p[i].TurnaroundTime;
        int rt = p[i].ResponseTime;
        
        sum_wt += wt; 
        sum_tat += tat;
        
        if (wt < min_wt) min_wt = wt;
        if (wt > max_wt) max_wt = wt;
        if (tat < min_tat) min_tat = tat;
        if (tat > max_tat) max_tat = tat;
        
        if (rt >= 0) { 
            sum_rt += rt; 
            counted_rt++; 
        }
    }

    print_table_footer();

    double avg_wt = n ? (double)sum_wt / n : 0.0;
    double avg_tat = n ? (double)sum_tat / n : 0.0;
    double avg_rt = counted_rt ? (double)sum_rt / counted_rt : 0.0;

    printf("%sAverage Waiting Time    : %.2f%s\n", ANSI_GREEN, avg_wt, ANSI_RESET);
    printf("%sAverage Turnaround Time : %.2f%s\n", ANSI_GREEN, avg_tat, ANSI_RESET);
    printf("%sAverage Response Time   : %.2f%s\n", ANSI_GREEN, avg_rt, ANSI_RESET);
    printf("%sMin/Max Waiting Time    : %d / %d%s\n", ANSI_YELLOW, min_wt, max_wt, ANSI_RESET);
    printf("%sMin/Max Turnaround Time : %d / %d%s\n", ANSI_YELLOW, min_tat, max_tat, ANSI_RESET);
    
    // Calculate CPU Utilization and Throughput
    if (n > 0) {
        int max_ct = 0;
        int total_bt = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].CompletionTime > max_ct) max_ct = p[i].CompletionTime;
            total_bt += p[i].BurstTime;
        }
        double cpu_util = max_ct > 0 ? (double)total_bt / max_ct * 100.0 : 0.0;
        double throughput = max_ct > 0 ? (double)n / max_ct : 0.0;
        
        printf("%sCPU Utilization         : %.2f%%%s\n", ANSI_CYAN, cpu_util, ANSI_RESET);
        printf("%sThroughput              : %.4f processes/unit time%s\n", 
               ANSI_CYAN, throughput, ANSI_RESET);
    }
}

// display_gantt_chart and display_comparison are implemented in gantt.c and comparison.c
// Do NOT implement stubs here to avoid multiple definition error
