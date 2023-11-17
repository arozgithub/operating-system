#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//2. Mutexes (Printing Even and Odd Numbers):

void *printEven(void *arg) {
    for (int i = 2; i <= 10; i += 2) {
        pthread_mutex_lock(&mutex);
        printf("Even: %d\n", i);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *printOdd(void *arg) {
    for (int i = 1; i <= 9; i += 2) {
        pthread_mutex_lock(&mutex);
        printf("Odd: %d\n", i);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t evenThread, oddThread;
    pthread_create(&evenThread, NULL, printEven, NULL);
    pthread_create(&oddThread, NULL, printOdd, NULL);

    pthread_join(evenThread, NULL);
    pthread_join(oddThread, NULL);

    return 0;
}

