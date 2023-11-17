#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main() {
    // Fork 4 child processes
    for (int i = 0; i < 4; i++) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            cerr << "Fork failed." << endl;
            return 1;
        } else if (child_pid == 0) {
            // Child process
            cout << "Child process " << getpid() << " is running." << endl;
            // Simulate some work in the child process
            sleep(2);
            cout << "Child process " << getpid() << " is done." << endl;
            return 0;
        }
    }

    // Parent process
    // to deleay the parent 
    sleep(4);
    cout << "Parent process " << getpid() << " is waiting for child processes." << endl;
//----wait ----waits for a child process to terminate, and returns that child process's pid. On error (eg when there are no child processes), -1 is returned. So, basically, the code keeps waiting for child processes to finish, until the waiting errors out, and then you know they are all finished.
    // Wait for all child processes to complete
    int status;
    pid_t child_pid;
    while ((child_pid = wait(&status)) != -1) {
        cout << "Parent process: Child process " << child_pid << " has completed." << endl;
    }

    cout << "All child processes have completed. Parent process is done." << endl;

    return 0;
}

