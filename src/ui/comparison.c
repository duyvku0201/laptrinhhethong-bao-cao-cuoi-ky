/**
 * @file comparison.c
 * @brief Algorithm comparison functionality
 * @author Team CPU Scheduling
 */

#include "../../include/display.h"
#include "../../include/process.h"
#include "../../include/algorithms.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <string.h>

// Struct để lưu metrics của mỗi thuật toán
typedef struct {
    char name[50];
    double avg_waiting_time;
    double avg_turnaround_time;
    double avg_response_time;
    double cpu_utilization;
    double throughput;
} AlgorithmMetrics;

/**
 * @brief Copy process array để test các thuật toán khác nhau
 */
static void copy_processes(Process dest[], const Process src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

/**
 * @brief Tính metrics từ process array
 */
static void calculate_metrics(Process p[], int n, AlgorithmMetrics *metrics) {
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
        if (p[i].CompletionTime > max_ct) {
            max_ct = p[i].CompletionTime;
        }
        total_bt += p[i].BurstTime;
    }
    
    metrics->avg_waiting_time = n > 0 ? (double)sum_wt / n : 0.0;
    metrics->avg_turnaround_time = n > 0 ? (double)sum_tat / n : 0.0;
    metrics->avg_response_time = counted_rt > 0 ? (double)sum_rt / counted_rt : 0.0;
    metrics->cpu_utilization = max_ct > 0 ? (double)total_bt / max_ct * 100.0 : 0.0;
    metrics->throughput = max_ct > 0 ? (double)n / max_ct : 0.0;
}

/**
 * @brief Display comparison table
 */
void display_comparison(Process original[], int n, int time_quantum) {
    if (!original || n <= 0) {
        printf("Error: Invalid input for comparison\n");
        return;
    }
    
    printf("\n");
    print_box_header("ALGORITHM COMPARISON");
    printf("\n");
    
    // Arrays to store results from each algorithm
    Process processes[6][MAX_PROCESSES];
    AlgorithmMetrics metrics[6];
    const char *algo_names[] = {
        "FCFS",
        "SJF", 
        "SRTF",
        "Priority NP",
        "Priority P",
        "Round Robin"
    };
    
    // Run all algorithms
    printf("Running all algorithms...\n\n");
    
    // 1. FCFS
    copy_processes(processes[0], original, n);
    fcfs(processes[0], n);
    strcpy(metrics[0].name, algo_names[0]);
    calculate_metrics(processes[0], n, &metrics[0]);
    
    // 2. SJF
    copy_processes(processes[1], original, n);
    sjf(processes[1], n);
    strcpy(metrics[1].name, algo_names[1]);
    calculate_metrics(processes[1], n, &metrics[1]);
    
    // 3. SRTF
    copy_processes(processes[2], original, n);
    srtf(processes[2], n);
    strcpy(metrics[2].name, algo_names[2]);
    calculate_metrics(processes[2], n, &metrics[2]);
    
    // 4. Priority Non-Preemptive
    copy_processes(processes[3], original, n);
    priority_non_preemptive(processes[3], n);
    strcpy(metrics[3].name, algo_names[3]);
    calculate_metrics(processes[3], n, &metrics[3]);
    
    // 5. Priority Preemptive
    copy_processes(processes[4], original, n);
    priority_preemptive(processes[4], n);
    strcpy(metrics[4].name, algo_names[4]);
    calculate_metrics(processes[4], n, &metrics[4]);
    
    // 6. Round Robin
    copy_processes(processes[5], original, n);
    round_robin(processes[5], n, time_quantum);
    strcpy(metrics[5].name, algo_names[5]);
    calculate_metrics(processes[5], n, &metrics[5]);
    
    // Print comparison table
    printf("╔════════════════╦══════════╦══════════╦══════════╦══════════╦═══════════╗\n");
    printf("║   Algorithm    ║ Avg WT   ║ Avg TAT  ║ Avg RT   ║ CPU Util ║ Throughput║\n");
    printf("╠════════════════╬══════════╬══════════╬══════════╬══════════╬═══════════╣\n");
    
    int best_wt_idx = 0, best_tat_idx = 0, best_rt_idx = 0;
    double min_wt = metrics[0].avg_waiting_time;
    double min_tat = metrics[0].avg_turnaround_time;
    double min_rt = metrics[0].avg_response_time;
    
    for (int i = 0; i < 6; i++) {
        if (metrics[i].avg_waiting_time < min_wt) {
            min_wt = metrics[i].avg_waiting_time;
            best_wt_idx = i;
        }
        if (metrics[i].avg_turnaround_time < min_tat) {
            min_tat = metrics[i].avg_turnaround_time;
            best_tat_idx = i;
        }
        if (metrics[i].avg_response_time < min_rt) {
            min_rt = metrics[i].avg_response_time;
            best_rt_idx = i;
        }
        
        printf("║ %-14s ║ %8.2f ║ %8.2f ║ %8.2f ║ %7.2f%% ║ %9.4f ║\n",
               metrics[i].name,
               metrics[i].avg_waiting_time,
               metrics[i].avg_turnaround_time,
               metrics[i].avg_response_time,
               metrics[i].cpu_utilization,
               metrics[i].throughput);
    }
    
    printf("╚════════════════╩══════════╩══════════╩══════════╩══════════╩═══════════╝\n\n");
    
    // Highlight best algorithms
    printf("%sBest Algorithm for:%s\n", ANSI_BOLD ANSI_GREEN, ANSI_RESET);
    printf("  • Lowest Avg Waiting Time    : %s%s%s (%.2f)\n", 
           ANSI_YELLOW, metrics[best_wt_idx].name, ANSI_RESET, min_wt);
    printf("  • Lowest Avg Turnaround Time : %s%s%s (%.2f)\n", 
           ANSI_YELLOW, metrics[best_tat_idx].name, ANSI_RESET, min_tat);
    printf("  • Lowest Avg Response Time   : %s%s%s (%.2f)\n", 
           ANSI_YELLOW, metrics[best_rt_idx].name, ANSI_RESET, min_rt);
    
    // Print bar chart for average waiting time
    printf("\n%sAverage Waiting Time Comparison (Bar Chart):%s\n", 
           ANSI_BOLD ANSI_CYAN, ANSI_RESET);
    
    double max_wt = 0;
    for (int i = 0; i < 6; i++) {
        if (metrics[i].avg_waiting_time > max_wt) {
            max_wt = metrics[i].avg_waiting_time;
        }
    }
    
    for (int i = 0; i < 6; i++) {
        printf("%-14s │ ", metrics[i].name);
        int bar_len = max_wt > 0 ? (int)((metrics[i].avg_waiting_time / max_wt) * 40) : 0;
        
        // Color bars
        const char *color = (i == best_wt_idx) ? ANSI_GREEN : ANSI_BLUE;
        printf("%s", color);
        for (int j = 0; j < bar_len; j++) {
            printf("█");
        }
        printf("%s %.2f\n", ANSI_RESET, metrics[i].avg_waiting_time);
    }
    
    printf("\n");
    print_separator();
}

/**
 * @brief Display comparison with colored output
 */
void display_comparison_colored(Process original[], int n, int time_quantum) {
    // For now, just call the regular comparison (it already has colors)
    display_comparison(original, n, time_quantum);
}
