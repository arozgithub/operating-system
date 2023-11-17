#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

#define SHM_KEY 12345
#define ARRAY_SIZE 20

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("No file given");
        exit(1);
    }

    const char* inputFileName = argv[1];
    int inputFile = open(inputFileName, O_RDONLY);

    if (inputFile == -1) {
        perror("Error: Unable to open input file");
        exit(1);
    }

    // Get the shared memory segment
    int shm_id = shmget(SHM_KEY, ARRAY_SIZE, 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    char* shared_array = (char*)shmat(shm_id, NULL, 0);

    // Open semaphore created by producer
    sem_t* semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Consumer (reader)
    printf("Consumer process is running.\n");

    sem_wait(semaphore); // Decrement semaphore, enter critical section

    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%c ", shared_array[i]);
    }
    printf("\n");

    sem_post(semaphore); // Increment semaphore, exit critical section

    // Close and unlink semaphore
    sem_close(semaphore);
    sem_unlink("/my_semaphore");

    // Detach shared memory segment
    shmdt(shared_array);

    return 0;
}

