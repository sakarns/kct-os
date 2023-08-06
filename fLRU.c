#include <stdio.h>

#define N 10
#define M 4

int referenceString[N] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
int frames[M] = {-1, -1, -1, -1};
int lastUsed[M] = {-1, -1, -1, -1};

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

int getLRUPage() {
    int i, min = lastUsed[0], minIndex = 0;
    for (i = 1; i < M; i++) {
        if (lastUsed[i] < min) {
            min = lastUsed[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void replacePage(int page) {
    int lruIndex = getLRUPage();
    frames[lruIndex] = page;
    lastUsed[lruIndex] = 0;
}

void updateLastUsed() {
    int i;
    for (i = 0; i < M; i++) {
        if (frames[i] != -1) {
            lastUsed[i]++;
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

void simulateLRU() {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d: ", referenceString[i]);
        if (isInFrames(referenceString[i])) {
            printf("Hit ");
            int j;
            for (j = 0; j < M; j++) {
                if (frames[j] == referenceString[i]) {
                    lastUsed[j] = 0;
                }
            }
        } else {
            printf("Miss ");
            pageFaults++;
            replacePage(referenceString[i]);
        }
        updateLastUsed();
        printFrames();
    }
}

int main() {
    simulateLRU();
    printf("Total page faults: %d\n", pageFaults);
    return 0;
}