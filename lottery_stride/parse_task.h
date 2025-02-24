#ifndef PARSE_TASK_H
#define PARSE_TASK_H

typedef struct Process {
    int pid;            
    int ticket;         
    int task_duration;  
    struct Process *next; 
} Process;

void parse_file(const char* filename, Process** head); 

#endif 