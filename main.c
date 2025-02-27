#include <stdio.h>
#include <stdlib.h>
#include "parser.h" // headers for parser "parse_jobs"
#include "utils.h" // enqueue,dequeue,print_queue, RT_TAT_print
#include "fifo.h" // function for sort_AT 
#include "sjf.h" // sorting according to sjf , forming duration 
#include "stcf.h" // stcf ,stcf_IO 
#include "rr.h" // RR 
#include "mlfq.h" //mlfq


process *processes_Q[MAX_PROCESSES]; // Queue stored in main
int front = -1, rear = -1;

// Function to perform FIFO scheduling
void fifo_schedule(process **processes) {
    int tat = 0; //Turn around time
    for (int i = 0; processes[i] != NULL; i++) {
        enqueue(processes_Q, &front, &rear, processes[i]); // enqueue all process in processes_Q
    }

    printf("\n Queue before sorting: \n");
    print_process(processes_Q);

    sort_AT(processes_Q, rear - front + 1); //sorting based on AT - rear - front + 1 is the size of queue

    printf("\n Queue after sorting:\n ");
    print_process(processes_Q);

    printf("\n Dequeuing processes: \n");
    printf("\n");
    while (front != -1) {
        process *p = dequeue(processes_Q, &front, &rear); // dequeing from the processes_Q
        tat = RT_TAT_print(p,tat);
    }
}

void sjf_schedule(process **processes){
    int tat = 0; //Turn around time
    for (int i = 0; processes[i] != NULL; i++) {
        enqueue(processes_Q, &front, &rear, processes[i]);  // enqueue all process in processes_Q
    }

    printf("\n Queue before sorting: \n");
    print_process(processes_Q);

    int* duration=calculate_total_job_duration(processes_Q,rear - front + 1); //rear - front + 1 is the size of queue
    SJF_sort_durations(duration,processes_Q,rear - front + 1);
    print_durations(duration,processes_Q,rear - front + 1);

    printf("\n Dequeuing processes: \n");
    printf("\n");
    while (front != -1) {
        process *p = dequeue(processes_Q, &front, &rear); // dequeing from the processes_Q
        tat = RT_TAT_print(p,tat);
    }
}

void stcf_schedule(process **processes){
    for (int i = 0; processes[i] != NULL; i++) {
        enqueue(processes_Q, &front, &rear, processes[i]);  // enqueue all process in processes_Q
    }

    printf("\n Queue before sorting: \n");
    print_process(processes_Q);

    sort_AT(processes_Q, rear - front + 1);
    int* duration=calculate_total_job_duration(processes_Q,rear - front + 1);

    STCF(processes_Q,duration,rear - front + 1);

}

void stcf_io_schedule(process **processes){
    for (int i = 0; processes[i] != NULL; i++) {
        enqueue(processes_Q, &front, &rear, processes[i]);  // enqueue all process in processes_Q
    }

    printf("\n Queue before sorting: \n");
    print_process(processes_Q);

    sort_AT(processes_Q, rear - front + 1);

    STCF_IO(processes_Q,rear - front + 1);

}

void rr_schedule(process **processes){
    for (int i = 0; processes[i] != NULL; i++) {
        enqueue(processes_Q, &front, &rear, processes[i]);  // enqueue all process in processes_Q
    }

    printf("\n Queue before sorting: \n");
    print_process(processes_Q);

    sort_AT(processes_Q, rear - front + 1);
    int* duration=calculate_total_job_duration(processes_Q,rear - front + 1);

    RR(processes_Q,duration,rear - front + 1);
}

void mlfq(process **processes){
    for (int i = 0; processes[i] != NULL; i++) {
        enqueue(processes_Q, &front, &rear, processes[i]);  // enqueue all process in processes_Q
    }

    printf("\n Queue before sorting: \n");
    print_process(processes_Q);

    sort_AT(processes_Q, rear - front + 1);
    mlfq_schedule(processes_Q);
    
}

int main() {
    process **processes = parse_jobs("jobs.txt");
    if (processes == NULL) {
        printf("No processes\n");
        return 1; 
    }

    // Call FIFO scheduling function
    //fifo_schedule(processes);

    // Call SJF scheduling function
    //sjf_schedule(processes);
    
    //Call STCF function without IO awareness
    //stcf_schedule(processes);

    //Call STCF function with IO awareness
    //stcf_io_schedule(processes);

    //Call RR function with IO awareness
    //rr_schedule(processes);

    //Call MLFQ function 
    mlfq(processes);

    return 0;
}





