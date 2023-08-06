#include <stdio.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

int flag[2];
int turn = 0;
int sharedVariable = 0;

void *thread1(void *arg) {
    int i;
    for (i = 0; i < 1000000; i++) {
        flag[0] = TRUE;
        turn = 1;
        while (flag[1] == TRUE && turn == 1);
        sharedVariable++;
        flag[0] = FALSE;
    }
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int i;
    for (i = 0; i < 1000000; i++) {
        flag[1] = TRUE;
        turn = 0;
        while (flag[0] == TRUE && turn == 0);
        sharedVariable++;
        flag[1] = FALSE;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("The value of sharedVariable is %d\n", sharedVariable);

    return 0;
}