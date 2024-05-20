#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>
sem_t sem_k, sem_s;
void* scrivereK(void *p);
void* scrivereS(void *p);
int main(){
    sem_init(&sem_k, 0, 1);
    sem_init(&sem_s, 0, 0);

    pthread_t tk, ts;

    pthread_create(&tk, NULL, scrivereK, NULL);
    pthread_create(&ts, NULL, scrivereS, NULL);

    pthread_join(tk, NULL);
    pthread_join(ts, NULL);
    printf("\n");

    sem_destroy(&sem_k);
    sem_destroy(&sem_s);
}
void* scrivereK(void *p){
    int i;
    for(i=0; i<5; i++){
        sem_wait(&sem_k);
        printf("(K=%d)\n", sem_k);
        printf("k");
        fflush(NULL);
        sem_post(&sem_s);
                printf("(S=%d)\n", sem_s);
        sleep(random()%2);
    }
    pthread_exit(NULL);
}

void* scrivereS(void *p){
    int i;
    for(i=0; i<5; i++){
        sem_wait(&sem_s);
                printf("(S=%d)\n", sem_s);
        printf("s");
        fflush(NULL);
        sem_post(&sem_k);
        printf("(K=%d)\n", sem_k);
        sleep(random()%2);
    }
    pthread_exit(NULL);
}