#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "sjf.h"

int* calculate_total_job_duration(process **processes,int size){// calculates the total duartion of all jobs in a process
    int* job_total_duration=malloc(size * sizeof(int));         // stores it in a array
    for (int i = 0; processes[i] != NULL; i++){
        int time=0;
        for(int j=0;j < processes[i]->n_jobs;j++){
            time+=processes[i]->jobs[j];
        }
        job_total_duration[i]=time;
    } 
    return job_total_duration;
}

void swap(int* a, int* b) { // simple int swap function
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SJF_sort_durations(int* arr,process **processes, int size) { // sorting based of SJF the process_Q
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            process *temp;
            if(arr[j] > arr[j + 1]) {  
                swap(&arr[j], &arr[j + 1]);
                temp = processes[j + 1];
                processes[j+1] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void print_durations(int* arr,process **processes,int size){
    printf("SJF durations of sorted process \n");
    for(int i=0;i<size;i++){
        printf("P%d : total time = %d\n",processes[i]->pid,arr[i]);
    }
    printf("\n");
}

