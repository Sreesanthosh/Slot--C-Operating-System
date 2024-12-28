#include <stdio.h>

typedef struct {
    int pid;        // Process ID
    int burst_time; // Burst time
    int start_time; // Start time
    int completion_time; // Completion time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
} Process;

void findWaitingTime(Process processes[], int n) {
    // The first process has no waiting time
    processes[0].waiting_time = 0;

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].completion_time;
    }
}

void findTurnaroundTime(Process processes[], int n) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time;
    }
}

void findCompletionTime(Process processes[], int n) {
    // Calculate completion time for each process
    processes[0].completion_time = processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
    }
}

void findAverageTimes(Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Find total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage waiting time = %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time = %.2f\n", (float)total_turnaround_time / n);
}

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

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }

    // Calculate the completion time, waiting time, and turnaround time
    findCompletionTime(processes, n);
    findWaitingTime(processes, n);
    findTurnaroundTime(processes, n);

    // Print the process details
    printProcessDetails(processes, n);

    // Calculate and print the average waiting time and turnaround time
    findAverageTimes(processes, n);

    return 0;
}

