#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;                // Process ID
    int burst_time;         // Burst time (execution time)
    int priority;           // Priority (lower value indicates higher priority)
    int arrival_time;       // Arrival time of the process
    int remaining_time;     // Remaining time for execution
    int start_time;         // Start time for the process execution
    int completion_time;    // Completion time for the process
    int waiting_time;       // Waiting time for the process
    int turnaround_time;    // Turnaround time for the process
} Process;

// Function to sort processes by arrival time
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

// Function to perform Preemptive Priority Scheduling
void preemptivePriorityScheduling(Process processes[], int n) {
    int time = 0;
    int completed = 0;
    int i;
    int highest_priority_idx;
    int all_completed = 0;

    while (completed < n) {
        // Find the process with the highest priority that has arrived
        highest_priority_idx = -1;
        int min_priority = 9999; // To store the smallest priority found

        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                highest_priority_idx = i;
            }
        }

        if (highest_priority_idx == -1) {
            // No process is ready to execute, increment time
            time++;
            continue;
        }

        // Process the selected process for 1 unit of time
        if (processes[highest_priority_idx].remaining_time == processes[highest_priority_idx].burst_time) {
            processes[highest_priority_idx].start_time = time;
        }

        processes[highest_priority_idx].remaining_time--;
        time++;

        // If the process completes, calculate its completion, turnaround, and waiting times
        if (processes[highest_priority_idx].remaining_time == 0) {
            processes[highest_priority_idx].completion_time = time;
            processes[highest_priority_idx].turnaround_time = processes[highest_priority_idx].completion_time - processes[highest_priority_idx].arrival_time;
            processes[highest_priority_idx].waiting_time = processes[highest_priority_idx].turnaround_time - processes[highest_priority_idx].burst_time;
            completed++;
        }
    }
}

// Function to print the process details
void printProcessDetails(Process processes[], int n) {
    printf("\nProcess ID\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
               processes[i].pid,
               processes[i].burst_time,
               processes[i].arrival_time,
               processes[i].priority,
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

    // Input the burst times, arrival times, and priorities for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Process IDs are 1, 2, 3, ...
        printf("Enter burst time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
        printf("Enter arrival time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter priority for Process %d (lower number = higher priority): ", processes[i].pid);
        scanf("%d", &processes[i].priority);
    }

    // Sort the processes by arrival time
    sortByArrivalTime(processes, n);

    // Perform preemptive priority scheduling
    preemptivePriorityScheduling(processes, n);

    // Print the process details
    printProcessDetails(processes, n);

    // Calculate and print the average waiting and turnaround times
    calculateAverageTimes(processes, n);

    return 0;
}

