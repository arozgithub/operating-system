#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
//9.Barriers:

pthread_barrier_t barrier;

void *threadFunction(void *arg) {
    int threadId = *((int *)arg);
    printf("Thread %d is waiting at the barrier\n", threadId);
    pthread_barrier_wait(&barrier);
    printf("Thread %d passed the barrier\n", threadId);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];

    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; ++i) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, (void *)&threadIds[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}

