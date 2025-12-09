#include "../../include/utils.h"
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>

   // Hàm _getch() tự chế cho NetBSD/Linux
   // Chức năng: Đọc 1 ký tự mà không cần nhấn Enter, không hiện ký tự ra màn hình
int _getch(void) {
    struct termios oldattr, newattr;
    int ch;

    // Lấy cấu hình terminal hiện tại
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;

    // Tắt chế độ CANONICAL (chờ Enter) và ECHO (hiện ký tự)
    newattr.c_lflag &= ~(ICANON | ECHO);

    // Áp dụng cấu hình mới
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    // Đọc ký tự
    ch = getchar();

    // Khôi phục cấu hình cũ
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}
#endif

// =========================================================

void print_colored(const char* color, const char* text) {
    if (color && text) printf("%s%s%s", color, text, ANSI_RESET);
}

void print_box_header(const char* title) {
    int title_len = (int)strlen(title);
    int total_width = 80;
    int padding = (total_width - title_len - 2) / 2;

    printf("\n");
    print_colored(ANSI_CYAN, "+");
    for (int i = 0; i < total_width - 2; i++) print_colored(ANSI_CYAN, "-");
    print_colored(ANSI_CYAN, "+\n");

    print_colored(ANSI_CYAN, "|");
    for (int i = 0; i < padding; i++) printf(" ");
    print_colored(ANSI_BOLD ANSI_YELLOW, title);
    for (int i = 0; i < total_width - padding - title_len - 2; i++) printf(" ");
    print_colored(ANSI_CYAN, "|\n");

    print_colored(ANSI_CYAN, "+");
    for (int i = 0; i < total_width - 2; i++) print_colored(ANSI_CYAN, "-");
    print_colored(ANSI_CYAN, "+\n");
}

void print_separator(int width, char c) {
    print_colored(ANSI_BLUE, "");
    for (int i = 0; i < width; i++) printf("%c", c);
    printf("\n");
    print_colored(ANSI_RESET, "");
}

void clear_screen(void) {
    printf("\033[2J\033[H");
}

int wait_for_enter_with_esc(void) {
    printf("\nPress [Enter] to continue, or [Esc] to return Main Menu...");
    while (1) {
        int c = _getch();
        if (c == KEY_ESC) return ESC_CANCEL;
        if (c == 10 || c == 13) return 1;
    }
}

// Hàm nhập số nguyên thông minh
int get_int_input_with_esc(const char* prompt) {
    printf("%s", prompt);
    char buffer[50] = { 0 };
    int idx = 0;

    while (1) {
        int c = _getch(); // Dùng int vì getchar trả về int

        if (c == KEY_ESC) {
            printf("\n[Cancelled]\n");
            return ESC_CANCEL;
        }

        if (c == 10 || c == 13) { // Enter (Unix dùng 10, Windows dùng 13)
            printf("\n");
            if (idx == 0) return 0;
            return atoi(buffer);
        }

        if (c == 127 || c == 8) { // Backspace (Unix thường là 127, Windows là 8)
            if (idx > 0) {
                printf("\b \b");
                idx--;
                buffer[idx] = 0;
            }
        }

        if (c >= '0' && c <= '9') {
            if (idx < 49) {
                printf("%c", c);
                buffer[idx++] = (char)c;
            }
        }

        if (c == '-' && idx == 0) {
            printf("%c", c);
            buffer[idx++] = (char)c;
        }
    }
}

int get_str_input_with_esc(const char* prompt, char* buf, int max_len) {
    printf("%s", prompt);
    int idx = 0;
    memset(buf, 0, max_len);

    while (1) {
        int c = _getch();

        if (c == KEY_ESC) {
            printf("\n[Cancelled]\n");
            return ESC_CANCEL;
        }

        if (c == 10 || c == 13) {
            printf("\n");
            return 1;
        }

        if (c == 127 || c == 8) { // Backspace handling for both OS
            if (idx > 0) {
                printf("\b \b");
                idx--;
                buf[idx] = 0;
            }
        }

        if (c >= 32 && c <= 126) {
            if (idx < max_len - 1) {
                printf("%c", c);
                buf[idx++] = (char)c;
            }
        }
    }
}