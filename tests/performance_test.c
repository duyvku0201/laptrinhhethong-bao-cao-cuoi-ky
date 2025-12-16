/**
 * @file performance_test.c
 * @brief Performance testing suite for CPU scheduling algorithms
 * @description Tests algorithms against expected outputs and measures performance
 */

#include "../include/process.h"
#include "../include/algorithms.h"
#include "../include/metrics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LINE 256
#define EPSILON 0.01  // For floating point comparison

// Structure to hold expected results
typedef struct {
    int pid;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} ExpectedResult;

typedef struct {
    ExpectedResult processes[MAX_PROCESSES];
    int count;
    float avg_wt;
    float avg_tat;
    float avg_rt;
} ExpectedOutput;

// Color codes for test results
#define COLOR_PASS "\033[32m"  // Green
#define COLOR_FAIL "\033[31m"  // Red
#define COLOR_INFO "\033[36m"  // Cyan
#define COLOR_WARN "\033[33m"  // Yellow
#define COLOR_RESET "\033[0m"

// Global counters
static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;

/**
 * @brief Read processes from input file
 */
int read_test_input(const char *filename, Process processes[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("%sError: Cannot open %s%s\n", COLOR_FAIL, filename, COLOR_RESET);
        return -1;
    }
    
    int n;
    if (fscanf(file, "%d", &n) != 1) {
        fclose(file);
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d %d %d %d",
                   &processes[i].ProcessId,
                   &processes[i].ArrivalTime,
                   &processes[i].BurstTime,
                   &processes[i].Priority) != 4) {
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return n;
}

/**
 * @brief Read expected output from file
 */
bool read_expected_output(const char *filename, ExpectedOutput *expected) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("%sWarning: Cannot open expected output %s%s\n", 
               COLOR_WARN, filename, COLOR_RESET);
        return false;
    }
    
    char line[MAX_LINE];
    expected->count = 0;
    
    // Skip header lines until we find the table
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "PID") && strstr(line, "CT")) {
            break;
        }
    }
    
    // Skip separator line
    fgets(line, sizeof(line), file);
    
    // Read process results
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Average") || strstr(line, "===")) {
            break;
        }
        
        int idx = expected->count;
        if (sscanf(line, "%d %*d %*d %*d %d %d %d %d",
                   &expected->processes[idx].pid,
                   &expected->processes[idx].completion_time,
                   &expected->processes[idx].turnaround_time,
                   &expected->processes[idx].waiting_time,
                   &expected->processes[idx].response_time) == 5) {
            expected->count++;
        }
    }
    
    // Read averages
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Average Waiting Time")) {
            sscanf(line, "Average Waiting Time : %f", &expected->avg_wt);
        } else if (strstr(line, "Average Turnaround Time")) {
            sscanf(line, "Average Turnaround Time : %f", &expected->avg_tat);
        } else if (strstr(line, "Average Response Time")) {
            sscanf(line, "Average Response Time : %f", &expected->avg_rt);
        }
    }
    
    fclose(file);
    return expected->count > 0;
}

/**
 * @brief Compare floating point numbers with tolerance
 */
bool float_equals(float a, float b) {
    return fabs(a - b) < EPSILON;
}

/**
 * @brief Find expected result for a process
 */
ExpectedResult* find_expected_result(ExpectedOutput *expected, int pid) {
    for (int i = 0; i < expected->count; i++) {
        if (expected->processes[i].pid == pid) {
            return &expected->processes[i];
        }
    }
    return NULL;
}

/**
 * @brief Verify results against expected output
 */
