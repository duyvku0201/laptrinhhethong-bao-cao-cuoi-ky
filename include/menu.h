#ifndef MENU_H
#define MENU_H

#include "process.h"

void show_menu();
void run_scheduling(int choice, Process p[], int n);
void print_header();
void print_process_table(Process p[], int n);
int display_menu(void);

#endif