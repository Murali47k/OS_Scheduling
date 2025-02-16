#ifndef UTILS_H
#define UTILS_H

#include "parser.h"  
#include <stdio.h>

void enqueue(process **processes_Q, int *front, int *rear, process *p);

process *dequeue(process **processes_Q, int *front, int *rear);

void print_process(process **processes);

int RT_TAT_print(process *p,int tat);

#endif //UTILS_H