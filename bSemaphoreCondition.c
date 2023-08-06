#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 1000000

int sharedVariable = 0;
sem_t semaphore;

void *thread1(void *arg) {
    int i;
    for (i = 0; i < MAX; i++) {
        sem_wait(&semaphore);
        sharedVariable++;
        sem_post(&semaphore);
    }
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int i;
    for (i = 0; i < MAX; i++) {
        sem_wait(&semaphore);
        sharedVariable++;
        sem_post(&semaphore);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    sem_init(&semaphore, 0, 1);

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("The value of sharedVariable is %d\n", sharedVariable);

    sem_destroy(&semaphore);

    return 0;
}