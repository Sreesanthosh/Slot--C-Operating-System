#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000  // Size of the array
#define NUM_THREADS 2    // Number of threads

// Shared data
int arr[ARRAY_SIZE];
long long result = 0;  // Result variable to store sum
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for synchronization

// Thread function to calculate sum of a section of the array
void* sum_array_part(void* arg) {
    int start_index = *((int*)arg);  // Start index for this thread
    int end_index = start_index + ARRAY_SIZE / NUM_THREADS;
    long long local_sum = 0;
    
    // Calculate sum for the assigned section
    for (int i = start_index; i < end_index; i++) {
        local_sum += arr[i];
    }

    // Synchronize access to shared variable 'result' using mutex
    pthread_mutex_lock(&mutex);  // Lock the mutex
    result += local_sum;         // Update the shared result
    pthread_mutex_unlock(&mutex); // Unlock the mutex

    return NULL;
}

int main() {
    // Initialize the array with some values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i + 1;  // Array values from 1 to ARRAY_SIZE
    }

    pthread_t threads[NUM_THREADS];  // Thread array
    int indices[NUM_THREADS];        // Start indices for each thread

    // Create threads to calculate sum in different sections of the array
    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i * (ARRAY_SIZE / NUM_THREADS);  // Set start index for each thread
        if (pthread_create(&threads[i], NULL, sum_array_part, &indices[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Output the final result
    printf("Total sum of the array: %lld\n", result);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

