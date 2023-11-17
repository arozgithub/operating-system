#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *threadFunction(void *arg) {
    int n = *((int *)arg);//type cast
    int t1 = 0, t2 = 1, nextTerm;
    
    printf("Fibonacci Series: %d, %d, ", t1, t2);
    nextTerm = t1 + t2;

    while (nextTerm <= n) {
        printf("%d, ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    printf("\n");

    pthread_exit(NULL);
}

//int main(int argc, char* argv[]) {
//    if (argc < 2) {
//        cout << "Usage: " << argv[0] << " <integer1> <integer2> <integer3> ..." << endl;
//        return 1;
//    }
//
//    int numArgs = argc - 1;
//    int* numbers = new int[numArgs];
//
//    for (int i = 0; i < numArgs; i++) {
//        numbers[i] = atoi(argv[i + 1]);
    }
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> <num3> ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int NUM_THREADS = argc - 1;
    int *numbers = (int *)malloc(NUM_THREADS * sizeof(int));

    for (int i = 0; i < NUM_THREADS; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, threadFunction, &numbers[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(numbers);
    return 0;
}

