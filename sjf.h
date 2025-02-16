#ifndef SJF_H
#define SJF_H

#include "parser.h"  // Ensure parser.h defines `process` structure
#include <stdio.h>

// Function to calculate total job duration for each process
int* calculate_total_job_duration(process **processes,int size);

// Function to print durations
void print_durations(int* arr,process **processes,int size);

void swap(int* a, int* b);

// SJF _Sorting
void SJF_sort_durations(int* arr,process **processes, int size);

#endif // SJF_H
