#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 20  // Increased max line length for flexibility

// Define a process structure for a linked list
typedef struct Process {
    int pid;            // Process ID (P1 -> 1, P2 -> 2, etc.)
    int ticket;         // Number of tickets assigned
    int task_duration;  // Total CPU workload
    struct Process *next; // Pointer to the next process
} Process;

// Function to create a new process node
Process* create_process(int pid, int ticket, int task_duration) {
    Process* new_proc = (Process*)malloc(sizeof(Process));
    if (!new_proc) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_proc->pid = pid;
    new_proc->ticket = ticket;
    new_proc->task_duration = task_duration;
    new_proc->next = NULL;
    return new_proc;
}

// Function to insert a process into the linked list
void insert_process(Process** head, int pid, int ticket, int task_duration) {
    Process* new_proc = create_process(pid, ticket, task_duration);
    
    if (*head == NULL) {
        *head = new_proc;
    } else {
        Process* temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_proc;
    }
}

// Function to parse the input file
void parse_file(const char* filename, Process** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        int pid, ticket, task_duration;
        char pname[5]; // Assuming max "Pxx" format

        // Parse the line (Example: "P1 55 102")
        if (sscanf(line, "%s %d %d", pname, &ticket, &task_duration) == 3) {
            // Extract process number (P1 -> 1, P2 -> 2, etc.)
            pid = atoi(&pname[1]);

            // Insert into linked list
            insert_process(head, pid, ticket, task_duration);
        }
    }

    fclose(file);
}

// Function to print the linked list
void print_processes(Process* head) {
    Process* temp = head;
    while (temp) {
        printf("Process ID: %d, Tickets: %d, Task Duration: %d\n", 
               temp->pid, temp->ticket, temp->task_duration);
        temp = temp->next;
    }
}

// Free linked list memory
void free_list(Process* head) {
    Process* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// // Main function
// int main() {
//     Process* process_list = NULL;

//     // Parse the input file
//     parse_file("task.txt", &process_list);

//     // Print the processes
//     print_processes(process_list);

//     // Free memory
//     free_list(process_list);

//     return 0;
// }


