#include <pthread.h>
#include <stdio.h>
//7.Thread-Local Storage:

pthread_key_t key;

void destructor(void *value) {
    free(value);
}

void *threadFunction(void *arg) {
    int *localValue = (int *)malloc(sizeof(int));
    *localValue = *((int *)arg);
    pthread_setspecific(key, localValue);
    printf("Thread-Specific Value: %d\n", *((int *)pthread_getspecific(key)));
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_key_create(&key, destructor);
    int threadValue = 42;
    pthread_create(&tid, NULL, threadFunction, (void *)&threadValue);
    pthread_join(tid, NULL);
    pthread_key_delete(key);
    return 0;
}

