// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    // Get the shared memory segment
    key_t key = ftok("reader.c", 65);  // Generate the same key as in writer
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment to our address space
    char *shm_ptr = (char*) shmat(shmid, NULL, 0);
    if (shm_ptr == (char*)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Read data from the shared memory
    printf("Reader: Reading from shared memory...\n");
    printf("Reader: %s\n", shm_ptr);

    // Detach the shared memory
    shmdt(shm_ptr);

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    printf("Reader: Exiting.\n");

    return 0;
}

