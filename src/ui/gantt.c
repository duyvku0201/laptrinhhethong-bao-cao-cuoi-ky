/**
 * @file gantt.c
 * @brief Gantt chart visualization for scheduling algorithms
 * @author Team CPU Scheduling
 */

#include "display.h"
#include "process.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Struct để lưu execution timeline
typedef struct {
    int pid;
    int start;
    int end;
} GanttSlot;

/**
 * @brief So sánh để sort theo start time
 */
static int compare_gantt(const void *a, const void *b) {
    GanttSlot *ga = (GanttSlot *)a;
    GanttSlot *gb = (GanttSlot *)b;
    return ga->start - gb->start;
}

/**
 * @brief Display Gantt chart (basic version)
 * @param processes Array of processes
 * @param n Number of processes
 */
void display_gantt_chart(Process processes[], int n) {
    if (!processes || n <= 0) {
        printf("\nNo processes to display in Gantt chart\n");
        return;
    }
    
    printf("\n");
    print_separator();
    printf("                    GANTT CHART\n");
    print_separator();
    
    // Sort processes by start time để hiển thị đúng thứ tự
    GanttSlot slots[MAX_PROCESSES];
    int slot_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].StartTime >= 0 && processes[i].CompletionTime > 0) {
            slots[slot_count].pid = processes[i].ProcessId;
            slots[slot_count].start = processes[i].StartTime;
            slots[slot_count].end = processes[i].CompletionTime;
            slot_count++;
        }
    }
    
    if (slot_count == 0) {
        printf("No valid timeline data\n");
        return;
    }
    
    qsort(slots, slot_count, sizeof(GanttSlot), compare_gantt);
    
    // Print top border
    printf(" ");
    for (int i = 0; i < slot_count; i++) {
        printf("+------");
    }
    printf("+\n");
    
    // Print process IDs
    printf(" ");
    for (int i = 0; i < slot_count; i++) {
        printf("|  P%-3d", slots[i].pid);
    }
    printf("|\n");
    
    // Print bottom border
    printf(" ");
    for (int i = 0; i < slot_count; i++) {
        printf("+------");
    }
    printf("+\n");
    
    // Print timeline
    printf("%-2d", slots[0].start);
    for (int i = 0; i < slot_count; i++) {
        printf("      %-2d", slots[i].end);
    }
    printf("\n\n");
}

/**
 * @brief Display Gantt chart with colors
 * @param processes Array of processes
 * @param n Number of processes
 */
void display_gantt_chart_colored(Process processes[], int n) {
    if (!processes || n <= 0) {
        printf("\nNo processes to display in Gantt chart\n");
        return;
    }
    
    printf("\n");
    print_colored(ANSI_CYAN, "========================================");
    printf("\n");
    print_colored(ANSI_BOLD ANSI_YELLOW, "          GANTT CHART (Colored)        ");
    printf("\n");
    print_colored(ANSI_CYAN, "========================================");
    printf("\n\n");
    
    // Sort processes by start time
    GanttSlot slots[MAX_PROCESSES];
    int slot_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (processes[i].StartTime >= 0 && processes[i].CompletionTime > 0) {
            slots[slot_count].pid = processes[i].ProcessId;
            slots[slot_count].start = processes[i].StartTime;
            slots[slot_count].end = processes[i].CompletionTime;
            slot_count++;
        }
    }
    
    if (slot_count == 0) {
        print_colored(ANSI_RED, "No valid timeline data\n");
        return;
    }
    
    qsort(slots, slot_count, sizeof(GanttSlot), compare_gantt);
    
    // Colors cho mỗi process (cycle through colors)
    const char *colors[] = {
        ANSI_GREEN, ANSI_YELLOW, ANSI_BLUE, 
        ANSI_MAGENTA, ANSI_CYAN, ANSI_RED
    };
    int num_colors = 6;
    
    // Print top border
    printf(" ");
    print_colored(ANSI_CYAN, "+");
    for (int i = 0; i < slot_count; i++) {
        print_colored(ANSI_CYAN, "------+");
    }
    printf("\n");
    
    // Print process IDs với màu
    printf(" ");
    print_colored(ANSI_CYAN, "|");
    for (int i = 0; i < slot_count; i++) {
        const char *color = colors[(slots[i].pid - 1) % num_colors];
        printf("%s  P%-3d%s", color, slots[i].pid, ANSI_RESET);
        print_colored(ANSI_CYAN, "|");
    }
    printf("\n");
    
    // Print bottom border
    printf(" ");
    print_colored(ANSI_CYAN, "+");
    for (int i = 0; i < slot_count; i++) {
        print_colored(ANSI_CYAN, "------+");
    }
    printf("\n");
    
    // Print timeline
    printf("%s%-2d%s", ANSI_BOLD, slots[0].start, ANSI_RESET);
    for (int i = 0; i < slot_count; i++) {
        printf("      %s%-2d%s", ANSI_BOLD, slots[i].end, ANSI_RESET);
    }
    printf("\n\n");
    
    // Print legend
    print_colored(ANSI_DIM, "Legend: Each block represents execution period of a process\n");
}
