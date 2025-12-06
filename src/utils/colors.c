/**
 * @file colors.c
 * @brief Utility functions for colored terminal output and UI enhancements
 * @author Team CPU Scheduling
 */

#include "utils.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief In text với màu sắc
 * @param color Mã màu ANSI (VD: ANSI_RED, ANSI_GREEN, ...)
 * @param text Nội dung cần in
 */
void print_colored(const char *color, const char *text) {
    if (color && text) {
        printf("%s%s%s", color, text, ANSI_RESET);
    }
}

/**
 * @brief In header đẹp với viền và tiêu đề
 * @param title Tiêu đề header
 */
void print_box_header(const char *title) {
    int title_len = strlen(title);
    int total_width = 80;
    int padding = (total_width - title_len - 2) / 2;
    
    // In dòng trên
    printf("\n");
    print_colored(ANSI_CYAN, "╔");
    for (int i = 0; i < total_width - 2; i++) {
        print_colored(ANSI_CYAN, "═");
    }
    print_colored(ANSI_CYAN, "╗\n");
    
    // In dòng tiêu đề
    print_colored(ANSI_CYAN, "║");
    for (int i = 0; i < padding; i++) printf(" ");
    print_colored(ANSI_BOLD ANSI_YELLOW, title);
    for (int i = 0; i < total_width - padding - title_len - 2; i++) printf(" ");
    print_colored(ANSI_CYAN, "║\n");
    
    // In dòng dưới
    print_colored(ANSI_CYAN, "╚");
    for (int i = 0; i < total_width - 2; i++) {
        print_colored(ANSI_CYAN, "═");
    }
    print_colored(ANSI_CYAN, "╝\n");
    printf("\n");
}

/**
 * @brief In gạch ngang phân cách
 */
void print_separator(void) {
    print_colored(ANSI_BLUE, "────────────────────────────────────────"
                             "────────────────────────────────────────\n");
}

/**
 * @brief Xóa màn hình console
 * Sử dụng ANSI escape codes để xóa màn hình
 */
void clear_screen(void) {
    // ANSI clear screen + move cursor to (0,0)
    printf("\033[2J\033[H");
    fflush(stdout);
}
