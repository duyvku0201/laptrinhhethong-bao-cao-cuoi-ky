#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../../include/process.h"
#include "../../include/display.h"
#include "../../include/utils.h"

static void print_table_header(void) {
    print_separator(80, '='); // Đã sửa: thêm tham số
    printf("%s%40s%s\n", ANSI_BOLD, "Scheduling Results", ANSI_RESET);
    print_separator(80, '=');
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
    printf("| PID |  AT |  BT | Priority |  CT | TAT |  WT |  RT |\n");
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
}

static void print_row(const Process* pr) {
    printf("| %3d | %3d | %3d | %8d | %3d | %3d | %3d | %3d |\n",
        pr->ProcessId, pr->ArrivalTime, pr->BurstTime, pr->Priority,
        pr->CompletionTime, pr->TurnaroundTime, pr->WaitingTime, pr->ResponseTime);
}

static void print_table_footer(void) {
    printf("+-----+-----+-----+----------+-----+-----+-----+-----+\n");
}

void display_results(Process p[], int n, const char* algo) {
    if (!p || n <= 0) return;
    printf("\n=== %s Scheduling Results ===\n", algo);
    display_results_colored(p, n, algo);
}

void display_results_colored(Process p[], int n, const char* algo) {
    if (!p || n <= 0) return;

    // In tiêu đề không dùng unicode đặc biệt
    printf("\n--- %s Results ---\n", algo);
    print_table_header();

    long sum_wt = 0, sum_tat = 0, sum_rt = 0;
    int counted_rt = 0;

    for (int i = 0; i < n; ++i) {
        print_row(&p[i]);
        sum_wt += p[i].WaitingTime;
        sum_tat += p[i].TurnaroundTime;
        if (p[i].ResponseTime >= 0) {
            sum_rt += p[i].ResponseTime;
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
}