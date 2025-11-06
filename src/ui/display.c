#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

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
    int pid = pr->pid ? pr->pid : 0;
    int at = pr->arrival_time ? pr->arrival_time : pr->ArrivalTime;
    int bt = pr->burst_time ? pr->burst_time : pr->BurstTime;
    int pri = pr->priority ? pr->priority : pr->Priority;

    int ct = pr->completion_time ? pr->completion_time : pr->CompletionTime;
    int tat = pr->turnaround_time ? pr->turnaround_time : pr->TurnaroundTime;
    int wt = pr->waiting_time ? pr->waiting_time : pr->WaitingTime;
    int rt = pr->response_time ? pr->response_time : pr->ResponseTime;

    printf("| %3d | %3d | %3d | %8d | %3d | %3d | %3d | %3d |\n",
           pid, at, bt, pri, ct, tat, wt, rt);
}

static void print_table_footer(void) {
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
}

void display_results(Process p[], int n, const char *algo) {
    printf("\n%s=== %s Scheduling Results ===%s\n", ANSI_CYAN, algo, ANSI_RESET);
    print_table_header();

    long sum_wt = 0, sum_tat = 0, sum_rt = 0; int counted_rt = 0;
    for (int i = 0; i < n; ++i) {
        print_row(&p[i]);
        // Sum with either field set
        int wt = p[i].waiting_time ? p[i].waiting_time : p[i].WaitingTime;
        int tat = p[i].turnaround_time ? p[i].turnaround_time : p[i].TurnaroundTime;
        int rt = p[i].response_time ? p[i].response_time : p[i].ResponseTime;
        sum_wt += wt; sum_tat += tat;
        if (rt >= 0) { sum_rt += rt; counted_rt++; }
    }

    print_table_footer();

    double avg_wt = n ? (double)sum_wt / n : 0.0;
    double avg_tat = n ? (double)sum_tat / n : 0.0;
    double avg_rt = counted_rt ? (double)sum_rt / counted_rt : 0.0;

    printf("Average Waiting Time    : %.2f\n", avg_wt);
    printf("Average Turnaround Time : %.2f\n", avg_tat);
    printf("Average Response Time   : %.2f\n", avg_rt);
}

void display_gantt_chart(Process p[], int n) {
    if (n <= 0) return;
    printf("\nGantt Chart (order of PIDs as given):\n");
    for (int i = 0; i < n; ++i) printf("+----");
    printf("+\n");
    for (int i = 0; i < n; ++i) printf("| %2d ", p[i].pid);
    printf("|\n");
    for (int i = 0; i < n; ++i) printf("+----");
    printf("+\n");
}

void display_comparison(Process p[], int n) {
    (void)p; (void)n;
    printf("\nComparison view is a placeholder for now.\n");
}
