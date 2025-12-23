#define _CRT_SECURE_NO_WARNINGS

/**
 * @file main.c
 * @brief Main entry point của chương trình
 */

#define DEFAULT_TIME_QUANTUM 2

#include "process.h"
#include "algorithms.h"
#include "io.h"
#include "display.h"
#include "menu.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Thêm thư viện để so sánh chuỗi nếu cần

 /**
  * @brief Main function
  */
int main() {
    // Khai báo biến
    Process processes[MAX_PROCESSES];  // Mảng processes
    Process original[MAX_PROCESSES];   // Backup để so sánh
    int n = 0;                         // Số processes
    int choice;                        // Lựa chọn của user
    int time_quantum;                  // Time quantum cho RR
    int c;                             // Biến tạm để xóa buffer

    // Clear screen and display welcome message
    clear_screen();
    print_box_header("CPU SCHEDULING ALGORITHMS SIMULATOR");

    printf("%sWelcome to CPU Scheduling Simulator!%s\n", ANSI_BOLD ANSI_GREEN, ANSI_RESET);
    printf("This program implements %s6 scheduling algorithms%s:\n", ANSI_YELLOW, ANSI_RESET);
    printf("  • FCFS (First Come First Serve)\n");
    printf("  • SJF (Shortest Job First)\n");
    printf("  • SRTF (Shortest Remaining Time First)\n");
    printf("  • Priority (Non-Preemptive)\n");
    printf("  • Priority (Preemptive)\n");
    printf("  • Round Robin\n\n");

    // Get input method
    int input_choice = display_input_menu();

    if (input_choice == 1) {
        // --- CHỈNH SỬA 1: Vòng lặp nhập file cho đến khi đúng ---
        char filename[256];
        int file_loaded = 0;

        while (!file_loaded) {
            printf("\n%sEnter filename%s (e.g., tests/test_cases/test1.txt): ", ANSI_BOLD, ANSI_RESET);
            scanf("%s", filename);

            if (read_from_file(filename, processes, &n)) {
                printf("%s✓ Successfully loaded %d processes%s\n", ANSI_GREEN, n, ANSI_RESET);
                file_loaded = 1; // Thoát vòng lặp
            }
            else {
                printf("%sError reading file. Please try again.%s\n", ANSI_RED, ANSI_RESET);
                // Vòng lặp sẽ tiếp tục quay lại yêu cầu nhập file
            }
        }
    }
    else if (input_choice == 2) {
        // Read from keyboard
        clear_screen();
        if (!read_from_keyboard(processes, &n)) {
            printf("%sError reading input. Exiting.%s\n", ANSI_RED, ANSI_RESET);
            return 1;
        }
        printf("%s✓ Successfully loaded %d processes%s\n", ANSI_GREEN, n, ANSI_RESET);
    }
    else {
        printf("%sInvalid choice. Exiting.%s\n", ANSI_RED, ANSI_RESET);
        return 1;
    }

    // Backup processes gốc
    copy_processes(original, processes, n);

    // BƯỚC 3: Main loop
    do {
        // Clear screen before showing menu
        clear_screen();

        // Reset processes về trạng thái ban đầu
        copy_processes(processes, original, n);

        // Hiển thị menu
        choice = display_menu();

        // BƯỚC 4: Xử lý lựa chọn
        switch (choice) {
        case 1: // FCFS
            clear_screen();
            printf("\n%s⚙ Running FCFS Algorithm...%s\n", ANSI_YELLOW, ANSI_RESET);
            fcfs(processes, n);
            display_results(processes, n, "FCFS - First Come First Serve");
            display_gantt_chart(processes, n);
            break;

        case 2: // SJF
            clear_screen();
            printf("\n%s⚙ Running SJF Algorithm...%s\n", ANSI_YELLOW, ANSI_RESET);
            sjf(processes, n);
            display_results(processes, n, "SJF - Shortest Job First (Non-Preemptive)");
            display_gantt_chart(processes, n);
            break;

        case 3: // SRTF
            clear_screen();
            printf("\n%s⚙ Running SRTF Algorithm...%s\n", ANSI_YELLOW, ANSI_RESET);
            srtf(processes, n);
            display_results(processes, n, "SRTF - Shortest Remaining Time First");
            display_gantt_chart(processes, n);
            break;

        case 4: // Priority NP
            clear_screen();
            printf("\n%s⚙ Running Priority (Non-Preemptive) Algorithm...%s\n", ANSI_YELLOW, ANSI_RESET);
            priority_non_preemptive(processes, n);
            display_results(processes, n, "Priority Scheduling (Non-Preemptive)");
            display_gantt_chart(processes, n);
            break;

        case 5: // Priority P
            clear_screen();
            printf("\n%s⚙ Running Priority (Preemptive) Algorithm...%s\n", ANSI_YELLOW, ANSI_RESET);
            priority_preemptive(processes, n);
            display_results(processes, n, "Priority Scheduling (Preemptive)");
            display_gantt_chart(processes, n);
            break;

        case 6: // Round Robin
            clear_screen();
            printf("\n%s⚙ Running Round Robin Algorithm...%s\n", ANSI_YELLOW, ANSI_RESET);
            printf("%sEnter time quantum:%s ", ANSI_BOLD, ANSI_RESET);
            scanf("%d", &time_quantum);

            if (!validate_time_quantum(time_quantum)) {
                printf("%s⚠ Invalid time quantum. Using default: %d%s\n",
                    ANSI_YELLOW, DEFAULT_TIME_QUANTUM, ANSI_RESET);
                time_quantum = DEFAULT_TIME_QUANTUM;
            }

            round_robin(processes, n, time_quantum);
            char rr_title[100];
            snprintf(rr_title, sizeof(rr_title), "Round Robin (Time Quantum = %d)", time_quantum);
            display_results(processes, n, rr_title);
            display_gantt_chart(processes, n);
            break;

        case 7: // Compare All
            clear_screen();
            printf("\n%s⚙ Comparing All Algorithms...%s\n", ANSI_YELLOW, ANSI_RESET);
            display_comparison(original, n, DEFAULT_TIME_QUANTUM);
            break;

        case 8: // Exit
            clear_screen();
            print_box_header("GOODBYE");
            printf("%s✓ Thank you for using CPU Scheduling Simulator!%s\n", ANSI_GREEN, ANSI_RESET);
            printf("%sGoodbye!%s\n\n", ANSI_CYAN, ANSI_RESET);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

        // Pause để user đọc kết quả
        if (choice != 8) {
            // --- CHỈNH SỬA 2: Xóa bộ nhớ đệm trước khi pause ---
            // Lệnh này sẽ 'ăn' hết các ký tự thừa (như dấu Enter) còn sót lại
            while ((c = getchar()) != '\n' && c != EOF);

            pause_enter();
        }

    } while (choice != 8);

    return 0;
}