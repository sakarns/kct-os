#include <stdio.h>

#define N 10
#define M 4

int referenceString[N] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
int frames[M] = {-1, -1, -1, -1};
int remainingTime[M] = {0, 0, 0, 0};

int pageFaults = 0;

bool isInFrames(int page) {
    int i;
    for (i = 0; i < M; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

int getShortest() {
    int i, min = remainingTime[0], minIndex = 0;
    for (i = 1; i < M; i++) {
        if (remainingTime[i] < min) {
            min = remainingTime[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void replacePage(int page) {
    int shortestIndex = getShortest();
    frames[shortestIndex] = page;
    remainingTime[shortestIndex] = M;
}

void updateRemainingTime() {
    int i;
    for (i = 0; i < M; i++) {
        if (frames[i] != -1) {
            remainingTime[i]--;
            if (remainingTime[i] == 0) {
                frames[i] = -1;
            }
        }
    }
}

void printFrames() {
    int i;
    for (i = 0; i < M; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

void simulateSRTN() {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d: ", referenceString[i]);
        if (isInFrames(referenceString[i])) {
printf("Hit ");
int j;
for (j = 0; j < M; j++) {
if (frames[j] == referenceString[i]) {
remainingTime[j] = M;
}
}
} else {
printf("Miss ");
pageFaults++;
replacePage(referenceString[i]);
}
updateRemainingTime();
printFrames();
}
}

int main() {
simulateSRTN();
printf("Total page faults: %d\n", pageFaults);
return 0;
}