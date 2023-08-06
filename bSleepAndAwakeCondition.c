#include <stdio.h>
#include <pthread.h>

#define MAX 1000000

int sharedVariable = 0;
int flag[2] = {0, 0};
int turn = 0;

void *thread1(void *arg) {
    int i;
    for (i = 0; i < MAX; i++) {
        flag[0] = 1;
        turn = 1;
        while (flag[1] == 1 && turn == 1) {
            flag[0] = 0;
            sleep(1);
            flag[0] = 1;
        }
        sharedVariable++;
        flag[0] = 0;
    }
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int i;
    for (i = 0; i < MAX; i++) {
        flag[1] = 1;
        turn = 0;
        while (flag[0] == 1 && turn == 0) {
            flag[1] = 0;
            sleep(1);
            flag[1] = 1;
        }
        sharedVariable++;
        flag[1] = 0;
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