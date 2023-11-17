#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t semaphore;
int fact[11];
int f=1;

void *factorial(void *arg) {
  int num=*((int *) arg);
  sem_wait(&semaphore);

for(int i=1;i<=num;i++){
  f=f*i;
}
fact[num]=f;
f=1;
sem_post(&semaphore);

pthread_exit(NULL);
}
int main() {
int numbers[10]={1,2,3,4,5,6,7,8,9,10};
    
    pthread_t threads[10];
   
    sem_init(&semaphore, 0, 1);
    
    
    for(int i=0;i<10;i++){
    pthread_create(&threads[i], NULL, factorial, &numbers[i]);
 }
 //printing in synchronized manner in ascending order
    for(int i=1;i<=10;i++){
    printf("factorial of thread[%d] is %d \n",i,fact[i]);
 }
    for(int i=0;i<10;i++){
    pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&semaphore);
    return 0;
}

