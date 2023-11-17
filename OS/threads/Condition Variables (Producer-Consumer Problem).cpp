#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 5
//4.Condition Variables (Producer-Consumer Problem):

int buffer[BUFFER_SIZE];
int itemCount = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufferNotEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t bufferNotFull = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while (itemCount == BUFFER_SIZE) {
            pthread_cond_wait(&bufferNotFull, &mutex);
        }
        buffer[itemCount++] = i;
        printf("Produced: %d\n", i);
        pthread_cond_signal(&bufferNotEmpty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while (itemCount == 0) {
            pthread_cond_wait(&bufferNotEmpty, &mutex);
        }
        int item = buffer[--itemCount];
        printf("Consumed: %d\n", item);
        pthread_cond_signal(&bufferNotFull);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
    return 0;
}

