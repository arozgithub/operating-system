#include <pthread.h>
#include <semaphore.h>
#include <iostream>
using namespace std;

sem_t a, b;
int counter = 0;
bool t = true;

void* funp(void* num) {
    while (t) {
        sem_wait(&a);
        if (counter < 100) {
            counter++;
            cout << "thread1: " << counter << endl;
            sem_post(&b);
        } else {
            t = false;
            sem_post(&b); 
        }
    }
    pthread_exit(NULL);
}

void* func(void* num) {
    while (t) {
        sem_wait(&b);
        if (counter < 100) {
            counter++;
            cout << "thread2: " << counter << endl;
            sem_post(&a);
        } else {
            t = false;
            sem_post(&a); 
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer;
    pthread_t consumer;

    sem_init(&a, 0, 1);
    sem_init(&b, 0, 0);

    pthread_create(&producer, NULL, funp, NULL);
    pthread_create(&consumer, NULL, func, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&a);
    sem_destroy(&b);

    return 0;
}

