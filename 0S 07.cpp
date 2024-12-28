#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;                // Process ID
    int burst_time;         // Burst time (execution time)
    int arrival_time;       // Arrival time
    int waiting_time;       // Waiting time for the process
    int turnaround_time;    // Turnaround time for the process
    int completion_time;    // Completion time for the process
} Process;

// Function to sort processes by arrival time (to handle arrival order)
void sortByArrivalTime(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to sort processes by burst time (used in SJF)
void sortByBurstTime(Process processes[], int n, int current_time) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sorting processes that have arrived and are ready for execution
            if (processes[i].arrival_time <= current_time && processes[i].burst_time > processes[j].burst_time && processes[j].arrival_time <= current_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to calculate completion time for each process
void calculateCompletionTime(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int i;

    while (completed < n) {
        // Sort processes by burst time for those that have arrived
        sortByBurstTime(processes, n, current_time);
        
        // Find the next process to execute
        int min_burst_time_idx = -1;
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
                min_burst_time_idx = i;
                break;
            }
        }

        if (min_burst_time_idx == -1) {
            current_time++;  // No process is ready to execute, so move time forward
            continue;
        }

        // Execute the selected process
        current_time += processes[min_burst_time_idx].burst_time;
        processes[min_burst_time_idx].completion_time = current_time;
        completed++;
    }
}

// Function to calculate waiting time and turnaround time for each process
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
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input the burst times and arrival times for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Process IDs are 1, 2, 3, ...
        printf("Enter burst time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        printf("Enter arrival time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
    }

    // Sort the processes by arrival time
    sortByArrivalTime(processes, n);

    // Calculate completion time for each process
    calculateCompletionTime(processes, n);

    // Calculate waiting time and turnaround time for each process
    calculateTimes(processes, n);

    // Print the process details
    printProcessDetails(processes, n);

    // Calculate and print the average waiting and turnaround times
    calculateAverageTimes(processes, n);

    return 0;
}

