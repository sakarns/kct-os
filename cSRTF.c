#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateMetrics(struct Process processes[], int n) {
    int i, j;
    int currentTime = 0;
    int shortestJobIndex;

    for (i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    for (i = 0; i < n; i++) {
        shortestJobIndex = -1;

        for (j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0) {
                if (shortestJobIndex == -1 || processes[j].remainingTime < processes[shortestJobIndex].remainingTime) {
                    shortestJobIndex = j;
                }
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
            i--;
            continue;
        }

        processes[shortestJobIndex].remainingTime--;

        if (processes[shortestJobIndex].remainingTime == 0) {
            processes[shortestJobIndex].completionTime = currentTime + 1;
            processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].completionTime - processes[shortestJobIndex].arrivalTime;
            processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
        }

        currentTime++;
    }
}

void printTable(struct Process processes[], int n) {
    int i;

    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }
}

int main() {
    struct Process processes[] = {
        {1, 0, 10},
        {2, 2, 5},
        {3, 5, 2},
        {4, 6, 6}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    calculateMetrics(processes, n);
    printTable(processes, n);

    return 0;
}