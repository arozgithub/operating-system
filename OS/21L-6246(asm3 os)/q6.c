#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#define NUM_PHILOSOPHERS 5
#define PHILOSOPHERS 5

sem_t chopstick[NUM_PHILOSOPHERS];

void *eat(void *arg) {
int i=0;
    int num = *((int *)arg);

    int left_chopstick = num;
    int right_chopstick = (num + 1) % NUM_PHILOSOPHERS;

    while (i<2) {//each philosopher can eat atmost two times in my logic
        printf("Philosopher %d is thinking\n", num);

        sem_wait(&chopstick[left_chopstick]);
        sem_wait(&chopstick[right_chopstick]);

        printf("Philosopher %d is eating with %d, %d\n", num, left_chopstick, right_chopstick);

        sleep(2); // Eating

        sem_post(&chopstick[left_chopstick]);
        sem_post(&chopstick[right_chopstick]);
        i++;
        
    }

    pthread_exit(NULL);
}

int main() {
    int philosopher[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};
    pthread_t threads[NUM_PHILOSOPHERS];

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        if (sem_init(&chopstick[i], 0, 1) != 0) {
            perror("Semaphore initialization failed");
            exit(EXIT_FAILURE);
        }
    }

   

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        if (pthread_create(&threads[i], NULL, eat, &philosopher[i]) != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(threads[i], NULL);
    }

    
    return 0;
}


