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
#include <string.h>

// Struct để lưu execution timeline
typedef struct {
    int pid;
    int start;
    int end;
} GanttSlot;

/**
 * @brief Display Gantt chart with colored visualization showing actual execution timeline
 * @param processes Array of processes (not used but kept for compatibility)
 * @param n Number of processes (not used but kept for compatibility)
 */
void display_gantt_chart(Process processes[], int n) {
    (void)processes; // Unused parameter
    (void)n;         // Unused parameter
    
    // Use global timeline instead
    extern TimelineEntry global_timeline[];
    extern int global_timeline_count;
    
    if (global_timeline_count == 0) {
        printf("\n%sNo timeline data available. Gantt chart cannot be displayed.%s\n", ANSI_RED, ANSI_RESET);
        printf("%sNote: Make sure to run an algorithm before displaying Gantt chart.%s\n\n", ANSI_YELLOW, ANSI_RESET);
        return;
    }
    
    printf("\n");
    print_box_header("GANTT CHART - Process Execution Timeline");
    
    // Use timeline entries directly
    GanttSlot slots[MAX_TIMELINE_ENTRIES];
    int slot_count = global_timeline_count;
    
    for (int i = 0; i < slot_count; i++) {
        slots[i].pid = global_timeline[i].process_id;
        slots[i].start = global_timeline[i].start_time;
        slots[i].end = global_timeline[i].end_time;
    }
    
    // Already sorted by time in timeline
    
    // Colors for each process (cycle through colors)
    const char *colors[] = {
        ANSI_GREEN, ANSI_YELLOW, ANSI_BLUE, 
        ANSI_MAGENTA, ANSI_CYAN, ANSI_RED
    };
    int num_colors = 6;
    
    // Display in one line with variable width blocks based on duration
    // Print top border
    printf("%s+", ANSI_CYAN);
    for (int i = 0; i < slot_count; i++) {
        int duration = slots[i].end - slots[i].start;
        int width = duration * 2 + 2; // 2 chars per time unit + padding
        if (width < 4) width = 4; // minimum width
        for (int j = 0; j < width; j++) printf("-");
        printf("+");
    }
    printf("%s\n", ANSI_RESET);
    
    // Print process IDs with colors (centered in variable width)
    printf("%s|", ANSI_CYAN);
    for (int i = 0; i < slot_count; i++) {
        int duration = slots[i].end - slots[i].start;
        int width = duration * 2 + 2;
        if (width < 4) width = 4;
        
        const char *color = colors[(slots[i].pid - 1) % num_colors];
        
        // Center the process ID
        char pid_str[10];
        snprintf(pid_str, sizeof(pid_str), "P%d", slots[i].pid);
        int pid_len = strlen(pid_str);
        int left_pad = (width - pid_len) / 2;
        int right_pad = width - pid_len - left_pad;
        
        for (int j = 0; j < left_pad; j++) printf(" ");
        printf("%s%s%s", color, pid_str, ANSI_RESET);
        for (int j = 0; j < right_pad; j++) printf(" ");
        printf("%s|%s", ANSI_CYAN, ANSI_RESET);
    }
    printf("\n");
    
    // Print bottom border
    printf("%s+", ANSI_CYAN);
    for (int i = 0; i < slot_count; i++) {
        int duration = slots[i].end - slots[i].start;
        int width = duration * 2 + 2;
        if (width < 4) width = 4;
        for (int j = 0; j < width; j++) printf("-");
        printf("+");
    }
    printf("%s\n", ANSI_RESET);
    
    // Print timeline numbers
    printf("%s%-2d%s", ANSI_BOLD, slots[0].start, ANSI_RESET);
    for (int i = 0; i < slot_count; i++) {
        int duration = slots[i].end - slots[i].start;
        int width = duration * 2 + 2;
        if (width < 4) width = 4;
        
        // Calculate spacing to align with the right edge of each block
        int num_len = snprintf(NULL, 0, "%d", slots[i].end);
        int spacing = width + 1 - num_len;
        
        for (int j = 0; j < spacing; j++) printf(" ");
        printf("%s%d%s", ANSI_BOLD, slots[i].end, ANSI_RESET);
    }
    printf("\n\n");
    
    // Print detailed execution log
    printf("%s═══ Execution Timeline Details ═══%s\n", ANSI_BOLD ANSI_CYAN, ANSI_RESET);
    printf("%-10s %-10s %-10s %-10s\n", "Process", "Start", "End", "Duration");
    printf("─────────────────────────────────────────\n");
    
    int process_exec_time[MAX_PROCESSES] = {0};
    int process_count[MAX_PROCESSES] = {0};
    
    for (int i = 0; i < slot_count; i++) {
        int duration = slots[i].end - slots[i].start;
        const char *color = colors[(slots[i].pid - 1) % num_colors];
        
        printf("%-10s%sP%d%s      %-10d %-10d %-10d\n", 
               "", color, slots[i].pid, ANSI_RESET,
               slots[i].start, slots[i].end, duration);
        
        process_exec_time[slots[i].pid] += duration;
        process_count[slots[i].pid]++;
    }
    
    printf("─────────────────────────────────────────\n");
    printf("\n%s═══ Process Execution Summary ═══%s\n", ANSI_BOLD ANSI_CYAN, ANSI_RESET);
    printf("%-10s %-15s %-10s\n", "Process", "Total CPU Time", "# of Runs");
    printf("─────────────────────────────────────────\n");
    
    for (int i = 1; i < MAX_PROCESSES; i++) {
        if (process_count[i] > 0) {
            const char *color = colors[(i - 1) % num_colors];
            printf("%-10s%sP%d%s      %-15d %-10d\n", 
                   "", color, i, ANSI_RESET,
                   process_exec_time[i], process_count[i]);
        }
    }
    
    printf("\n%s└─ Each block shows when each process was actively running on the CPU%s\n", ANSI_DIM, ANSI_RESET);
    printf("%s└─ Context switches are visible as process changes%s\n\n", ANSI_DIM, ANSI_RESET);
}
