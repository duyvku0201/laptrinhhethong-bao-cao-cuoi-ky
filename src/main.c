#include <stdio.h>
#include <stdlib.h>
#include "../include/process.h"
#include "../include/algorithms.h"
#include "../include/io.h"
#include "../include/display.h"
#include "../include/utils.h"
#include "../include/menu.h"

int main() {
    Process processes[MAX_PROCESSES];
    Process original[MAX_PROCESSES];
    int n = 0;
    int choice;
    int time_quantum;
    int input_method;

    while (1) {
        clear_screen();
        print_box_header("CPU SCHEDULING ALGORITHMS SIMULATOR");

        // === 1. NHẬP LIỆU ===
        input_method = display_input_menu();

        // Nếu nhấn ESC ở menu chọn kiểu nhập -> Reset lại từ đầu
        if (input_method == ESC_CANCEL) continue;

        if (input_method == 1) { // File
            char filename[256];
            int ret = get_str_input_with_esc("Enter filename (e.g., tests/test_cases/test1.txt): ", filename, 256);

            if (ret == ESC_CANCEL) continue; // Nhấn Esc khi nhập tên file

            if (!LoadProcessesFromFile(filename, processes, &n)) {
                printf("Failed to load file. Press Enter to retry.\n");
                wait_for_enter_with_esc();
                continue;
            }
        }
        else { // Keyboard
            if (!ReadProcessesFromConsole(processes, &n)) {
                // Nếu hàm trả về false (do nhấn Esc), ta quay lại màn hình chính ngay
                continue;
            }
        }

        copy_processes(original, processes, n);

        // === 2. CHẠY THUẬT TOÁN ===
        do {
            copy_processes(processes, original, n);
            reset_gantt_log();

            choice = display_menu();

            // Nếu nhấn Esc ở menu thuật toán -> Quay lại màn hình nhập liệu (Màn hình đầu tiên)
            if (choice == ESC_CANCEL) break;

            switch (choice) {
            case 1: fcfs(processes, n); display_results(processes, n, "FCFS"); display_gantt_chart(processes, n); break;
            case 2: sjf(processes, n); display_results(processes, n, "SJF"); display_gantt_chart(processes, n); break;
            case 3: srtf(processes, n); display_results(processes, n, "SRTF"); display_gantt_chart(processes, n); break;
            case 4: priority_non_preemptive(processes, n); display_results(processes, n, "Priority NP"); display_gantt_chart(processes, n); break;
            case 5: priority_preemptive(processes, n); display_results(processes, n, "Priority P"); display_gantt_chart(processes, n); break;
            case 6:
                // Nhập Quantum cũng hỗ trợ Esc
                time_quantum = get_int_input_with_esc("Enter Time Quantum: ");
                if (time_quantum == ESC_CANCEL) break; // Thoát case, quay lại menu thuật toán

                round_robin(processes, n, time_quantum);
                display_results(processes, n, "Round Robin");
                display_gantt_chart(processes, n);
                break;
            case 7: display_comparison(original, n, 2); break;
            case 8:
                printf("Exiting program... Goodbye!\n");
                return 0;
            }

            // Dừng màn hình để xem kết quả. Nếu nhấn Esc ở đây -> Quay về menu thuật toán
            if (choice != 8) {
                if (wait_for_enter_with_esc() == ESC_CANCEL) {
                    // Tùy chọn: Nhấn Esc lúc xem kết quả thì về Menu thuật toán
                    // Nếu muốn về hẳn màn hình đầu tiên thì thêm logic break
                }
            }
        } while (choice != 8);
    }

    return 0;
}