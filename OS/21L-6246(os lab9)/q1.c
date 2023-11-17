#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

 sem_t semaphore_a;
sem_t semaphore_sp;

int n = 5;
int x = 0;
int count = 0;

void *threadFunction1(void *arg) {
    count++;
    sem_wait(&semaphore_a);
    x = x + 1;
    printf("x shared variable is: %d\n", x);
    sem_post(&semaphore_a);

    
    pthread_exit(NULL);
}

void *threadFunction2(void *arg) {
if (count== 5) {
        sem_post(&semaphore_sp);
    }

    sem_wait(&semaphore_sp);
    printf("all threads have completed\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread[n];
    pthread_t special;

    // initializing semaphores with values
    sem_init(&semaphore_a, 0, 1);
    sem_init(&semaphore_sp, 0, 0);

    for (int i = 0; i < n; i++) {
        pthread_create(&thread[i], NULL, threadFunction1, NULL);
    }

    pthread_create(&special, NULL, threadFunction2, NULL);

    for (int i = 0; i < n; i++) {
        pthread_join(thread[i], NULL);
    }

    pthread_join(special, NULL);

    return 0;
}

