#ifndef MLFQ_H
#define MLFQ_H

#include "parser.h"  // Includes process structure

// Multi-Level Feedback Queue Scheduler
void mlfq_schedule(process **processes);

// Helper function prototypes
void handle_arrivals(int current_time, process **processes, int *next_proc_index,
                     int total_processes, process *queue0[], int *front0, int *rear0);

void update_io_processes(int current_time, process *queue0[], int *front0, int *rear0);

process *schedule_running_process(int current_time,
                                  process *queue0[], int *front0, int *rear0,
                                  process *queue1[], int *front1, int *rear1,
                                  process *queue2[], int *front2, int *rear2,
                                  int *running_level, int *running_quantum);

void shift_jobs(process *p);

#endif // MLFQ_H
