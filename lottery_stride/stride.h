#ifndef STRIDE_H
#define STRIDE_H
#include <stdio.h>
#include <stdlib.h>
#include "parse_task.h"
#include <time.h>
#include "lottery.h"
#include <limits.h>

// Function to compute the Greatest Common Divisor (GCD)
int gcd(int a, int b);

// Function to compute the Least Common Multiple (LCM) of two numbers
int lcm(int a, int b);

// Function to find LCM of an array
int lcm_of_array(int arr[], int size);

// Function to compute the LCM of all process tickets
int lcm_tickets(Process* head);

// Function to compute the stride list for each process
int* stride_lst_of_process(Process* head);

// Function to find the index of the minimum value in an array
int find_min_index(int arr[], int size);

// Function to implement Stride scheduling algorithm
void Strides(Process* head, int* SL, int size);

#endif // STRIDE_H
