#include <stdio.h>

#define N 5

int allocation[N][N] = {
    {0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0}
};

int request[N][N] = {
    {0, 0, 0, 0, 0},
    {1, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1}
};

int available[N] = {1, 0, 0, 1, 0};

int main() {
    int i, j, k;
    int finish[N] = {0};
    int work[N];

    for (i = 0; i < N; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < N; i++) {
        if (!finish[i]) {
            for (j = 0; j < N; j++) {
                if (request[i][j] > work[j]) {
                    break;
                }
            }

            if (j == N) {
                for (k = 0; k < N; k++) {
                    work[k] += allocation[i][k];
                }

                finish[i] = 1;
                i = -1; // reset the outer loop
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (!finish[i]) {
            printf("Deadlock detected!\n");
            return 1;
        }
    }

    printf("No deadlock detected.\n");
    return 0;
}