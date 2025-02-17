#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "parser.h"
#include "utils.h" 
#include "rr.h"

#define TIME_SLICE 10

void RR(process **processes, int *duration, int size) {
    int timer = 0, completed = 0; // initialinsing timer , no of completed
    int *response_time = malloc(size * sizeof(int)); // response time list correseponding to each process
    int *turnaround_time = malloc(size * sizeof(int)); // turn_arround time list correseponding to each process
    int *flaglist = malloc(size * sizeof(int)); // flaglist to check which are the process that are currently in execution phase

    for (int i = 0; i < size; i++) {
        flaglist[i] = 0;            // initialising flag_list
        response_time[i] = -1;
    }

    int process_index = 0; // gets the first process that is enqueue to list based on arival time

    while (completed < size) {
        int executed = 0; // flag to see if any excution is taking place or not

        for (int i = 0; i < size; i++) {
            // Process must have arrived and not be completed
            if (flaglist[i] != 0 && duration[i] > 0) {
                executed = 1;
                // Mark response time if it's the first time the process runs
                if (response_time[i] == -1) {
                    response_time[i] = timer - processes[i]->arrival_time -1; // response time flag intial with -1
                }

                // the time slice could be Time slice or remaing duartion less than time slice
                int execute_time = (duration[i] > TIME_SLICE) ? TIME_SLICE : duration[i];
                duration[i] -= execute_time; // subtracting time slice 
                timer += execute_time;//timer is incremented as time slice if a process exist

                if (duration[i] == 0) { // if the duration of a process becomes 0
                    completed++;
                    turnaround_time[i] = timer-1;
                    flaglist[i] = 0;
                }
            }
        }

        // Enqueue processes that arrive at the current time
        while (process_index < size && processes[process_index]->arrival_time <= timer) { 
            flaglist[process_index] = 1; // if the timer has crossed the arrival time of process it will be add 
            process_index++; 
        }

        // If no processes were executed, move time forward
        if (!executed) {
            timer++;
        }
    }

    for (int i = 0; i < size; i++) {
    printf(" P%d \n Response time : %d \n Turn around time : %d \n",
           processes[i]->pid, response_time[i], turnaround_time[i]);
    }
     
    free(response_time);
    free(turnaround_time);
    free(flaglist);
}