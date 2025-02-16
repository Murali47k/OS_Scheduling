#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "fifo.h"  

void sort_AT(process **processes_Q, int size) { // sorting the queue based on each process AT 
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (processes_Q[j]->arrival_time > processes_Q[j + 1]->arrival_time) {
                process *temp = processes_Q[j];
                processes_Q[j] = processes_Q[j + 1];
                processes_Q[j + 1] = temp;
            }
        }
    }
}

