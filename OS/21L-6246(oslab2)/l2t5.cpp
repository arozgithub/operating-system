#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char* argv[]) {
    pid_t pid = fork();
 int sum=0;
    int avg;
    int numArgs = argc - 1;
    int* numbers = new int[numArgs];
    if (pid < 0) {
        cerr << "Fork failed." << endl;
        return 1;
        }
        
     else if (pid == 0) {
     
        for (int i = 0; i < numArgs; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }
   for (int i = 0; i < numArgs; i++) {
       sum=numbers[i]+sum;
       
    }
    cout<<"sum is"<<sum<<endl;
    pid_t pid2=fork();
    if(pid2 == 0) {
    avg=sum/numArgs;
    cout<<"avg is"<<avg<<endl;
    int max=0;
     pid_t pid3=fork();
     if (pid3 == 0){
     for(int i=0;i<numArgs;i++){
     if(numbers[i]>=max){
     max=numbers[i];
     
     }
     }
    cout<<"max is:"<<max;
    }
     else if(pid3>0){
        // Parent process
        wait(NULL); // Wait for the child process to complete
      
    }
    
    }
    else if(pid2>0){
        // Parent process
        wait(NULL); // Wait for the child process to complete
      
    }

}

    
    
     else {
        // Parent process
        wait(NULL); // Wait for the child process to complete
      
    }
   
    

    return 0;
}


