#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_JOBS  6 // creates up to max of 6 jobs

int random_int(int min, int max) {
    return min + rand() % (max - min + 1); // random number generator
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n); // number of process to be created

    srand(time(NULL)); 

    FILE *file = fopen("jobs.txt", "w"); // writing in file jobs.txt

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;  
    }

    for (int i = 1; i <= n; i++) {
        int start_time = random_int(0, 100); //generates random number for AT and save PID and AT
        fprintf(file,"P%d %d", i, start_time);  
        
        char job_type = 'C'; 
        int job_count = random_int(1, MAX_JOBS);

        for (int j = 0; j < job_count; j++) { // for random number of JOB created making time , 
                                              //even jobs are CPU whereas odd are I/O
            int duration = random_int(10, 300); 

            fprintf(file," %c %d", job_type, duration);

            if (job_type == 'C'){
                job_type = 'I';
            }
            else{
                job_type = 'C';
            }
        }
        fprintf(file,"\n");
    }

    fclose(file); // closing the file

    return 0;
}
