#include <stdio.h>

typedef struct {
    int pid;              // Process ID
    int burst_time;       // Burst time (execution time)
    int waiting_time;     // Waiting time
    int turnaround_time;  // Turnaround time
    int completion_time;  // Completion time
} Process;

// Function to calculate waiting time for each process
void calculateWaitingTime(Process processes[], int n) {
    processes[0].waiting_time = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].completion_time;
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

// Function to calculate completion time for each process
void calculateCompletionTime(Process processes[], int n) {
    processes[0].completion_time = processes[0].burst_time; // Completion time of first process
    for (int i = 1; i < n; i++) {
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
    }
}

// Function to sort processes by burst time (Shortest Job First)
void sortByBurstTime(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                // Swap the processes if they are in the wrong order
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to print the process details
void printProcessDetails(Process processes[], int n) {
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].burst_time, 
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
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input the burst times for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Process IDs are 1, 2, 3, ...
        printf("Enter burst time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }

    // Sort the processes by burst time
    sortByBurstTime(processes, n);

    // Calculate completion time, waiting time, and turnaround time
    calculateCompletionTime(processes, n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    // Print the process details
    printProcessDetails(processes, n);

    // Calculate and print the average waiting and turnaround times
    calculateAverageTimes(processes, n);

    return 0;
}

