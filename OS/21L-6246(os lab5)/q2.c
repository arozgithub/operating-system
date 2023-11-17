#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>  // Include this for open()
#include <sys/stat.h> // Include this for open()
#include <string.h> // Include this for strlen()

#define SHM_KEY 12345
#define ARRAY_SIZE 1000 // Adjust this as needed

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("No file given");
        exit(1);
    }

    const char* inputFileName = argv[1];
    int inputFile = open(inputFileName, O_RDONLY); // Use O_RDONLY only

    if (inputFile == -1) {
        perror("Error: Unable to open input file");
        exit(1);
    }

    // Seek to the end of the file to get its size
    off_t fileSize = lseek(inputFile, 0, SEEK_END);

    // Create a shared memory segment
    int shm_id = shmget(SHM_KEY, fileSize, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    char* shared_array = (char*)shmat(shm_id, NULL, 0);
    if (shared_array == (void*)-1) { /* operation failed. */
        perror("shmat");
        exit(1);
    }

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process (reader)
        int bytesRead = read(inputFile, shared_array, fileSize);
        if (bytesRead == -1) {
            perror("Error reading from file");
            exit(1);
        }
        close(inputFile);
        // The child process should exit here.
    } else {
        // Parent process (writer)

        // Wait for the child to finish reading
        wait(NULL);

        printf("Parent process is running.\n");

        // Perform case conversion and remove integers
        for (int i = 0; i < fileSize; i++) {
            if (isalpha(shared_array[i])) {
                shared_array[i] = islower(shared_array[i]) ? toupper(shared_array[i]) : tolower(shared_array[i]);
            } else if (isdigit(shared_array[i])) {
                // Replace integers with spaces
                shared_array[i] = ' ';
            }
        }

        // Open the same file for writing
        int outputFile = open(inputFileName, O_WRONLY | O_TRUNC);
        if (outputFile == -1) {
            perror("Error: Unable to open output file");
            exit(1);
        }

        // Write the modified data back to the file
        ssize_t bytesWritten = write(outputFile, shared_array, fileSize);
        if (bytesWritten == -1) {
            perror("Error writing to file");
            exit(1);
        }

        close(outputFile);

        // Detach and remove the shared memory segment
        shmdt(shared_array);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    return 0;
}

