#ifndef UTILS_H
#define UTILS_H

#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Key codes
#define KEY_ESC 27
#define ESC_CANCEL -9999

// Colors
#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD    "\x1b[1m"
#define ANSI_DIM     "\x1b[2m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"

// UI Functions
void print_colored(const char* color, const char* text);
void print_box_header(const char* title);
void print_separator(int width, char c);
void clear_screen(void);

// Input Functions
int wait_for_enter_with_esc(void);
int get_int_input_with_esc(const char* prompt);
int get_str_input_with_esc(const char* prompt, char* buf, int max_len);

// Sorting & Validation
void sort_by_arrival(Process processes[], int n);
void sort_by_priority(Process processes[], int n);
void sort_by_pid(Process processes[], int n);
void copy_processes(Process dest[], Process src[], int n);
int validate_input(Process processes[], int n);
int check_duplicate_pids(Process processes[], int n);
int validate_time_quantum(int time_quantum);

// Helpers (Static Inline để tránh lỗi Linker)
static inline int min_int(int a, int b) { return (a < b) ? a : b; }
static inline int max_int(int a, int b) { return (a > b) ? a : b; }

#endif // UTILS_H