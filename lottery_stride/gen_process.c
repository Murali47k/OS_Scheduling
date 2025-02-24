#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int random_int(int min, int max) {
    return min + rand() % (max - min + 1); // random number generator
}

int main() {
    int n=5; // NUMBER of PROCESS


    srand(time(NULL)); 

    FILE *file = fopen("task.txt", "w"); // writing in file jobs.txt

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;  
    }

    for (int i = 1; i <= n; i++) {
        int tickets = random_int(0, 100); //generates random number for tickets
        int duration = random_int(10, 300); 
        fprintf(file,"P%d %d %d", i, tickets,duration);  
        fprintf(file,"\n");
    }

    fclose(file); // closing the file

    return 0;
}
