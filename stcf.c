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

        int current_index = find_shortest_job(duration, head, tail);
        
        if(current_index!=-1){
            if(flaglist[current_index]==0){
                response_time[current_index]=timer;
                flaglist[current_index]=1;
            }
            duration[current_index]-=1;
            if(duration[current_index]==0){
                turnaround_time[current_index]=timer+1;
                duration[current_index]=INT_MAX; // ending the process
                completed +=1;
            }
        }
        timer++;
    }

    for (int i = 0; i < size; i++) {
    printf(" P%d \n Response time : %d \n Turn around time : %d \n",
           processes[i]->pid, response_time[i], turnaround_time[i]);
    }

}