#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    pid_t pid, parent_pid;
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    pid_t current_pid = getpid();
    pid_t parent_pid = getppid();

    if (pid == 0) {
        printf("Child Process:\n");
        printf("Current Process ID (PID): %d\n", current_pid);
        printf("Parent Process ID (PPID): %d\n", parent_pid);
    } else {
        printf("Parent Process:\n");
        printf("Current Process ID (PID): %d\n", current_pid);
        printf("Parent Process ID (PPID): %d\n", parent_pid);
    }
    return 0;
}

