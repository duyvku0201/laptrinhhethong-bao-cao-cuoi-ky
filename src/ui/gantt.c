#include "../../include/display.h"
#include "../../include/process.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    int start;
    int end;
} GanttEvent;

static GanttEvent gantt_history[2000];
static int gantt_count = 0;

void reset_gantt_log(void) {
    gantt_count = 0;
}

void log_gantt_event(int pid, int start, int end) {
    if (start >= end) return;
    if (gantt_count > 0 && gantt_history[gantt_count - 1].pid == pid && gantt_history[gantt_count - 1].end == start) {
        gantt_history[gantt_count - 1].end = end;
    }
    else {
        gantt_history[gantt_count].pid = pid;
        gantt_history[gantt_count].start = start;
        gantt_history[gantt_count].end = end;
        gantt_count++;
    }
}

void display_gantt_chart_colored(Process processes[], int n) {
    if (gantt_count == 0) {
        printf("\nNo Gantt data available.\n");
        return;
    }
    printf("\n");
    print_separator(60, '=');
    printf("          GANTT CHART\n");
    print_separator(60, '=');
    printf("\n");

    // Top border
    printf(" ");
    for (int i = 0; i < gantt_count; i++) {
        print_colored(ANSI_CYAN, "+");
        int duration = gantt_history[i].end - gantt_history[i].start;
        int bar_len = (duration > 2) ? 6 : 4;
        for (int k = 0; k < bar_len; k++) print_colored(ANSI_CYAN, "-");
    }
    print_colored(ANSI_CYAN, "+\n");

    // PID
    printf(" ");
    for (int i = 0; i < gantt_count; i++) {
        print_colored(ANSI_CYAN, "|");
        int duration = gantt_history[i].end - gantt_history[i].start;
        int bar_len = (duration > 2) ? 6 : 4;
        char pid_str[10];
        sprintf(pid_str, "P%d", gantt_history[i].pid);
        int padding = (bar_len - (int)strlen(pid_str)) / 2;
        for (int k = 0; k < padding; k++) printf(" ");
        printf("%s%s%s", ANSI_GREEN, pid_str, ANSI_RESET);
        for (int k = 0; k < bar_len - padding - strlen(pid_str); k++) printf(" ");
    }
    print_colored(ANSI_CYAN, "|\n");

    // Bottom border
    printf(" ");
    for (int i = 0; i < gantt_count; i++) {
        print_colored(ANSI_CYAN, "+");
        int duration = gantt_history[i].end - gantt_history[i].start;
        int bar_len = (duration > 2) ? 6 : 4;
        for (int k = 0; k < bar_len; k++) print_colored(ANSI_CYAN, "-");
    }
    print_colored(ANSI_CYAN, "+\n");

    // Timeline
    printf("%-2d", gantt_history[0].start);
    for (int i = 0; i < gantt_count; i++) {
        int duration = gantt_history[i].end - gantt_history[i].start;
        int bar_len = (duration > 2) ? 6 : 4;
        int num_len = (gantt_history[i].end >= 100) ? 3 : (gantt_history[i].end >= 10) ? 2 : 1;
        for (int k = 0; k < bar_len + 1 - num_len; k++) printf(" ");
        printf("%d", gantt_history[i].end);
    }
    printf("\n\n");
}

void display_gantt_chart(Process processes[], int n) {
    display_gantt_chart_colored(processes, n);
}