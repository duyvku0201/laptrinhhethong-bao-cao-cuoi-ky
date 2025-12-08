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
 * @brief Display Gantt chart with colored visualization
 * @param processes Array of processes
 * @param n Number of processes
 */
void display_gantt_chart(Process processes[], int n) {
    if (!processes || n <= 0) {
        printf("\n%sNo processes to display in Gantt chart%s\n", ANSI_RED, ANSI_RESET);
        return;
    }
    
    printf("\n");
    print_box_header("GANTT CHART");
    
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
        printf("%sNo valid timeline data%s\n", ANSI_RED, ANSI_RESET);
        return;
    }
    
    qsort(slots, slot_count, sizeof(GanttSlot), compare_gantt);
    
    // Colors for each process (cycle through colors)
    const char *colors[] = {
        ANSI_GREEN, ANSI_YELLOW, ANSI_BLUE, 
        ANSI_MAGENTA, ANSI_CYAN, ANSI_RED
    };
    int num_colors = 6;
    
    // Print top border
    printf(" %s┌", ANSI_CYAN);
    for (int i = 0; i < slot_count; i++) {
        printf("──────");
        if (i < slot_count - 1) printf("┬");
    }
    printf("┐%s\n", ANSI_RESET);
    
    // Print process IDs with colors
    printf(" %s│%s", ANSI_CYAN, ANSI_RESET);
    for (int i = 0; i < slot_count; i++) {
        const char *color = colors[(slots[i].pid - 1) % num_colors];
        printf("%s  P%-3d%s", color, slots[i].pid, ANSI_RESET);
        printf("%s│%s", ANSI_CYAN, ANSI_RESET);
    }
    printf("\n");
    
    // Print bottom border
    printf(" %s└", ANSI_CYAN);
    for (int i = 0; i < slot_count; i++) {
        printf("──────");
        if (i < slot_count - 1) printf("┴");
    }
    printf("┘%s\n", ANSI_RESET);
    
    // Print timeline
    printf("%s%-2d%s", ANSI_BOLD, slots[0].start, ANSI_RESET);
    for (int i = 0; i < slot_count; i++) {
        printf("      %s%-2d%s", ANSI_BOLD, slots[i].end, ANSI_RESET);
    }
    printf("\n\n");
    
    // Print legend
    printf("%s└─ Each block represents execution period of a process%s\n", ANSI_DIM, ANSI_RESET);
}
