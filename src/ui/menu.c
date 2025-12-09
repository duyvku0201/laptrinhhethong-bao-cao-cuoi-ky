#include <stdio.h>
#include "../../include/process.h"
#include "../../include/algorithms.h"
#include "../../include/display.h"
#include "../../include/io.h"
#include "../../include/utils.h"

int display_menu(void) {
    int choice;
    printf("\n");
    print_separator(60, '=');
    printf("           CPU SCHEDULING ALGORITHMS MENU\n");
    print_separator(60, '=');
    printf("\n");
    printf("  1. FCFS (First Come First Serve)\n");
    printf("  2. SJF (Shortest Job First - Non-Preemptive)\n");
    printf("  3. SRTF (Shortest Remaining Time First - Preemptive)\n");
    printf("  4. Priority Scheduling (Non-Preemptive)\n");
    printf("  5. Priority Scheduling (Preemptive)\n");
    printf("  6. Round Robin\n");
    printf("  7. Compare All Algorithms\n");
    printf("  8. Exit\n");
    printf("\n");
    print_separator(60, '-');

    // Dùng hàm nhập mới
    choice = get_int_input_with_esc("Enter your choice [1-8] (Esc to restart): ");

    if (choice == ESC_CANCEL) return ESC_CANCEL; // Truyền tín hiệu hủy lên trên

    while (choice < 1 || choice > 8) {
        printf("Invalid choice! Please enter 1-8: ");
        choice = get_int_input_with_esc("Enter your choice [1-8]: ");
        if (choice == ESC_CANCEL) return ESC_CANCEL;
    }
    return choice;
}

int display_input_menu(void) {
    int choice;
    printf("\n");
    printf("How do you want to input process data?\n");
    printf("  1. Read from file\n");
    printf("  2. Enter from keyboard\n");
    printf("\n");

    choice = get_int_input_with_esc("Enter choice [1-2] (Esc to restart): ");

    if (choice == ESC_CANCEL) return ESC_CANCEL;

    while (choice < 1 || choice > 2) {
        printf("Invalid choice! Please enter 1-2: ");
        choice = get_int_input_with_esc("Enter choice [1-2]: ");
        if (choice == ESC_CANCEL) return ESC_CANCEL;
    }
    return choice;
}