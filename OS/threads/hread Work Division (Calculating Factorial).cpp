#include <stdio.h>
#include <pthread.h>
//3. Thread Work Division (Calculating Factorial):

unsigned long long factorial = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculateFactorial(void *arg) {
    int n = *((int *)arg);
    for (int i = 1; i <= n; ++i) {
        pthread_mutex_lock(&mutex);
        factorial *= i;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    int n = 5; // Example number for factorial calculation
    pthread_t tid;
    pthread_create(&tid, NULL, calculateFactorial, &n);
    pthread_join(tid, NULL);
    printf("Factorial: %llu\n", factorial);
    return 0;
}

