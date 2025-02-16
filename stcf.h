#ifndef STCF_H
#define STCF_H

#include <limits.h>
#include "parser.h"
#include "utils.h"


// Queue for managing processes
//extern process *Queue[MAX_PROCESSES]; 
extern int head, tail;

// Function prototypes
int find_shortest_job(int *duration, int head, int tail);
void STCF(process **processes, int *duration, int size);

#endif // STCF_H
