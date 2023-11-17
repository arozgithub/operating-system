#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>

#define MAX_COOKS 2
#define MAX_CUSTOMERS 5

int main() {
    // Create arrays to represent cooks and customers
    int cooks[MAX_COOKS];
    int customers[MAX_CUSTOMERS];

    // Initialize cooks and customers as available (0 means available, 1 means busy)
    for (int i = 0; i < MAX_COOKS; i++) {
        cooks[i] = 0;
    }
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customers[i] = 0;
    }

    srand(time(NULL)); // Initialize random seed

    // Start a loop to handle customer requests
    while (1) {
        // Fork a new child process to handle a customer request
        pid_t child = fork();
        
        if (child == 0) { // Child process (customer)
            int customer_id = getpid(); // Get the customer's process ID
            printf("Customer %d is in the restaurant.\n", customer_id);
            
            // Find an available cook
            int cook_index = -1;
            while (cook_index == -1) {
                for (int i = 0; i < MAX_COOKS; i++) {
                    if (cooks[i] == 0) {
                        cook_index = i;
                        cooks[i] = 1; // Mark the cook as busy
                        break;
                    }
                }
                if (cook_index == -1) {
                    printf("Customer %d is waiting for a cook.\n", customer_id);
                    // If no cook is available, the customer waits
                    usleep(100000); // Sleep for a short time to reduce CPU usage
                }
            }

            printf("Customer %d is being served by Cook %d.\n", customer_id, cook_index);

            // Simulate the customer being served (sleep for a random time)
            sleep(rand() % 3 + 1);

            printf("Customer %d has been served and is leaving the restaurant.\n", customer_id);
            cooks[cook_index] = 0; // Mark the cook as available
            exit(0);
        } else if (child > 0) { // Parent process (restaurant manager)
            // Wait for the child process to finish handling the customer request
            wait(NULL);
        } else { // Fork error
            printf("Failed to fork.\n");
            exit(1);
        }
    }

    return 0;
}

