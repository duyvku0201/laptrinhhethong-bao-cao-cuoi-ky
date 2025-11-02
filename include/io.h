#ifndef IO_H
#define IO_H

#include "process.h"

int read_from_file(const char* filename, Process p[], int* n);
int read_from_keyboard(Process p[], int* n);
int write_to_file(const char* filename, Process p[], int n, const char* algo);

#endif
