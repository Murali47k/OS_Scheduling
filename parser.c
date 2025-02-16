#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1000 // making max line length
#define MAX_PROCESSES 50 // max number of processes
#define MAX_JOBS 10

typedef struct __process { // process structure 
    int pid;
    int arrival_time;
    int n_jobs;
    int *jobs; // array of jobs (timing) even - CPU , odd - I/O
} process;


process **parse_jobs(const char *filename) {
    FILE *jobs_f = fopen(filename, "r");
    if (jobs_f == NULL) {
        fprintf(stderr, "Could not open file\n");
        return NULL;
    }

    static process *processes[MAX_PROCESSES]; // Static to persist after function returns
    char line[LINE_LENGTH];
    int i = 0;

    while (fgets(line, LINE_LENGTH, jobs_f) != NULL) { // take sthe line from the jobs.txt file
        processes[i] = malloc(sizeof(process)); // dynamically creating a process 
        process *p = processes[i];

        p->jobs = (int *)malloc(sizeof(int) * MAX_JOBS); // dynamically creating array for job timing
        p->n_jobs = 0;

        char *tok = strtok(line, " "); // tokeninxsing to store PID
        sscanf(tok, "P%d", &(p->pid));

        tok = strtok(NULL, " ");
        p->arrival_time = atoi(tok); // tokeninxsing to store AT

        while ((tok = strtok(NULL, " ")) != NULL) { // tokenising to store job time 
            tok = strtok(NULL, " ");
            if (tok == NULL) break;
            p->jobs[p->n_jobs] = atoi(tok);
            p->n_jobs += 1; // for each jobs incrementing number of jobs (n_jobs)
        }
        i += 1;
    }

    fclose(jobs_f);
    processes[i] = NULL;  // last process is stored as NULL pointer
    return processes; // returns a array of pointers to all process
}
