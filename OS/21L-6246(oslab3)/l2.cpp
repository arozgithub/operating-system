#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main() {
    // Fork 1 child processes
    
        pid_t child_pid = fork();

        if (child_pid == -1) {
            cerr << "Fork failed." << endl;
            return 1;
        } else if (child_pid == 0) {
            // Child process
            cout << "Child process " << getpid() << " is running." << endl;
            ///bin/ls is the path to the executable file of the 'ls' command. This is the program that we want to run in the child process.
           execl("/bin/ls", "ls", "-l", NULL); // Execute 'ls -l' in the child process
        return 0; // This line should not be reached if execl() succeeds
   
    
}
    // Parent process
   
    cout << "Parent process " << getpid() << " is waiting for child processes." << endl;
//----wait ----waits for a child process to terminate, and returns that child process's pid. On error (eg when there are no child processes), -1 is returned. So, basically, the code keeps waiting for child processes to finish, until the waiting errors out, and then you know they are all finished.
    // Wait for all child processes to complete
    int status;
  
    //here we use waitpid because we have only one child and specify more about child
        waitpid(child_pid, &status, 0); // Wait for the child process to terminate
        //An exit status of 0 typically indicates that the child process exited successfully without errors.
        
        cout << "Parent process: Child process " << child_pid << " has completed." << endl;
  
    cout << "All child processes have completed. Parent process is done." << endl;

    return 0;
}

