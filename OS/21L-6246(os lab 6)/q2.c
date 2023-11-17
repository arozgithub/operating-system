#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

double averageValue;
int maxValue;
int minValue;

struct ThreadData {
    int* numbers;
    int size;
};

void* Average(void* args) {// 
    struct ThreadData* data = (struct ThreadData*)args;// we did this becuase function gets an address of struct object so it must do this: (struct ThreadData*)args
    int total = 0;
    for (int i = 0; i < data->size; ++i) {
        total =total + data->numbers[i];
    }
    averageValue = (double)total / data->size;
    pthread_exit(NULL);
}

void* Max(void* args) {
    struct ThreadData* data = (struct ThreadData*)args;
    maxValue = data->numbers[0];
    for (int i = 1; i < data->size; ++i) {
        if (data->numbers[i] > maxValue) {
            maxValue = data->numbers[i];
        }
    }
    pthread_exit(NULL);
}

void* Min(void* args) {
    struct ThreadData* data = (struct ThreadData*)args;
    minValue = data->numbers[0];
    for (int i = 1; i < data->size; ++i) {
        if (data->numbers[i] < minValue) {
            minValue = data->numbers[i];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a series of numbers.\n");
        return 1;
    }

    int size = argc - 1;
    int* numbers = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        numbers[i] = atoi(argv[i + 1]);
    }

    struct ThreadData data = {numbers, size}; // assigning values to struct parameters

    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    pthread_create(&t1, NULL, Average, &data);
    pthread_create(&t2, NULL, Max, &data);
    pthread_create(&t3, NULL, Min, &data);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("The average value is %lf\n", averageValue);
    printf("The maximum value is %d\n", maxValue);
    printf("The minimum value is %d\n", minValue);

    free(numbers);

    return 0;
}

