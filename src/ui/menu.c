
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
 * @brief Display main menu and get user input
 * @return User's choice (1-8)
 */
int display_menu(void) {
    int choice;

    printf("\n");
    print_box_header("CPU SCHEDULING ALGORITHMS MENU");

    printf("  %s1.%s FCFS (First Come First Serve)\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s2.%s SJF (Shortest Job First - Non-Preemptive)\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s3.%s SRTF (Shortest Remaining Time First - Preemptive)\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s4.%s Priority Scheduling (Non-Preemptive)\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s5.%s Priority Scheduling (Preemptive)\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s6.%s Round Robin\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s7.%s Compare All Algorithms\n", ANSI_GREEN, ANSI_RESET);
    printf("  %s8.%s Exit\n", ANSI_RED, ANSI_RESET);
    printf("\n");
    print_separator();

    printf("%sEnter your choice [1-8]:%s ", ANSI_BOLD, ANSI_RESET);
    scanf("%d", &choice);

    // Validate input
    while (choice < 1 || choice > 8) {
        printf("%sInvalid choice! Please enter 1-8:%s ", ANSI_RED, ANSI_RESET);
        scanf("%d", &choice);
    }

    return choice;
}

/**
 * @brief Display input menu
 * @return Input method choice (1-2)
 */
int display_input_menu(void) {
    int choice;

    printf("\n");
    print_box_header("INPUT METHOD SELECTION");
    printf("  %s1.%s Read from file\n", ANSI_CYAN, ANSI_RESET);
    printf("  %s2.%s Enter from keyboard\n", ANSI_CYAN, ANSI_RESET);
    printf("\n");
    printf("%sEnter choice [1-2]:%s ", ANSI_BOLD, ANSI_RESET);
    scanf("%d", &choice);

    while (choice < 1 || choice > 2) {
        printf("%sInvalid choice! Please enter 1-2:%s ", ANSI_RED, ANSI_RESET);
        scanf("%d", &choice);
    }

    return choice;
}