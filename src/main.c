#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "algorithms.h"
#include "io.h"
#include "display.h"
#include "utils.h"

void show_menu();
void run_scheduling(int choice, Process p[], int n);

void print_header()
{
    printf("\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*    CPU SCHEDULING ALGORITHMS SIMULATOR       *\n");
    printf("*                Version 1.0                    *\n");
    printf("*                                               *\n");
    printf("*       Developed by: Group [X]                 *\n");
    printf("*       Course: Operating Systems               *\n");
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("\n");
}

void print_process_table(Process p[], int n)
{
    printf("\n=========================================\n");
    printf("           Loaded Processes              \n");
    printf("=========================================\n");
    printf("PID\tAT\tBT\tPriority\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].priority);
    }
    printf("=========================================\n");
}

int main()
{
    Process proc[100];
    int n, choice, input_type;
    char fname[100];

    print_header();

    printf("=========================================\n");
    printf("                INPUT METHOD              \n");
    printf("=========================================\n");
    printf("  1. Read from file\n");
    printf("  2. Enter from keyboard\n");
    printf("=========================================\n");
    printf("Select input method: ");
    scanf("%d", &input_type);

    if (input_type == 1)
    {
        printf("\nEnter filename: ");
        scanf("%99s", fname);

        if (!read_from_file(fname, proc, &n))
        {
            char path[200];
            sprintf(path, "tests/test_cases/%s", fname);
            if (!read_from_file(path, proc, &n))
            {
                printf("\nError: Cannot open file '%s'\n", fname);
                printf("Expected format:\n");
                printf("Line 1: number_of_processes\n");
                printf("Next lines: PID arrival_time burst_time priority\n");
                return 1;
            }
        }
        printf("\nFile loaded successfully!\n");
    }
    else if (input_type == 2)
    {
        if (!read_from_keyboard(proc, &n))
        {
            printf("\nError: Failed to read input\n");
            return 1;
        }
        printf("\nInput received successfully!\n");
    }
    else
    {
        printf("\nError: Invalid input method\n");
        return 1;
    }

    print_process_table(proc, n);

    printf("\nPress Enter to continue...");
    getchar();
    getchar();

    while (1)
    {
        show_menu();
        scanf("%d", &choice);

        if (choice == 0)
        {
            printf("\n=========================================\n");
            printf("  Thanks for using our program! Goodbye! \n");
            printf("=========================================\n\n");
            break;
        }

        if (choice < 0 || choice > 8)
        {
            printf("\nError: Invalid choice. Please select 0-8.\n");
            continue;
        }

        run_scheduling(choice, proc, n);

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }

    return 0;
}