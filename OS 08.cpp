#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;                // Process ID
    int burst_time;         // Burst time (execution time)
    int remaining_time;     // Remaining time for execution
    int arrival_time;       // Arrival time of the process
    int completion_time;    // Completion time of the process
    int waiting_time;       // Waiting time for the process
    int turnaround_time;    // Turnaround time for the process
} Process;

// Function to calculate completion time for each process
void calculateCompletionTime(Process processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;
    int i;

    // Keep looping until all processes are completed
    while (completed < n) {
        int progress = 0; // To track if any process is executed in the current cycle

        // Iterate over all processes to execute them
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    processes[i].remaining_time -= quantum;
                    current_time += quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = current_time;
                    completed++;
                }
                progress = 1;
            }
        }

        // If no process is ready, increment time
        if (progress == 0) {
            current_time++;
        }
    }
}

// Function to calculate waiting time and turnaround time
void calculateTimes(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

// Function to print process details
void printProcessDetails(Process processes[], int n) {
    printf("\nProcess ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
               processes[i].pid,
               processes[i].burst_time,
               processes[i].arrival_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);
    }
}

// Function to calculate average waiting and turnaround times
void calculateAverageTimes(Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f", (float)total_turnaround_time / n);
}

int main() {
    int n, quantum;

    // Input the number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    Process processes[n];

    // Input the burst times and arrival times for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Process IDs are 1, 2, 3, ...
        printf("Enter burst time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
        printf("Enter arrival time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
    }

    // Calculate completion time for each process using Round Robin scheduling
    calculateCompletionTime(processes, n, quantum);

    // Calculate waiting time and turnaround time for each process
    calculateTimes(processes, n);

    // Print the process details
    printProcessDetails(processes, n);

    // Calculate and print the average waiting and turnaround times
    calculateAverageTimes(processes, n);

    return 0;
}