bool verify_results(Process actual[], int n, ExpectedOutput *expected, const char *test_name) {
    bool all_passed = true;
    
    printf("\n%s=== Verifying %s ===%s\n", COLOR_INFO, test_name, COLOR_RESET);
    
    // Check each process
    for (int i = 0; i < n; i++) {
        ExpectedResult *exp = find_expected_result(expected, actual[i].ProcessId);
        if (!exp) {
            printf("%s  ✗ Process P%d: Not found in expected output%s\n",
                   COLOR_FAIL, actual[i].ProcessId, COLOR_RESET);
            all_passed = false;
            continue;
        }
        
        bool process_passed = true;
        
        // Check completion time
        if (actual[i].CompletionTime != exp->completion_time) {
            printf("%s  ✗ P%d CT: Expected %d, Got %d%s\n",
                   COLOR_FAIL, actual[i].ProcessId, exp->completion_time,
                   actual[i].CompletionTime, COLOR_RESET);
            process_passed = false;
        }
        
        // Check turnaround time
        if (actual[i].TurnaroundTime != exp->turnaround_time) {
            printf("%s  ✗ P%d TAT: Expected %d, Got %d%s\n",
                   COLOR_FAIL, actual[i].ProcessId, exp->turnaround_time,
                   actual[i].TurnaroundTime, COLOR_RESET);
            process_passed = false;
        }
        
        // Check waiting time
        if (actual[i].WaitingTime != exp->waiting_time) {
            printf("%s  ✗ P%d WT: Expected %d, Got %d%s\n",
                   COLOR_FAIL, actual[i].ProcessId, exp->waiting_time,
                   actual[i].WaitingTime, COLOR_RESET);
            process_passed = false;
        }
        
        // Check response time
        if (actual[i].ResponseTime != exp->response_time) {
            printf("%s  ✗ P%d RT: Expected %d, Got %d%s\n",
                   COLOR_FAIL, actual[i].ProcessId, exp->response_time,
                   actual[i].ResponseTime, COLOR_RESET);
            process_passed = false;
        }
        
        if (process_passed) {
            printf("%s  ✓ P%d: All metrics correct%s\n",
                   COLOR_PASS, actual[i].ProcessId, COLOR_RESET);
        }
        
        all_passed = all_passed && process_passed;
    }
    
    // Check averages
    float actual_avg_wt = CalculateAverageWaitingTime(actual, n);
    float actual_avg_tat = CalculateAverageTurnaroundTime(actual, n);
    float actual_avg_rt = CalculateAverageResponseTime(actual, n);
    
    if (!float_equals(actual_avg_wt, expected->avg_wt)) {
        printf("%s  ✗ Avg WT: Expected %.2f, Got %.2f%s\n",
               COLOR_FAIL, expected->avg_wt, actual_avg_wt, COLOR_RESET);
        all_passed = false;
    } else {
        printf("%s  ✓ Avg WT: %.2f (correct)%s\n",
               COLOR_PASS, actual_avg_wt, COLOR_RESET);
    }
    
    if (!float_equals(actual_avg_tat, expected->avg_tat)) {
        printf("%s  ✗ Avg TAT: Expected %.2f, Got %.2f%s\n",
               COLOR_FAIL, expected->avg_tat, actual_avg_tat, COLOR_RESET);
        all_passed = false;
    } else {
        printf("%s  ✓ Avg TAT: %.2f (correct)%s\n",
               COLOR_PASS, actual_avg_tat, COLOR_RESET);
    }
    
    if (!float_equals(actual_avg_rt, expected->avg_rt)) {
        printf("%s  ✗ Avg RT: Expected %.2f, Got %.2f%s\n",
               COLOR_FAIL, expected->avg_rt, actual_avg_rt, COLOR_RESET);
        all_passed = false;
    } else {
        printf("%s  ✓ Avg RT: %.2f (correct)%s\n",
               COLOR_PASS, actual_avg_rt, COLOR_RESET);
    }
    
    return all_passed;
}

/**
 * @brief Run a single test case
 */
bool run_test(const char *algo_name, const char *input_file, const char *expected_file,
              void (*algorithm)(Process[], int)) {
    total_tests++;
    
    printf("\n%s" "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" "%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%sTest: %s - %s%s\n", COLOR_INFO, algo_name, input_file, COLOR_RESET);
    printf("%s" "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" "%s\n",
           COLOR_INFO, COLOR_RESET);
    
    // Read input
    Process processes[MAX_PROCESSES];
    int n = read_test_input(input_file, processes);
    
    if (n <= 0) {
        printf("%s✗ FAILED: Cannot read input file%s\n", COLOR_FAIL, COLOR_RESET);
        failed_tests++;
        return false;
    }
    
    // Read expected output
    ExpectedOutput expected;
    if (!read_expected_output(expected_file, &expected)) {
        printf("%s✗ FAILED: Cannot read expected output%s\n", COLOR_FAIL, COLOR_RESET);
        failed_tests++;
        return false;
    }
    
    // Run algorithm
    algorithm(processes, n);
    
    // Verify results
    char test_name[256];
    snprintf(test_name, sizeof(test_name), "%s - %s", algo_name, input_file);
    bool passed = verify_results(processes, n, &expected, test_name);
    
    if (passed) {
        printf("\n%s✓✓✓ TEST PASSED ✓✓✓%s\n", COLOR_PASS, COLOR_RESET);
        passed_tests++;
    } else {
        printf("\n%s✗✗✗ TEST FAILED ✗✗✗%s\n", COLOR_FAIL, COLOR_RESET);
        failed_tests++;
    }
    
    return passed;
}

