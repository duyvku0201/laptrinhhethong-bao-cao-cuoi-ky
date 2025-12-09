#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "process.h"
#include "display.h"
#include "utils.h"

static void print_table_header(void) {
    printf("\n╔═════╦═════╦═════╦══════════╦═════╦═════╦═════╦═════╗\n");
    printf("║ %sPID%s ║ %s AT%s ║ %s BT%s ║ %sPriority%s ║ %s CT%s ║ %sTAT%s ║ %s WT%s ║ %s RT%s ║\n",
           ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET,
           ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET,
           ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET);
    printf("╠═════╬═════╬═════╬══════════╬═════╬═════╬═════╬═════╣\n");
}

static void print_row(const Process *pr) {
    printf("║ %3d ║ %3d ║ %3d ║ %8d ║ %3d ║ %3d ║ %3d ║ %3d ║\n",
           pr->ProcessId, pr->ArrivalTime, pr->BurstTime, pr->Priority,
           pr->CompletionTime, pr->TurnaroundTime, pr->WaitingTime, pr->ResponseTime);
}

static void print_table_footer(void) {
    printf("╚═════╩═════╩═════╩══════════╩═════╩═════╩═════╩═════╝\n");
}

void display_results(Process p[], int n, const char *algo) {
    if (!p || n <= 0) return;
    
    printf("\n");
    print_box_header(algo);
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

    // Calculate CPU Utilization and Throughput
    int max_ct = 0, total_bt = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].CompletionTime > max_ct) max_ct = p[i].CompletionTime;
        total_bt += p[i].BurstTime;
    }
    double cpu_util = max_ct > 0 ? (double)total_bt / max_ct * 100.0 : 0.0;
    double throughput = max_ct > 0 ? (double)n / max_ct : 0.0;
    
    // Display metrics in a nice box with proper alignment
    printf("\n%s┌──────────────────────────────────────────────────┐%s\n", ANSI_CYAN, ANSI_RESET);
    printf("%s│%s %sPerformance Metrics%s                          %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s├──────────────────────────────────────────────────┤%s\n", ANSI_CYAN, ANSI_RESET);
    printf("%s│%s Average Waiting Time    : %s%-20.2f%s %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_GREEN, avg_wt, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s│%s Average Turnaround Time : %s%-20.2f%s %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_GREEN, avg_tat, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s│%s Average Response Time   : %s%-20.2f%s %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_GREEN, avg_rt, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s│%s Min/Max Waiting Time    : %s%-3d / %-14d%s %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_YELLOW, min_wt, max_wt, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s│%s Min/Max Turnaround Time : %s%-3d / %-14d%s %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_YELLOW, min_tat, max_tat, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s│%s CPU Utilization         : %s%-19.2f%%%s %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_MAGENTA, cpu_util, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s│%s Throughput              : %s%-6.4f proc/time%s   %s│%s\n", ANSI_CYAN, ANSI_RESET, ANSI_MAGENTA, throughput, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s└──────────────────────────────────────────────────┘%s\n", ANSI_CYAN, ANSI_RESET);
}

// display_gantt_chart and display_comparison are implemented in gantt.c and comparison.c
