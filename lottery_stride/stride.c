#include <stdio.h>
#include <stdlib.h>
#include "parse_task.h"
#include <time.h>
#include "lottery.h"
#include <limits.h>

#define TIME_SLICE 10
// Function to compute the Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute the Least Common Multiple (LCM) of two numbers
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;  // Prevents overflow
}

// Function to find LCM of an array
int lcm_of_array(int arr[], int size) {
    int result = arr[0];  // Start with first element
    for (int i = 1; i < size; i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}

int lcm_tickets(Process* head){
    int* arr=(int *)malloc(len_list(head)*sizeof(int));
    int i=0;
    Process* trv=head;
    while(trv!=NULL){
        arr[i]=trv->ticket;
        trv=trv->next;
        i++;
    }

    return lcm_of_array(arr,len_list(head));
}

int* stride_lst_of_process(Process* head){
    int* arr=(int *)malloc(len_list(head)*sizeof(int));
    int i=0;
    int lcm=lcm_tickets(head);
    Process* trv=head;
    while(trv!=NULL){
        arr[i]=lcm / trv->ticket;
        trv=trv->next;
        i++;
    }
    return arr;
}

int find_min_index(int arr[], int size) {
    int min_index = 0; 
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;  
        }
    }
    return min_index;
}


void Strides(Process* head, int* SL, int size) {//SL= stride list
    int timer = 0;
    int completed = 0; // Number of completed processes
    int *response_time = (int *)malloc(size * sizeof(int)); // Response times
    int *turnaround_time = (int *)malloc(size * sizeof(int)); // Turnaround times
    int *steps_per_process = (int *)malloc(size * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        response_time[i] = -1;
        turnaround_time[i] = -1;
        steps_per_process[i]=0;
    }

    while (completed < size) {
        Process* trv = head;
        Process* prev = NULL;
        int i = 0;
        // for(int j=0;j<size;j++){
        //     printf("%d ",steps_per_process[j]);
        // }
        // printf("\n");
        int curr_stride=find_min_index(steps_per_process,size);
        while (trv != NULL) {
            if (i==curr_stride) {
                if (trv->task_duration > TIME_SLICE) {
                    trv->task_duration -= TIME_SLICE;
                    steps_per_process[i]+=SL[i];
                    if (response_time[i] == -1) { // First execution
                        response_time[i] = timer;
                    }
                    timer += TIME_SLICE;
                } else if(trv->task_duration <= TIME_SLICE && trv->task_duration > 0){ // Process completes
                    if (response_time[i] == -1) { // First execution if task_duration == TIME_slice
                        response_time[i] = timer;
                    }
                    timer += trv->task_duration;
                    if (turnaround_time[i] == -1){
                        turnaround_time[i] = timer;
                        
                    }
                    steps_per_process[i]=INT_MAX;
                    //steps_per_process[i]+=SL[i];
                    completed++;

                    //Remove completed process from the linked list
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

