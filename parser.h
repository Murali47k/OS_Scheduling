#ifndef PARSER_H
#define PARSER_H

#define MAX_PROCESSES 50

typedef struct __process {
    int pid;
    int arrival_time;
    int n_jobs;
    int *jobs;
} process;

process **parse_jobs(const char *filename);

#endif 