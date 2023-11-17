#include <pthread.h>
#include <stdio.h>
#define SIZE 3
//6.Matrix Multiplication with Threads:

int matrixA[SIZE][SIZE] = { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} };

int matrixB[SIZE][SIZE] = { {9, 8, 7},
                            {6, 5, 4},
                            {3, 2, 1} };

int result[SIZE][SIZE];

typedef struct {
    int row;
    int col;
} MatrixElement;

void* multiplyThread(void* arg) {
    MatrixElement* element = (MatrixElement*)arg;
    int row = element->row;
    int col = element->col;
    int sum = 0;

    for (int i = 0; i < SIZE; i++) {
        sum += matrixA[row][i] * matrixB[i][col];
    }

    result[row][col] = sum;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[SIZE][SIZE];
    MatrixElement elements[SIZE][SIZE];

    // Create threads for each element of the resulting matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            elements[i][j].row = i;
            elements[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiplyThread, (void*)&elements[i][j]);
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the result
    printf("Result Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

