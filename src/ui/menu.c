
#define _CRT_SECURE_NO_WARNINGS
/**
 * @file menu.c
 * @brief Menu display functions
 */

#include <stdio.h>

#include "process.h"
#include "algorithms.h"
#include "display.h"
#include "io.h"
#include "utils.h"
 /**
  * @brief Hiển thị main menu và nhận input
  * @return Choice của user (1-8)
  */
int display_menu(void) {
    int choice;

    printf("\n");
    print_separator();
    printf("           CPU SCHEDULING ALGORITHMS MENU\n");
    print_separator();

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
    print_separator();

    printf("Enter your choice [1-8]: ");
    scanf("%d", &choice);

    // Validate input
    while (choice < 1 || choice > 8) {
        printf("Invalid choice! Please enter 1-8: ");
        scanf("%d", &choice);
    }

    return choice;
}

/**
 * @brief Hiển thị input menu
 * @return Input method choice (1-2)
 */
int display_input_menu(void) {
    int choice;

    printf("\n");
    printf("How do you want to input process data?\n");
    printf("  1. Read from file\n");
    printf("  2. Enter from keyboard\n");
    printf("\nEnter choice [1-2]: ");
    scanf("%d", &choice);

    while (choice < 1 || choice > 2) {
        printf("Invalid choice! Please enter 1-2: ");
        scanf("%d", &choice);
    }

    return choice;
}