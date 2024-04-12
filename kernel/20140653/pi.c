#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h> // For getpid()

#define NUM_THREADS 2
#define NUM_POINTS 1000000
#define RADIUS 1

long points_in_circle = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *throw_darts(void *param) {
    int tid = *((int *)param);
    unsigned int rand_state = tid + time(NULL);
    long local_points_in_circle = 0;

    for (int i = 0; i < NUM_POINTS/NUM_THREADS; i++) {
        double x = (double)rand_r(&rand_state) / RAND_MAX * 2 - 1;
        double y = (double)rand_r(&rand_state) / RAND_MAX * 2 - 1;
        if (sqrt(x * x + y * y) <= RADIUS) {
            local_points_in_circle++;
        }
    }

    // Lock the mutex before updating the global count
    pthread_mutex_lock(&mutex);
    points_in_circle += local_points_in_circle;
    pthread_mutex_unlock(&mutex);

    // Print the thread's results
    printf("Thread %d (PID %d): 원안에 포인트 %ld \n", tid, getpid(), local_points_in_circle);
    pthread_exit(0);
}

int pi() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Reset global counter before creating threads
    points_in_circle = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Create the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, throw_darts, (void *)&thread_args[i]);
    }

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Calculate and print the estimated value of pi
    double pi_estimate = 4 * (double)points_in_circle / NUM_POINTS;
    printf("Parent (PID %d): 예측된 pi 값: %f\n", getpid(), pi_estimate);

    return 0;
}
