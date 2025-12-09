#include "../../include/display.h"
#include "../../include/process.h"
#include "../../include/algorithms.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    double avg_waiting_time;
    double avg_turnaround_time;
    double avg_response_time;
    double cpu_utilization;
    double throughput;
} AlgorithmMetrics;

static void copy_processes_internal(Process dest[], const Process src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

static void calculate_metrics(Process p[], int n, AlgorithmMetrics* metrics) {
    if (!p || n <= 0 || !metrics) return;
    long sum_wt = 0, sum_tat = 0, sum_rt = 0;
    int counted_rt = 0;
    int max_ct = 0;
    int total_bt = 0;
    for (int i = 0; i < n; i++) {
        sum_wt += p[i].WaitingTime;
        sum_tat += p[i].TurnaroundTime;
        if (p[i].ResponseTime >= 0) {
            sum_rt += p[i].ResponseTime;
            counted_rt++;
        }
        if (p[i].CompletionTime > max_ct) max_ct = p[i].CompletionTime;
        total_bt += p[i].BurstTime;
    }
    metrics->avg_waiting_time = n > 0 ? (double)sum_wt / n : 0.0;
    metrics->avg_turnaround_time = n > 0 ? (double)sum_tat / n : 0.0;
    metrics->avg_response_time = counted_rt > 0 ? (double)sum_rt / counted_rt : 0.0;
    metrics->cpu_utilization = max_ct > 0 ? (double)total_bt / max_ct * 100.0 : 0.0;
    metrics->throughput = max_ct > 0 ? (double)n / max_ct : 0.0;
}

void display_comparison(Process original[], int n, int time_quantum) {
    if (!original || n <= 0) return;

    print_box_header("ALGORITHM COMPARISON");

    Process processes[6][MAX_PROCESSES];
    AlgorithmMetrics metrics[6];
    const char* algo_names[] = { "FCFS", "SJF", "SRTF", "Priority NP", "Priority P", "Round Robin" };

    printf("Running all algorithms...\n");

    // 1. FCFS
    copy_processes_internal(processes[0], original, n);
    fcfs(processes[0], n);
    strcpy(metrics[0].name, algo_names[0]);
    calculate_metrics(processes[0], n, &metrics[0]);

    // 2. SJF
    copy_processes_internal(processes[1], original, n);
    sjf(processes[1], n);
    strcpy(metrics[1].name, algo_names[1]);
    calculate_metrics(processes[1], n, &metrics[1]);

    // 3. SRTF
    copy_processes_internal(processes[2], original, n);
    srtf(processes[2], n);
    strcpy(metrics[2].name, algo_names[2]);
    calculate_metrics(processes[2], n, &metrics[2]);

    // 4. Priority NP
    copy_processes_internal(processes[3], original, n);
    priority_non_preemptive(processes[3], n);
    strcpy(metrics[3].name, algo_names[3]);
    calculate_metrics(processes[3], n, &metrics[3]);

    // 5. Priority P
    copy_processes_internal(processes[4], original, n);
    priority_preemptive(processes[4], n);
    strcpy(metrics[4].name, algo_names[4]);
    calculate_metrics(processes[4], n, &metrics[4]);

    // 6. Round Robin
    copy_processes_internal(processes[5], original, n);
    round_robin(processes[5], n, time_quantum);
    strcpy(metrics[5].name, algo_names[5]);
    calculate_metrics(processes[5], n, &metrics[5]);

    // Print Table
    // Sửa lỗi gọi hàm print_separator: thêm tham số 100, '='
    print_separator(100, '=');
    printf("| %-14s | %8s | %8s | %8s | %7s | %9s |\n", "Algorithm", "Avg WT", "Avg TAT", "Avg RT", "CPU %", "Throuput");
    print_separator(100, '-');

    for (int i = 0; i < 6; i++) {
        printf("| %-14s | %8.2f | %8.2f | %8.2f | %7.2f%%| %9.4f |\n",
            metrics[i].name,
            metrics[i].avg_waiting_time,
            metrics[i].avg_turnaround_time,
            metrics[i].avg_response_time,
            metrics[i].cpu_utilization,
            metrics[i].throughput);
    }
    print_separator(100, '=');
    printf("\n");
}