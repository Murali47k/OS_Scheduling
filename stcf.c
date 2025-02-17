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

int* calculate_first_job_duration(process **processes,int size){// calculates the duartion of first jobs in a process
    int* job_total_duration=malloc(size * sizeof(int));         // stores it in a array
    for (int i = 0; processes[i] != NULL; i++){
        job_total_duration[i]=processes[i]->jobs[0];
    } 
    return job_total_duration;
}

void STCF_IO(process **processes,int *duration,int size){
    int timer = 0, completed = 0;
    int* response_time =malloc(size * sizeof(int));
    int* turnaround_time = malloc(size * sizeof(int));
    int* flaglist = malloc(size * sizeof(int));
    int* njob_donelist = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        flaglist[i] = 0;
        njob_donelist[i]=1;// number of job currently choesen in a process
    }
    int process_index = 0;

    while (completed < size){
        // Enqueue processes that have arrived
        while (process_index < size && processes[process_index]->arrival_time == timer) {// while because if two process 
            //enqueue(Queue, &head, &tail, processes[process_index]);               // have the same arrival time
            process_index++;
            tail++;
        }

        int current_index = find_shortest_job(duration, head, tail);// calulate teh smallest duration job available
        
        if(current_index!=-1){
            if(flaglist[current_index]==0){
                response_time[current_index]=timer; // calculating current RT
                flaglist[current_index]=1;
            }
            duration[current_index]-=1;
            if(duration[current_index]==0){
                if(njob_donelist[current_index] < processes[current_index]->n_jobs){//if first job is done , takes next job
                    duration[current_index] = processes[current_index]->jobs[njob_donelist[current_index]];
                    njob_donelist[current_index]+=1;//increments njob_done list
                }
                else{// all the job are over
                turnaround_time[current_index]=timer+1;//TAT is end of process time
                duration[current_index]=INT_MAX; // ending the process
                completed +=1;
                }
            }
        }
        timer++;
    }

    for (int i = 0; i < size; i++) {
    printf(" P%d \n Response time : %d \n Turn around time : %d \n",
           processes[i]->pid, response_time[i], turnaround_time[i]);
           printf("\n");
    }
}
