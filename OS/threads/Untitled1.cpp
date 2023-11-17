#include <stdio.h>
#include <pthread.h>

#define ROWS 3
#define COLS 4

int matrix[ROWS][COLS] = {0};

void *childThreadFunction(void *arg) {
    // Set a value in the 2D array
    matrix[1][2] = 42;
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    // Create the child thread
    pthread_create(&tid, NULL, childThreadFunction, NULL);

    // Wait for the child thread to complete
    pthread_join(tid, NULL);

    // Print the entire 2D array
    printf("2D Array from the child thread:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

