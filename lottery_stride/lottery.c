#include <stdio.h>
#include <stdlib.h>
#include "parse_task.h"
#include <time.h>

int len_list(Process* head){
    int count=0;
    Process* trv=head;
    while(trv!=NULL){
        trv=trv->next;
        count+=1;
    }
    return count;
}

int random_int(int min, int max) {
    return min + rand() % (max - min + 1); // random number generator
}

int* cumulative_ticket_list(Process* head,int size){
    int* arr=(int *)malloc((size+1)*sizeof(int));
    int i=1;
    Process* trv=head;
    int cumm_ticket_sum=0;
    arr[0]=0;
    while(trv!=NULL){
        arr[i]=cumm_ticket_sum + trv->ticket;
        cumm_ticket_sum+=trv->ticket;
        trv=trv->next;
        i+=1;
    }
    return arr;
}

#define TIME_SLICE 10

void Lottery(Process* head, int *CTL, int size) {
    int timer = 0;
    int completed = 0; // Number of completed processes
    int *response_time = (int *)malloc(size * sizeof(int)); // Response times
    int *turnaround_time = (int *)malloc(size * sizeof(int)); // Turnaround times
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        response_time[i] = -1;
        turnaround_time[i] = -1;
    }

    while (completed < size) {
        Process* trv = head;
        Process* prev = NULL;
        int i = 1;

        int curr_ticket = random_int(0, CTL[size]);
        //printf("%d ",curr_ticket);
        // Find the process corresponding to the drawn lottery ticket
        while (trv != NULL) {
            if (CTL[i - 1] <= curr_ticket && curr_ticket < CTL[i]) {
                
                // printf("Selected ticket: %d -> Process: P%d (Remaining time: %d)\n", curr_ticket, trv->pid, trv->task_duration);

                if (trv->task_duration > TIME_SLICE) {
                    trv->task_duration -= TIME_SLICE;
                    if (response_time[i - 1] == -1) { // First execution
                        response_time[i - 1] = timer;
                    }
                    timer += TIME_SLICE;
                } else if(trv->task_duration <= TIME_SLICE && trv->task_duration > 0){ // Process completes
                    if (response_time[i - 1] == -1) { // First execution if task_duration == TIME_slice
                        response_time[i - 1] = timer;
                    }
                    timer += trv->task_duration;
                    if (turnaround_time[i - 1] == -1){
                        turnaround_time[i - 1] = timer;
                    }
                    completed++;

                    // Remove completed process from the linked list
                    if (prev == NULL) {
                        head = head->next;
                    } else {
                        prev->next = trv->next;
                    }
                    free(trv);
                }
                break;
            }
            prev = trv;
            trv = trv->next;
            i++;
        }
    }

    // Print response and turnaround times
    printf("\nProcess Scheduling Results:\n");
    for (int i = 0; i < size; i++) {
        printf("P%d -> Response Time: %d, Turnaround Time: %d\n", i + 1, response_time[i], turnaround_time[i]);
    }

    free(response_time);
    free(turnaround_time);
}
