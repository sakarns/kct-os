#include <stdio.h>

#define N 10
#define M 4

int referenceString[N] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
int frames[M] = {-1, -1, -1, -1};

int pageFaults = 0;
int currentIndex = 0;

bool isInFrames(int page) {
    int i;
    for (i = 0; i < M; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

void replacePage() {
    frames[currentIndex] = referenceString[currentIndex];
    currentIndex = (currentIndex + 1) % M;
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

void simulateFIFO() {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d: ", referenceString[i]);
        if (isInFrames(referenceString[i])) {
            printf("Hit ");
        } else {
            printf("Miss ");
            pageFaults++;
            replacePage();
        }
        printFrames();
    }
}

int main() {
    simulateFIFO();
    printf("Total page faults: %d\n", pageFaults);
    return 0;
}