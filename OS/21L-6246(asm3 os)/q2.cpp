#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <iostream>
using namespace std;
sem_t a,b; 
int buffer=0;
int i = 1;
int sum=0;
bool t=true;
void* funp(void* num){
    while(t){
    if(i == 100){
         t=false;
    }
    
    sem_wait(&a);
    buffer=i;
    cout<<"producer generates: "<<buffer;
    cout<<endl;
    sem_post(&b);
    }
    pthread_exit(NULL);
}
    
void* func(void* num){
    while(t){
    sem_wait(&b);
    cout<<"consumer consumes: "<<buffer;
    cout<<endl;
    i++;
    
    sem_post(&a);
    }
    pthread_exit(NULL);
}
int main(){

pthread_t producer;
pthread_t consumer;

sem_init(&a, 0, 1);
sem_init(&b, 0, 0);

pthread_create(&producer,NULL,funp,NULL);
pthread_create(&consumer,NULL,func,NULL);

pthread_join(producer,NULL);
pthread_join(consumer,NULL);
}
