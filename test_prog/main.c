#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
// compile  gcc -o mutex0 mutex0.c -lpthread
// mutex0.c RACE condition See mutex1.c

pthread_mutex_t myMutex;

char answer[1024];
sem_t len1;
int cnt = 0;
void *thread(void *arg){
    int id = *(int *)arg;
   // while (1){
        
        printf("Thread %d Waiting for sem Release space\n",id);
        sem_wait(&len1);
        pthread_mutex_lock(&myMutex);
        printf("Thread %d Entered protected zone \n",id);
        cnt ++;
        printf("Protected zone count: %d\n",cnt);
        pthread_mutex_unlock(&myMutex);
        
        sleep(1);
        
        
        sleep(1);
        pthread_mutex_lock(&myMutex);
        printf("Thread %d Left protected zone \n",id);
        cnt --;
        pthread_mutex_unlock(&myMutex);
        sem_post(&len1);
        sleep(1);
  //  }
}

int main(void){
    if (pthread_mutex_init(&myMutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    
    int i = 0;
    pthread_t threads[10];
    
    if (sem_init(&len1, 0 ,1) != 0){
        fprintf(stderr,"Error! ");
        exit(1);
    }
    for (i = 0;i < 5;i++){
        pthread_create(&threads[i] , NULL,thread,(void*)&i);
    }
    sem_post(&len1);
    for (i = 0;i < 5;i++){
        pthread_join(&threads[i],NULL);
    }
}