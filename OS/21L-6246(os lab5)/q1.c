#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_KEY 12345
#define ARRAY_SIZE 5

int main() {
    int shm_id;
    int *shared_array;//pointer
    pid_t child_pid;

    // Create a shared memory segment
    shm_id2 = shmget(SHM_KEY, ARRAY_SIZE , 0666 | IPC_CREAT | IPC_EXCL);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment tp processe's space adress
    shared_array = shmat(shm_id2, NULL, 0);
   if (!shared_array) { /* operation failed. */
    perror("shmat: ");
    exit(1);
}
// Parent process (writer)
        printf("Parent process (writer) is running.\n");
        printf("Enter %d integers:\n", ARRAY_SIZE);
        for (int i = 0; i < ARRAY_SIZE; i++) {
            scanf("%d", &shared_array[i]);
        }
    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process (reader)
        printf("Child process (reader) is running.\n");
        printf("Squares of the integers:\n");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d squared is %d\n", shared_array[i], shared_array[i] * shared_array[i]);
        }
    } 
        

    // Detach and remove the shared memory segment
    shmdt(shared_array);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

