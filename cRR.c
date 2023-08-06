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

void calculateMetrics(struct Process processes[], int n, int quantum) {
    int i, j;
    int currentTime = 0;

    for (i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (1) {
        int done = 1;

        for (i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                done = 0;

                if (processes[i].remainingTime > quantum) {
                    processes[i].remainingTime -= quantum;
                    currentTime += quantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                }
            }
        }

        if (done == 1) {
            break;
        }
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
    int quantum = 2;

    calculateMetrics(processes, n, quantum);
    printTable(processes, n);

    return 0;
}