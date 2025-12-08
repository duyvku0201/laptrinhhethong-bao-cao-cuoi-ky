#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "process.h"

// ANSI color helpers (safe to use on most terminals)
#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD    "\x1b[1m"
#define ANSI_DIM     "\x1b[2m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"

// Small inline helpers to avoid separate .c dependency
static inline int min_int(int a, int b) { return a < b ? a : b; }
static inline int max_int(int a, int b) { return a > b ? a : b; }
static inline int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}
static inline void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// UI utilities - declarations (implementations in colors.c)
void print_colored(const char *color, const char *text);
void print_box_header(const char *title);
void print_separator(void);
void clear_screen(void);

static inline void pause_enter(void) {
    fputs("\nPress Enter to continue...", stdout);
    fflush(stdout);
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
}

// Validation utilities
int validate_time_quantum(int time_quantum);
int check_duplicate_pids(Process processes[], int n);

// Process utilities
void copy_processes(Process dest[], const Process src[], int n);

// Sorting utilities
void sort_by_arrival(Process processes[], int n);
void sort_by_burst(Process processes[], int n);
void sort_by_priority(Process processes[], int n);

#endif // UTILS_H
