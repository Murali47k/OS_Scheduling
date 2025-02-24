#ifndef LOTTERY_H
#define LOTTERY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parse_task.h"

// Function prototypes
int len_list(Process* head);
int random_int(int min, int max);
int* cumulative_ticket_list(Process* head, int size);
void Lottery(Process* head, int *CTL, int size);

#endif // LOTTERY_H