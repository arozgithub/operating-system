#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cmath>

using namespace std;

int main() {
    int childToParent[2]; // Pipe for child to parent communication
    int parentToChild[2]; // Pipe for parent to child communication
  
    int number;

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

        // Read the integer from the parent
        read(parentToChild[0], &number, sizeof(number));

        // Calculate square root
        double squareRoot = sqrt(static_cast<double>(number));

        // Send square root back to the parent
        write(childToParent[1], &squareRoot, sizeof(squareRoot));

        // Close pipes
        close(parentToChild[0]);
        close(childToParent[1]);
    } else {
        // Parent process
        close(parentToChild[0]); // Close read end of parentToChild pipe
        close(childToParent[1]); // Close write end of childToParent pipe

        // Input integer from user
        cout << "Enter integer: ";
        cin >> number;

        // Send the integer to the child
        write(parentToChild[1], &number, sizeof(number));

        // Wait for the child to finish
        wait(NULL);

        // Receive the square root from the child
        double squareRoot;
        read(childToParent[0], &squareRoot, sizeof(squareRoot));

        // Display results
      
        cout << "Square root: " << squareRoot << endl;

        // Close pipes
        close(parentToChild[1]);
        close(childToParent[0]);
    }

    return 0;
}