/**
 * @brief Print test summary
 */
void print_summary() {
    printf("\n\n");
    printf("%s╔════════════════════════════════════════════════════════════╗%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s║                    TEST SUMMARY                            ║%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s╠════════════════════════════════════════════════════════════╣%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s║  Total Tests  : %-40d  ║%s\n",
           COLOR_INFO, total_tests, COLOR_RESET);
    printf("%s║  %sPassed Tests%s : %-40d  %s║%s\n",
           COLOR_INFO, COLOR_PASS, COLOR_INFO, passed_tests, COLOR_INFO, COLOR_RESET);
    printf("%s║  %sFailed Tests%s : %-40d  %s║%s\n",
           COLOR_INFO, COLOR_FAIL, COLOR_INFO, failed_tests, COLOR_INFO, COLOR_RESET);
    
    float success_rate = (total_tests > 0) ? 
                         (100.0f * passed_tests / total_tests) : 0.0f;
    printf("%s║  Success Rate : %.2f%%%-35s  ║%s\n",
           COLOR_INFO, success_rate, "", COLOR_RESET);
    printf("%s╚════════════════════════════════════════════════════════════╝%s\n",
           COLOR_INFO, COLOR_RESET);
    
    if (failed_tests == 0) {
        printf("\n%s🎉 ALL TESTS PASSED! 🎉%s\n\n", COLOR_PASS, COLOR_RESET);
    } else {
        printf("\n%s⚠ SOME TESTS FAILED ⚠%s\n\n", COLOR_FAIL, COLOR_RESET);
    }
}

/**
 * @brief Main function
 */
int main() {
    printf("\n");
    printf("%s╔══════════════════════════════════════════════════════════════╗%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s║         CPU SCHEDULING PERFORMANCE TEST SUITE                ║%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s╚══════════════════════════════════════════════════════════════╝%s\n",
           COLOR_INFO, COLOR_RESET);
    
    // ==================== FCFS Tests ====================
    printf("\n%s" "█████████████████████████████████████████████████████████████" "%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s                    FCFS ALGORITHM TESTS                        %s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s" "█████████████████████████████████████████████████████████████" "%s\n",
           COLOR_INFO, COLOR_RESET);
    
    run_test("FCFS", "tests/test_cases/test1.txt",
             "tests/expected_outputs/test1_fcfs_expected.txt", fcfs);
    
    run_test("FCFS", "tests/test_cases/test_fcfs_2.txt",
             "tests/expected_outputs/test2_fcfs_expected.txt", fcfs);
    
    run_test("FCFS", "tests/test_cases/test_fcfs_3.txt",
             "tests/expected_outputs/test3_fcfs_expected.txt", fcfs);
    
    run_test("FCFS", "tests/test_cases/test_complex.txt",
             "tests/expected_outputs/test_complex_fcfs_expected.txt", fcfs);
    
    run_test("FCFS", "tests/test_cases/test_edge_cases.txt",
             "tests/expected_outputs/test_edge_fcfs_expected.txt", fcfs);
    
    // ==================== Priority Non-Preemptive Tests ====================
    printf("\n%s" "█████████████████████████████████████████████████████████████" "%s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s          PRIORITY NON-PREEMPTIVE ALGORITHM TESTS              %s\n",
           COLOR_INFO, COLOR_RESET);
    printf("%s" "█████████████████████████████████████████████████████████████" "%s\n",
           COLOR_INFO, COLOR_RESET);
    
    run_test("Priority NP", "tests/test_cases/test_priority_np_1.txt",
             "tests/expected_outputs/test1_priority_np_expected.txt",
             priority_non_preemptive);
    
    run_test("Priority NP", "tests/test_cases/test_priority_np_2.txt",
             "tests/expected_outputs/test2_priority_np_expected.txt",
             priority_non_preemptive);
    
    run_test("Priority NP", "tests/test_cases/test_priority_np_3.txt",
             "tests/expected_outputs/test3_priority_np_expected.txt",
             priority_non_preemptive);
    
    run_test("Priority NP", "tests/test_cases/test_priority_np_4.txt",
             "tests/expected_outputs/test4_priority_np_expected.txt",
             priority_non_preemptive);
    
    run_test("Priority NP", "tests/test_cases/test_priority_np_5.txt",
             "tests/expected_outputs/test5_priority_np_expected.txt",
             priority_non_preemptive);
    
    // Print final summary
    print_summary();
    
    return (failed_tests == 0) ? 0 : 1;
}