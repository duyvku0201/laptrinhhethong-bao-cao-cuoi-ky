#include "io.h"
#include <stdio.h>

int read_from_file(const char *filename, Process p[], int *n)
{
    *n = 2;
    p[0].pid = 1;
    p[0].arrival_time = 0;
    p[0].burst_time = 5;
    p[0].priority = 1;
    p[1].pid = 2;
    p[1].arrival_time = 1;
    p[1].burst_time = 3;
    p[1].priority = 2;
    return 1;
}

int read_from_keyboard(Process p[], int *n)
{
    *n = 2;
    p[0].pid = 1;
    p[0].arrival_time = 0;
    p[0].burst_time = 5;
    p[0].priority = 1;
    p[1].pid = 2;
    p[1].arrival_time = 1;
    p[1].burst_time = 3;
    p[1].priority = 2;
    return 1;
}

int write_to_file(const char *filename, Process p[], int n, const char *algo)
{
    printf("Saving results to file: %s (algo: %s)\n", filename, algo);
    return 1;
}