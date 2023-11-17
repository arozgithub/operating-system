#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstring>
#include <semaphore.h>
#include<sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstdlib>

using namespace std;

int main() {

char buffer1;
int sum1 = 0;
int count1=0;

char buffer2;
int sum2 = 0;
int count2=0;

int totalsum=0;
int totalcount=0;
int Average=0;
 
 

int inputfd = open("i.txt", O_RDONLY);
    if (inputfd == -1) {
        cout << "Error opening the file" << endl;
    }
    
   int inputfd1 = open("12.txt", O_RDONLY);
    if (inputfd1 == -1) {
        cout << "Error opening the file" << endl;
    }
    
    int sharedid = shmget((key_t)123456789, sizeof(int), IPC_CREAT | 0666);
    if (sharedid < 0) {
        cout << "Shared memory creation failed" << endl;
        return 1;
    }

    int* a = (int*)shmat(sharedid, NULL, 0);

for(int i=0;i<5;i++)
{
a[i]=0;
}


    sem_t sem;
    sem_init(&sem, 1, 1);

    pid_t pid = fork();

    if (pid == -1) {
        cout << "Fork failed." << endl;
        return 1;
    } else if (pid == 0) {
        sem_wait(&sem);
        while (read(inputfd,&buffer1,sizeof(buffer1)) > 0) {
        if (isdigit(buffer1)) {
            sum1 =sum1+buffer1-48;
            a[0]=sum1;
            count1++;
            
        }
    }    
        a[1]=count1;
        cout<<"first child"<<endl;
        sem_post(&sem);
        shmdt(a);
        exit(0); 
    } else {
        wait(NULL);

        pid_t pid1 = fork();

        if (pid1 == -1) {
            cout<< "Fork failed." << endl;
            return 1;
        } else if (pid1 == 0) {
            sem_wait(&sem);
         while (read(inputfd1,&buffer2,sizeof(buffer2)) > 0) {
        if (isdigit(buffer2)) {
            sum2 =sum2+buffer2-48;
            a[2]=sum2;
            count2++;
            
        }
    }    
        a[3]=count2;
            cout<<"Second child"<<endl;
            sem_post(&sem);
            shmdt(a);
            exit(0); 
        } else {
            wait(NULL);
            sem_wait(&sem);
            totalsum=a[0]+a[2];
            totalcount=a[1]+a[3];
            Average=totalsum/totalcount;
            cout<<"The total sum is:"<<totalsum<<endl;
            cout<<"The total count is:"<<totalcount<<endl;
            cout<<"The Average of all the integers is:"<<Average<<endl;
            sem_post(&sem);
            shmdt(a);
            shmctl(sharedid, IPC_RMID, NULL);
        }
    }

    sem_destroy(&sem);

    return 0;
}

