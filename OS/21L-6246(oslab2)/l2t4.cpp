#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
int fibonacci(int number) {
    if (number<= 1) {
        return number;
    }
    return fibonacci(number - 1) + fibonacci(number- 2);
}
int main() {
int arr[15];
    int number;
    cout << "Enter a number: ";
    cin >> number;

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
        }
        
     else if (pid == 0) {
        if (number< 0) {
        cout << "Invalid input. Please enter a non-negative integer." << endl;
        return 1; // Exit with an error code
    }
    
    for (int i = 0; i < number; ++i) {
    arr[i]=fibonacci(i);
       
    }
    
     cout << "Parent: Received result from child." << endl;
        cout<<"febonacci series is: "<<endl;
         for (int i = 0; i < number; ++i) {
        cout<<arr[i]<<" ";
       
}
}

    
    
     else {
        // Parent process
        wait(NULL); // Wait for the child process to complete
      
    }
   
    

    return 0;
}


