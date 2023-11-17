#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Initial balance in the account
int balance = 1000;

void deposit(int amount) {
    balance += amount;
}

void withdraw(int amount) {
    if (balance >= amount) {
        balance -= amount;
    } else {
        printf("Insufficient balance!\n");
    }
}

int main() {
    // Create a variable to store the process ID.
    pid_t child_pid;

    // Create two child processes for two account holders.
    for (int i = 0; i < 2; i++) {
        child_pid = fork();

        if (child_pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Code executed by child processes (account holders)
            int amount;
            if (i == 0) {
                // First account holder deposits
                printf("Account Holder 1: Enter deposit amount: ");
                scanf("%d", &amount);
                deposit(amount);
                printf("Account Holder 1: Deposited %d. New Balance: %d\n", amount, balance);
            } else {
                // Second account holder withdraws
                printf("Account Holder 2: Enter withdrawal amount: ");
                scanf("%d", &amount);
                withdraw(amount);
                printf("Account Holder 2: Withdrawn %d. New Balance: %d\n", amount, balance);
            }
            exit(EXIT_SUCCESS); // Exit the child process
        }
    }

    // Code executed by the parent process.
    for (int i = 0; i < 2; i++) {
        wait(NULL); // Wait for both child processes to finish
    }

    printf("Final Balance: %d\n", balance);

    return 0;
}

