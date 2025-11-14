/**
 * @file io.c
 * @brief Wrapper functions for I/O operations
 * @description This file provides wrapper functions that delegate to
 *              the actual implementations in file_handler.c and input.c
 */

#include "io.h"
#include <stdio.h>

/**
 * @brief Read processes from file
 * @param filename Path to the input file
 * @param p Array to store processes
 * @param n Pointer to store number of processes read
 * @return 1 on success, 0 on failure
 */
int read_from_file(const char *filename, Process p[], int *n)
{
    if (LoadProcessesFromFile(filename, p, n)) {
        return 1; // Success
    }
    return 0; // Failure
}

/**
 * @brief Read processes from keyboard input
 * @param p Array to store processes
 * @param n Pointer to store number of processes read
 * @return 1 on success, 0 on failure
 */
int read_from_keyboard(Process p[], int *n)
{
    if (ReadProcessesFromConsole(p, n)) {
        return 1; // Success
    }
    return 0; // Failure
}

/**
 * @brief Write scheduling results to file
 * @param filename Output file path
 * @param p Array of processes
 * @param n Number of processes
 * @param algo Algorithm name
 * @return 1 on success, 0 on failure
 */
int write_to_file(const char *filename, Process p[], int n, const char *algo)
{
    // Calculate average metrics
    float avg_wt = 0.0f, avg_tat = 0.0f;
    for (int i = 0; i < n; i++) {
        avg_wt += p[i].WaitingTime;
        avg_tat += p[i].TurnaroundTime;
    }
    if (n > 0) {
        avg_wt /= n;
        avg_tat /= n;
    }
    
    if (SaveResultsToFile(filename, algo, p, n, avg_wt, avg_tat)) {
        return 1; // Success
    }
    return 0; // Failure
}