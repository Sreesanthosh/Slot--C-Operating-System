#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Array of mutexes representing chopsticks
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

// Function for philosopher's behavior
void* philosopher(void* num) {
    int philosopher_id = *((int*)num);

    while (1) {
        // Philosopher is thinking
        printf("Philosopher %d is thinking.\n", philosopher_id);
        usleep(rand() % 1000);  // Simulate thinking time

        // Try to pick up the left chopstick (mutex)
        printf("Philosopher %d is trying to pick up left chopstick.\n", philosopher_id);
        pthread_mutex_lock(&chopsticks[philosopher_id]);

        // Try to pick up the right chopstick (mutex)
        printf("Philosopher %d is trying to pick up right chopstick.\n", philosopher_id);
        pthread_mutex_lock(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);

        // Philosopher starts eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        usleep(rand() % 1000);  // Simulate eating time

        // Put down the right chopstick
        pthread_mutex_unlock(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right chopstick.\n", philosopher_id);

        // Put down the left chopstick
        pthread_mutex_unlock(&chopsticks[philosopher_id]);
        printf("Philosopher %d put down left chopstick.\n", philosopher_id);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, (void*)&philosopher_ids[i]) != 0) {
            perror("Thread creation failed");
            exit(1);
        }
    }

    // Wait for philosopher threads to finish (this will never happen in this version)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}

