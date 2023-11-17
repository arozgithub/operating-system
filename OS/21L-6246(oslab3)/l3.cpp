#include <iostream>
#include <cstdlib>

int main() {
    // Use system() to invoke external commands
    // The return value of system() indicates the success or failure of the command
//the system() function takes the provided command string and passes it to the default system shell (typically /bin/sh or /bin/bash on Unix-like systems). The shell is responsible for interpreting and executing the command.

//The shell runs the specified command in a subshell or a new process. It waits for the command to complete.

//When the command finishes executing, the shell returns the exit status of the command to the calling program.

//The calling program can check the return value of system() to determine whether the command executed successfully or not.
    int result;

    // Copy a file or directory using 'cp'
    result = system("cp -r log.txt w.txt");
    if (result == 0) {
        std::cout << "cp command executed successfully." << std::endl;
    } else {
        std::cerr << "cp command failed." << std::endl;
    }

    // Create a directory using 'mkdir'
    result = system("mkdir new_directory");
    if (result == 0) {
        std::cout << "mkdir command executed successfully." << std::endl;
    } else {
        std::cerr << "mkdir command failed." << std::endl;
    }

    // Remove a directory using 'rmdir'
    result = system("rmdir new_directory");
    if (result == 0) {
        std::cout << "rmdir command executed successfully." << std::endl;
    } else {
        std::cerr << "rmdir command failed." << std::endl;
    }

    // List directory contents using 'ls'
    result = system("ls -l");
    if (result == 0) {
        std::cout << "ls command executed successfully." << std::endl;
    } else {
        std::cerr << "ls command failed." << std::endl;
    }

    return 0;
}

