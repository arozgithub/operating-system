#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
   
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror( "Fork failed." );
            return 1;
        } 
        else if (child_pid == 0) {
            // Child process
          printf("child process %d is running.\n", getpid());
        
        
            // Simulate some work in the child process
            sleep(2);
            printf("child process %d is done.\n", getpid());
            return 0;
        }
    

    // Parent process
    // to deleay the parent 
    sleep(4);
    //cout << "Parent process " << getpid() << " is waiting for child processes." << endl;

    int status;
     child_pid;
    if (child_pid != -1) {
    if (WIFEXITED(status)) {
        printf("Parent process: Child process %d has completed.\n", child_pid);
    } else {
        printf("Parent process: Child process %d did not exit normally.\n", child_pid);
    }
} else {
    perror("Wait failed");
}


    return 0;
}

