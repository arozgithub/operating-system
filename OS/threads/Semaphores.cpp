#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
//8.Semaphores (Dining Philosophers Problem):

sem_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int philosopherId = *((int *)arg);
    int leftFork = philosopherId;
    int rightFork = (philosopherId + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking\n", philosopherId);
        sleep(rand() % 5 + 1);

        sem_wait(&forks[leftFork]);
        sem_wait(&forks[rightFork]);

        printf("Philosopher %d is eating\n", philosopherId);
        sleep(rand() % 3 + 1);

        sem_post(&forks[leftFork]);
        sem_post(&forks[rightFork]);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherIds[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);
        philosopherIds[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&philosopherIds[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
        sem_destroy(&forks[i]);
    }

    return 0;
}

