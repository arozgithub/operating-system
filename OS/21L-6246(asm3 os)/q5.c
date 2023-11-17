#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t semaphore_a;
sem_t semaphore_b;
sem_t semaphore_c;

int x=1;
int y=0;
int z=0;
int sharedaccount=1000;

void *threadFunction1(void *arg) {


int count=0;
sem_wait(&semaphore_a);
while(count!=5){	
sharedaccount=sharedaccount-200;
printf("a shared account balance:%d$\n",sharedaccount);
count=count+1;
 }
  sem_post(&semaphore_c);
  
  pthread_exit(NULL);

}

void *threadFunction2(void *arg) {

int count=0;
sem_wait(&semaphore_b);
while(count!=5){	
sharedaccount=sharedaccount-200;
printf("b shared account balance:%d$\n",sharedaccount);
count=count+1;
 }
  
  pthread_exit(NULL);
}
void *threadFunction3(void *arg) {


int count=0;
sem_wait(&semaphore_c);
while(count!=5){	
sharedaccount=sharedaccount-200;
printf("c shared account balance:%d$\n",sharedaccount);
count=count+1;
 }
  sem_post(&semaphore_b);
  
  pthread_exit(NULL);
}
int main() {
    

    pthread_t A;
    pthread_t B;
    pthread_t C;
    // initializing semaphores with values
    // a with 1 and b and c with 0
    // second parameter is whether semaphores are shared or not 0 means no  
    sem_init(&semaphore_a, 0, x);
    sem_init(&semaphore_b, 0, y);
    sem_init(&semaphore_c, 0, z);
    
  pthread_create(&A, NULL, threadFunction1, NULL);
  pthread_create(&B, NULL, threadFunction2, NULL);
  pthread_create(&C, NULL, threadFunction3, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);
   
    return 0;
}

