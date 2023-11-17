#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct Parameters {
    int parameter1;
    int parameter2;
};
int isPrime(int num) {
    if (num <= 1) {
        return 0; // 0 and 1 are not prime
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // Not prime if it has a divisor other than 1 and itself
        }
    }
    return 1;
}
int main() {
      struct Parameters parameters_rec;
      int value1;
      int value2;
      int pipe_parenttochild[2];
      int par_rec;
       // Create a pipe
    if (pipe(pipe_parenttochild) == -1) {
        perror("pipe");
        return 1;
    }
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror( "Fork failed." );
            return 1;
        } 
        else if (child_pid == 0) {
            // Child process
          printf("child process %d is running.\n", getpid());
          close(pipe_parenttochild[1]);
          // Read input from the pipe (read end)
          ssize_t bytes_read=read(pipe_parenttochild[0], &parameters_rec, sizeof(parameters_rec));
          if (bytes_read == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        // Access individual members
int param1 = parameters_rec.parameter1;
int param2 = parameters_rec.parameter2;
for (int num = param1; num <= param2; num++) {
            if (isPrime(num)) {
                printf("%d\n", num);
                
            }
        }

 
            // Simulate some work in the child process
            sleep(2);
            printf("child process %d is done.\n", getpid());
            return 0;
        }
    

    // Parent process
              
        close(pipe_parenttochild[0]);
        struct Parameters par_send;
        printf("Parent process (PID: %d) is running.\n", getpid());
        
        printf("Enter a value 1: ");
        scanf("%d", &value1);
        printf("Parent process received: %d\n", value1)  ;
        printf("Enter a value 1: ");
        
        scanf("%d", &value2);
        printf("Parent process received: %d\n", value2)  ;
        par_send.parameter1=value1;
        par_send.parameter2=value2;
        ssize_t bytes_written=write(pipe_parenttochild[1], &par_send, sizeof(par_send));
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipe_parenttochild[1]); // close the write end

    return 0;
}

