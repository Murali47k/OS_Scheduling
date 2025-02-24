#include "mlfq.h"
#include "utils.h"  // For enqueue and dequeue functions
#include <stdio.h>
#include <stdlib.h>

// Shifts the jobs array for a process (removing the first element)
void shift_jobs(process *p) {
    for (int i = 0; i < p->n_jobs - 1; i++) {
        p->jobs[i] = p->jobs[i+1];
    }
    p->n_jobs--;
}

// Handles arrivals at the current clock tick
void handle_arrivals(int current_time, process **processes, int *next_proc_index,int total_processes, process *queue0[], int *front0, int *rear0) {
    while (*next_proc_index < total_processes && processes[*next_proc_index]->arrival_time == current_time) {
        enqueue(queue0, front0, rear0, processes[*next_proc_index]);
        printf("Time %d: Process %d arrived and enqueued in Queue 0 (arrival time: %d)\n",
               current_time, processes[*next_proc_index]->pid,
               processes[*next_proc_index]->arrival_time);
        (*next_proc_index)++;
    }
}

// Updates processes in I/O; if finished, re-enqueues them to Queue 0
void update_io_processes(int current_time, process *queue0[], int *front0, int *rear0) {
    for (int i = 0; i < *rear0 + 1; i++) {
        process *p = queue0[i];
        if (p->n_jobs > 0 && p->jobs[0] % 2 == 1) { // Odd jobs are I/O
            p->jobs[0]--; // Decrement remaining I/O time
            if (p->jobs[0] == 0) {
                shift_jobs(p); // Remove completed I/O job
                printf("Time %d: Process %d finished I/O and enqueued in Queue 0\n",
                       current_time, p->pid);
                enqueue(queue0, front0, rear0, p);
            }
        }
    }
}

// Returns the next process to run from the highest priority non-empty queue
process *schedule_running_process(int current_time,
                                  process *queue0[], int *front0, int *rear0,
                                  process *queue1[], int *front1, int *rear1,
                                  process *queue2[], int *front2, int *rear2,
                                  int *running_level, int *running_quantum) {
    process *running = NULL;
    if (*front0 != -1) {
        running = dequeue(queue0, front0, rear0);
        *running_level = 0;
        *running_quantum = 10;
        printf("Time %d: Process %d started running from Queue 0\n",
               current_time, running->pid);
    } else if (*front1 != -1) {
        running = dequeue(queue1, front1, rear1);
        *running_level = 1;
        *running_quantum = 20;
        printf("Time %d: Process %d started running from Queue 1\n",
               current_time, running->pid);
    } else if (*front2 != -1) {
        running = dequeue(queue2, front2, rear2);
        *running_level = 2;
        *running_quantum = -1; // No quantum limit in Queue 2 (FCFS)
        printf("Time %d: Process %d started running from Queue 2\n",
               current_time, running->pid);
    }
    return running;
}

void mlfq_schedule(process **processes) {
    // Three separate queues for different priorities.
    process *queue0[MAX_PROCESSES];
    process *queue1[MAX_PROCESSES];
    process *queue2[MAX_PROCESSES];
    int front0 = -1, rear0 = -1;
    int front1 = -1, rear1 = -1;
    int front2 = -1, rear2 = -1;

    int current_time = 0;
    int total_processes = 0;
    while (processes[total_processes] != NULL)
        total_processes++;
    int next_proc_index = 0;

    process *running = NULL;
    int running_level = -1;   // 0 for Q0, 1 for Q1, 2 for Q2
    int running_quantum = 0;  // Remaining quantum for running process

    // Simulation loop continues while there are pending processes:
    while (front0 != -1 || front1 != -1 || front2 != -1 ||
           running != NULL || next_proc_index < total_processes) {
        // 1. Handle new arrivals.
        handle_arrivals(current_time, processes, &next_proc_index, total_processes,
                        queue0, &front0, &rear0);

        // 2. Update I/O processes and move them to queue0 if completed.
        update_io_processes(current_time, queue0, &front0, &rear0);

        // 3. If no process is running, schedule one.
        if (running == NULL) {
            // Before dequeuing, print the remaining burst time of the next process.
            if (front0 != -1) {
                printf("Time %d: Process %d has %d CPU burst time left before dequeuing.\n",
                       current_time, queue0[front0]->pid, queue0[front0]->jobs[0]);
            } else if (front1 != -1) {
                printf("Time %d: Process %d has %d CPU burst time left before dequeuing.\n",
                       current_time, queue1[front1]->pid, queue1[front1]->jobs[0]);
            } else if (front2 != -1) {
                printf("Time %d: Process %d has %d CPU burst time left before dequeuing.\n",
                       current_time, queue2[front2]->pid, queue2[front2]->jobs[0]);
            }

            running = schedule_running_process(current_time,
                                               queue0, &front0, &rear0,
                                               queue1, &front1, &rear1,
                                               queue2, &front2, &rear2,
                                               &running_level, &running_quantum);
        }

        if (running != NULL) {
            running->jobs[0]--; // Execute 1 time unit
            // Check if the process is done
            if (running->jobs[0] == 0) {
                printf("Time %d: Process %d completed execution\n", current_time+1, running->pid);
                running = NULL; // Remove the process
            } 
            else if (running_level != 2) {  // Q0 and Q1 have time slices
                running_quantum--;
                
                if (running_quantum == 0) {
                    if (running_level == 0) {
                        enqueue(queue1, &front1, &rear1, running);
                        printf("Time %d: Process %d quantum expired in Queue 0; moved to Queue 1\n", current_time+1, running->pid);
                    } else if (running_level == 1) {
                        enqueue(queue2, &front2, &rear2, running);
                        printf("Time %d: Process %d quantum expired in Queue 1; moved to Queue 2\n", current_time+1, running->pid);
                    }
                    running = NULL; // Stop running this process
                }
            }
        }
        current_time++; // Advance clock
    }
    printf("All processes completed. Total elapsed time: %d time units.\n", current_time);
}


