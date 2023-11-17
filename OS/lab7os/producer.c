#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
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

    // Create a shared memory segment
    int shm_id = shmget(SHM_KEY, ARRAY_SIZE, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    char* shared_array = (char*)shmat(shm_id, NULL, 0);

    // Create and initialize semaphore
    sem_t semaphore;
    sem_init(&semaphore, 1, 1); // 1 indicates the semaphore is shared among processes

    // Producer (writer)
    printf("Producer process is running.\n");

    sem_wait(&semaphore); // Decrement semaphore, enter critical section

    int bytesRead = read(inputFile, shared_array, ARRAY_SIZE);
    if (bytesRead == -1) {
        perror("Error reading from file");
        exit(1);
    }

    sem_post(&semaphore); // Increment semaphore, exit critical section

    // Detach shared memory segment
    shmdt(shared_array);

    // Remove shared memory segment
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

