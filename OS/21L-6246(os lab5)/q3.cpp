#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main() {
    int childToParent[2]; // Pipe for child to parent communication
    int parentToChild[2]; // Pipe for parent to child communication

    // Create pipes
    pipe(parentToChild);
    pipe(childToParent);

    pid_t cpid = fork();

    if (cpid == -1) {
        cerr << "Fork failed." << endl;
        return 1;
    }

    if (cpid == 0) {
        // Child process
        close(parentToChild[1]); // Close write end of parentToChild pipe
        close(childToParent[0]); // Close read end of childToParent pipe

        char buffer[1024]; // Buffer for reading from the pipe
        ssize_t bytes_read = read(parentToChild[0], buffer, sizeof(buffer));

        if (bytes_read < 0) {
            cerr << "Error reading from parent." << endl;
            return 1;
        }

        // Reverse the case of each character in the message
        for (int i = 0; i < bytes_read; ++i) {
            if (isupper(buffer[i])) {
                buffer[i] = tolower(buffer[i]);
            } else if (islower(buffer[i])) {
                buffer[i] = toupper(buffer[i]);
            }
        }

        // Send modified message back to the parent
        write(childToParent[1], buffer, bytes_read);

        // Close pipes
        close(parentToChild[0]);
        close(childToParent[1]);
    } else {
        // Parent process
        close(parentToChild[0]); // Close read end of parentToChild pipe
        close(childToParent[1]); // Close write end of childToParent pipe

        string message;
        cout << "Enter message: ";
        getline(cin, message);

        // Send the message to the child
        write(parentToChild[1], message.c_str(), message.size() + 1);

        // Wait for the child to finish
        wait(NULL);

        // Receive the modified message from the child
        char buffer[1024];
        ssize_t bytes_read = read(childToParent[0], buffer, sizeof(buffer));

        if (bytes_read < 0) {
            cerr << "Error reading from child." << endl;
            return 1;
        }

        // Display results
        buffer[bytes_read] = '\0'; // Null-terminate the received data
        cout << "Modified message: " << buffer << endl;

        // Close pipes
        close(parentToChild[1]);
        close(childToParent[0]);
    }

    return 0;
}

