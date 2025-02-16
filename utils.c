#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"  

void enqueue(process **processes_Q, int *front, int *rear, process *p) { // basic circular queue enque function to enqueue a process
    if ((*rear + 1) % MAX_PROCESSES == *front) {
        printf("Queue overflow\n");
        return;
    } 

    if (*front == -1) {
        *front = 0; 
    }

    *rear = (*rear + 1) % MAX_PROCESSES;  
    processes_Q[*rear] = p;
}

process *dequeue(process **processes_Q, int *front, int *rear) { // basic dequeue function to dequeue a process 
    if (*front == -1) {
        printf("Queue underflow\n");
        return NULL;
    }

    process *dequeued_process = processes_Q[*front];
    printf(" Process %d is the dequeued value \n", dequeued_process->pid); // prints teh dequeued process

    if (*front == *rear) { 
        *front = -1;
        *rear = -1;
    } else {
        *front = (*front + 1) % MAX_PROCESSES;
    }

    return dequeued_process;
}

void print_process(process **processes) {
    for (int i = 0; processes[i] != NULL; i++) {
        process *p = processes[i];
        printf(" PID:\t%d\n AT:\t%d\n", p->pid, p->arrival_time); // printing the pid and AT

        for (int j = 0; j < p->n_jobs; j++) {
            if (j % 2 == 0) printf(" CPU:\t%d\n", p->jobs[j]); // print the cpu and i/o time of each job in process
            else printf(" I/O:\t%d\n", p->jobs[j]);
        }
        printf("\n");
    }
}

int RT_TAT_print(process *p,int tat){
    int TAT = tat;
    int RT = abs(TAT - p->arrival_time); // Calculating Response Time
    for(int i = 0;i < p->n_jobs; i++){
        TAT += p->jobs[i]; // Calculating Turn-around Time
    }
    printf("\n Response time : %d \n Turn around time : %d \n",RT,TAT);
    printf("\n");
    return TAT;
}