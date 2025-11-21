
#define _CRT_SECURE_NO_WARNINGS

/**
 * @file main.c
 * @brief Main entry point của chương trình
 */

#include "include/process.h"
#include "include/algorithms.h"
#include "include/io.h"
#include "include/display.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>

 /**
  * @brief Main function
  * Flow:
  * 1. Hiển thị header
  * 2. Đọc input (file hoặc keyboard)
  * 3. Hiển thị menu chọn algorithm
  * 4. Chạy algorithm được chọn
  * 5. Hiển thị kết quả
  * 6. Lặp lại hoặc exit
  */
int main() {
    // Khai báo biến
    Process processes[MAX_PROCESSES];  // Mảng processes
    Process original[MAX_PROCESSES];   // Backup để so sánh
    int n = 0;                         // Số processes
    int choice;                        // Lựa chọn của user
    int time_quantum;                  // Time quantum cho RR

    // BƯỚC 1: Hiển thị header
    print_header("CPU SCHEDULING ALGORITHMS SIMULATOR");

    printf("Welcome to CPU Scheduling Simulator!\n");
    printf("This program implements 6 scheduling algorithms:\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. SJF (Shortest Job First)\n");
    printf("3. SRTF (Shortest Remaining Time First)\n");
    printf("4. Priority (Non-Preemptive)\n");
    printf("5. Priority (Preemptive)\n");
    printf("6. Round Robin\n\n");

    // BƯỚC 2: Đọc input
    printf("How do you want to input process data?\n");
    printf("1. Read from file\n");
    printf("2. Enter from keyboard\n");
    printf("Enter choice [1-2]: ");

    int input_choice;
    scanf("%d", &input_choice);

    if (input_choice == 1) {
        // Đọc từ file
        char filename[256];
        printf("Enter filename (e.g., tests/test_cases/test1.txt): ");
        scanf("%s", filename);

        if (!read_from_file(filename, processes, &n)) {
            printf("Error reading file. Exiting.\n");
            return 1;
        }
    }
    else if (input_choice == 2) {
        // Đọc từ keyboard
        if (!read_from_keyboard(processes, &n)) {
            printf("Error reading input. Exiting.\n");
            return 1;
        }
    }
    else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    // Backup processes gốc
    copy_processes(original, processes, n);

    // BƯỚC 3: Main loop
    do {
        // Reset processes về trạng thái ban đầu
        copy_processes(processes, original, n);

        // Hiển thị menu
        choice = display_menu();

        // BƯỚC 4: Xử lý lựa chọn
        switch (choice) {
        case 1: // FCFS
            printf("\n--- Running FCFS Algorithm ---\n");
            fcfs(processes, n);
            display_results(processes, n, "FCFS");
            break;

        case 2: // SJF
            printf("\n--- Running SJF Algorithm ---\n");
            sjf(processes, n);
            display_results(processes, n, "SJF (Non-Preemptive)");
            break;

        case 3: // SRTF
            printf("\n--- Running SRTF Algorithm ---\n");
            srtf(processes, n);
            display_results(processes, n, "SRTF (Preemptive SJF)");
            break;

        case 4: // Priority NP
            printf("\n--- Running Priority (Non-Preemptive) Algorithm ---\n");
            priority_non_preemptive(processes, n);
            display_results(processes, n, "Priority (Non-Preemptive)");
            break;

        case 5: // Priority P
            printf("\n--- Running Priority (Preemptive) Algorithm ---\n");
            priority_preemptive(processes, n);
            display_results(processes, n, "Priority (Preemptive)");
            break;

        case 6: // Round Robin
            printf("\n--- Running Round Robin Algorithm ---\n");
            printf("Enter time quantum: ");
            scanf("%d", &time_quantum);

            if (!validate_time_quantum(time_quantum)) {
                printf("Invalid time quantum. Using default: %d\n",
                    DEFAULT_TIME_QUANTUM);
                time_quantum = DEFAULT_TIME_QUANTUM;
            }

            round_robin(processes, n, time_quantum);
            display_results(processes, n, "Round Robin");
            break;

        case 7: // Compare All
            printf("\n--- Comparing All Algorithms ---\n");
            display_comparison(original, n, DEFAULT_TIME_QUANTUM);
            break;

        case 8: // Exit
            printf("\nThank you for using CPU Scheduling Simulator!\n");
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

        // Pause để user đọc kết quả
        if (choice != 8) {
            wait_for_enter();
        }

    } while (choice != 8);

    return 0;
}