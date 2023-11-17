#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
        }
        
     else if (pid == 0) {
        // Child process
        if (number % 2 == 0) {
           cout << "Child: The number is even." << endl;
        } else {
            cout << "Child: The number is odd." << endl;
        }
    }
     else {
        // Parent process
        wait(NULL); // Wait for the child process to complete
        cout << "Parent: Received result from child." << endl;
        cout<<"number is "<<number<<endl;
    }

    return 0;
}

