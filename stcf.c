#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "parser.h"
#include "utils.h" 
#include "stcf.h"

//process *Queue[MAX_PROCESSES]; // Queue stored in main
int head = 0, tail = -1;

int find_shortest_job(int *duration, int head, int tail) {
    int min_time = INT_MAX;
    int x = -1;
    for (int i = head; i <= tail; i++) {
        if (duration[i] < min_time) {
            min_time = duration[i];
            x = i;
        }
    }
    return x;
}

void STCF(process **processes,int *duration,int size){
    int timer = 0, completed = 0;
    int* response_time =malloc(size * sizeof(int));
    int* turnaround_time = malloc(size * sizeof(int));
    int* flaglist = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        flaglist[i] = 0;
    }
    int process_index = 0;

    while (completed < size){
        // Enqueue processes that have arrived
        while (process_index < size && processes[process_index]->arrival_time == timer) {// while because if two process 
            //enqueue(Queue, &head, &tail, processes[process_index]);               // have the same arrival time
            process_index++;
            tail++;
        }

        int current_index = find_shortest_job(duration, head, tail);// finds the current shortest job available
        
        if(current_index!=-1){
            if(flaglist[current_index]==0){
                response_time[current_index]=timer;// to caluculate when the process is selected RT
                flaglist[current_index]=1;
            }
            duration[current_index]-=1;
            if(duration[current_index]==0){ // end of process
                turnaround_time[current_index]=timer+1; //TAT is calculated
                duration[current_index]=INT_MAX; // ending the process
                completed +=1;
            }
        }
        timer++;//clock timer increase
    }

    for (int i = 0; i < size; i++) {
    printf(" P%d \n Response time : %d \n Turn around time : %d \n",
           processes[i]->pid, response_time[i], turnaround_time[i]);
           printf("\n");
    }

}


void STCF_IO(process **processes, int size) {
    int timer = 0, finished_count = 0;
    
    // Arrays to track each process's current CPU or I/O remaining time,
    // the index of the current job, response and turnaround times,
    // and a flag to indicate if response time has been recorded.
    int *cpu_remaining = malloc(size * sizeof(int));
    int *io_remaining  = malloc(size * sizeof(int));
    int *job_index     = malloc(size * sizeof(int)); // current job index in the jobs array
    int *response_time = malloc(size * sizeof(int));
    int *turnaround_time = malloc(size * sizeof(int));
    int *started       = calloc(size, sizeof(int));  // 0: not started, 1: started

    // Process state: 
    // 0 = not arrived, 1 = ready, 2 = running, 3 = in I/O, 4 = finished
    int *state = malloc(size * sizeof(int));

    // Initialize each process
    for (int i = 0; i < size; i++) {
        job_index[i] = 0;
        cpu_remaining[i] = processes[i]->jobs[0]; // first job is always a CPU burst
        io_remaining[i] = 0;
        if (processes[i]->arrival_time <= 0) {
            state[i] = 1;  // ready
        } else {
            state[i] = 0;  // not arrived yet
        }
    }
    
    // Simulation loop: run until all processes are finished
    while (finished_count < size) {
        // Check and mark new arrivals
        for (int i = 0; i < size; i++) {
            if (state[i] == 0 && processes[i]->arrival_time <= timer) {
                state[i] = 1; // process becomes ready
            }
        }

        // Process I/O: for processes in I/O state, decrement their I/O timer.
        // When an I/O burst finishes, move to the next job (which is a CPU burst).
        for (int i = 0; i < size; i++) {
            if (state[i] == 3) {
                io_remaining[i]--;
                if (io_remaining[i] <= 0) {
                    // I/O completed, move to next job (CPU burst)
                    job_index[i]++;
                    if (job_index[i] < processes[i]->n_jobs) {
                        cpu_remaining[i] = processes[i]->jobs[job_index[i]];
                        state[i] = 1;  // ready to run
                    } else {
                        state[i] = 4;  // finished
                        turnaround_time[i] = timer + 1;
                        finished_count++;
                    }
                }
            }
        }
        
        // Preempt any process currently marked as running.
        // (We treat them as ready so that the scheduler can re-check for the shortest job.)
        for (int i = 0; i < size; i++) {
            if (state[i] == 2)
                state[i] = 1;
        }
        
        // CPU scheduling: select the ready process with the shortest remaining CPU burst.
        int selected = -1;
        int min_remaining = INT_MAX;
        for (int i = 0; i < size; i++) {
            if ((state[i] == 1 || state[i] == 2) && cpu_remaining[i] < min_remaining) {
                selected = i;
                min_remaining = cpu_remaining[i];
            }
        }
        
        // If a process is selected, run it for one time unit.
        if (selected != -1) {
            if (!started[selected]) {
                response_time[selected] = timer;
                started[selected] = 1;
            }
            state[selected] = 2; // mark as running
            cpu_remaining[selected]--;  // run for 1 tick
            
            // If the CPU burst completes...
            if (cpu_remaining[selected] <= 0) {
                job_index[selected]++; // move past the finished CPU burst
                if (job_index[selected] < processes[selected]->n_jobs) {
                    // Next job should be an I/O burst.
                    io_remaining[selected] = processes[selected]->jobs[job_index[selected]];
                    state[selected] = 3; // process is now in I/O
                } else {
                    // No more jobs: process is finished.
                    state[selected] = 4;
                    turnaround_time[selected] = timer + 1;
                    finished_count++;
                }
            }
        }
        
        timer++; // increment the simulation clock
    }
    
    // Print the response time and turnaround time for each process
    for (int i = 0; i < size; i++) {
        printf("P%d \n Response time : %d \n Turn around time : %d \n\n",
               processes[i]->pid, response_time[i], turnaround_time[i]);
    }
    
    // Clean up allocated memory
    free(cpu_remaining);
    free(io_remaining);
    free(job_index);
    free(response_time);
    free(turnaround_time);
    free(started);
    free(state);
}
