#include <stdio.h>
#include <stdbool.h>

#define N 5
#define M 3

int allocation[N][M] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int max[N][M] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int available[M] = {3, 3, 2};

bool finish[N] = {false};

int need[N][M];

void calculateNeed() {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int process) {
    int i, j;
    int work[M];
    for (i = 0; i < M; i++) {
        work[i] = available[i];
    }

    bool finishCopy[N];
    for (i = 0; i < N; i++) {
        finishCopy[i] = finish[i];
    }

    finishCopy[process] = true;

    for (i = 0; i < N; i++) {
        if (!finishCopy[i]) {
            for (j = 0; j < M; j++) {
                if (need[i][j] > work[j]) {
                    break;
                }
            }

            if (j == M) {
                for (j = 0; j < M; j++) {
                    work[j] += allocation[i][j];
                }
                finishCopy[i] = true;
                i = -1; // reset the outer loop
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (!finishCopy[i]) {
            return false;
        }
    }

    return true;
}

bool detectDeadlock() {
    int i, j;
    bool deadlockFound = true;

    calculateNeed();

    while (deadlockFound) {
        deadlockFound = false;

        for (i = 0; i < N; i++) {
            if (!finish[i] && isSafe(i)) {
                for (j = 0; j < M; j++) {
                    available[j] += allocation[i][j];
                }
                finish[i] = true;
                deadlockFound = true;
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (!finish[i]) {
            return true;
        }
    }

    return false;
}

int main() {
    if (detectDeadlock()) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }
    return 0;
}