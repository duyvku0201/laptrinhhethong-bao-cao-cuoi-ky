/**
 * @file comparison.c
 * @brief Algorithm comparison functionality
 * @author Team CPU Scheduling
 */

#include "display.h"
#include "process.h"
#include "algorithms.h"
#include "utils.h"
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
    
    // Run all algorithms and display their individual results
    printf("%sRunning all algorithms...%s\n\n", ANSI_YELLOW, ANSI_RESET);
    
    // 1. FCFS
    copy_processes(processes[0], original, n);
    fcfs(processes[0], n);
    strcpy(metrics[0].name, algo_names[0]);
    calculate_metrics(processes[0], n, &metrics[0]);
    display_results(processes[0], n, algo_names[0]);
    display_gantt_chart(processes[0], n);
    
    // 2. SJF
    copy_processes(processes[1], original, n);
    sjf(processes[1], n);
    strcpy(metrics[1].name, algo_names[1]);
    calculate_metrics(processes[1], n, &metrics[1]);
    display_results(processes[1], n, algo_names[1]);
    display_gantt_chart(processes[1], n);
    
    // 3. SRTF
    copy_processes(processes[2], original, n);
    srtf(processes[2], n);
    strcpy(metrics[2].name, algo_names[2]);
    calculate_metrics(processes[2], n, &metrics[2]);
    display_results(processes[2], n, algo_names[2]);
    display_gantt_chart(processes[2], n);
    
    // 4. Priority Non-Preemptive
    copy_processes(processes[3], original, n);
    priority_non_preemptive(processes[3], n);
    strcpy(metrics[3].name, algo_names[3]);
    calculate_metrics(processes[3], n, &metrics[3]);
    display_results(processes[3], n, algo_names[3]);
    display_gantt_chart(processes[3], n);
    
    // 5. Priority Preemptive
    copy_processes(processes[4], original, n);
    priority_preemptive(processes[4], n);
    strcpy(metrics[4].name, algo_names[4]);
    calculate_metrics(processes[4], n, &metrics[4]);
    display_results(processes[4], n, algo_names[4]);
    display_gantt_chart(processes[4], n);
    
    // 6. Round Robin
    copy_processes(processes[5], original, n);
    round_robin(processes[5], n, time_quantum);
    strcpy(metrics[5].name, algo_names[5]);
    calculate_metrics(processes[5], n, &metrics[5]);
    
    char rr_title[100];
    snprintf(rr_title, sizeof(rr_title), "%s (Time Quantum = %d)", algo_names[5], time_quantum);
    display_results(processes[5], n, rr_title);
    display_gantt_chart(processes[5], n);
    
    printf("\n");
    print_box_header("COMPARISON SUMMARY");
    
    // Print comparison table
    printf("╔════════════════╦══════════╦══════════╦══════════╦══════════╦═══════════╗\n");
    printf("║ %sAlgorithm%s      ║ %sAvg WT%s   ║ %sAvg TAT%s  ║ %sAvg RT%s   ║ %sCPU Util%s ║ %sThroughput%s║\n",
           ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET,
           ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_BOLD, ANSI_RESET);
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
    
    // Highlight best algorithms in a box
    printf("%s┌──────────────────────────────────────────────────┐%s\n", ANSI_GREEN, ANSI_RESET);
    printf("%s│%s %sBest Performing Algorithms%s                  %s│%s\n", ANSI_GREEN, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_GREEN, ANSI_RESET);
    printf("%s├──────────────────────────────────────────────────┤%s\n", ANSI_GREEN, ANSI_RESET);
    printf("%s│%s ★ Lowest Avg Waiting Time    : %s%-11s%s (%.2f)  %s│%s\n", 
           ANSI_GREEN, ANSI_RESET, ANSI_BOLD ANSI_YELLOW, metrics[best_wt_idx].name, ANSI_RESET, min_wt, ANSI_GREEN, ANSI_RESET);
    printf("%s│%s ★ Lowest Avg Turnaround Time : %s%-11s%s (%.2f)  %s│%s\n", 
           ANSI_GREEN, ANSI_RESET, ANSI_BOLD ANSI_YELLOW, metrics[best_tat_idx].name, ANSI_RESET, min_tat, ANSI_GREEN, ANSI_RESET);
    printf("%s│%s ★ Lowest Avg Response Time   : %s%-11s%s (%.2f)  %s│%s\n", 
           ANSI_GREEN, ANSI_RESET, ANSI_BOLD ANSI_YELLOW, metrics[best_rt_idx].name, ANSI_RESET, min_rt, ANSI_GREEN, ANSI_RESET);
    printf("%s└──────────────────────────────────────────────────┘%s\n", ANSI_GREEN, ANSI_RESET);
    
    // Print bar chart for average waiting time
    printf("\n%s┌──────────────────────────────────────────────────────────────────────┐%s\n", ANSI_CYAN, ANSI_RESET);
    printf("%s│%s %sAvg Waiting Time Comparison (Bar Chart)%s                       %s│%s\n", 
           ANSI_CYAN, ANSI_RESET, ANSI_BOLD, ANSI_RESET, ANSI_CYAN, ANSI_RESET);
    printf("%s├──────────────────────────────────────────────────────────────────────┤%s\n", ANSI_CYAN, ANSI_RESET);
    
    double max_wt = 0;
    for (int i = 0; i < 6; i++) {
        if (metrics[i].avg_waiting_time > max_wt) {
            max_wt = metrics[i].avg_waiting_time;
        }
    }
    
    for (int i = 0; i < 6; i++) {
        printf("%s│%s %-12s │ ", ANSI_CYAN, ANSI_RESET, metrics[i].name);
        int bar_len = max_wt > 0 ? (int)((metrics[i].avg_waiting_time / max_wt) * 40) : 0;
        
        const char *color = (i == best_wt_idx) ? ANSI_GREEN : ANSI_BLUE;
        printf("%s", color);
        for (int j = 0; j < bar_len; j++) {
            printf("█");
        }
        printf("%s", ANSI_RESET);
        
        // Calculate how many spaces we need for proper alignment
        // Format: bars + space + number + spaces to reach column 70
        char value_str[20];
        snprintf(value_str, sizeof(value_str), " %.2f", metrics[i].avg_waiting_time);
        int value_len = strlen(value_str);
        int total_content = bar_len + value_len;
        int padding = 52 - total_content; // 52 is the content width before the right border
        
        printf("%s", value_str);
        for (int j = 0; j < padding; j++) printf(" ");
        printf("%s│%s\n", ANSI_CYAN, ANSI_RESET);
    }
    
    printf("%s└──────────────────────────────────────────────────────────────────────┘%s\n", ANSI_CYAN, ANSI_RESET);
}


