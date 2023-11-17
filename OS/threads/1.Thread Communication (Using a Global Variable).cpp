#include <stdio.h>
#include <pthread.h>
// 1.Thread Communication (Using a Global Variable):
int sharedVariable = 0;

void *childThreadFunction(void *arg) {
    sharedVariable = 10;
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, childThreadFunction, NULL);
    pthread_join(tid, NULL);
    printf("Value from child thread: %d\n", sharedVariable);
    return 0;
}

