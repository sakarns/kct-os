#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateMetrics(struct Process processes[], int n) {
    int i, j;
    int currentTime = 0;
    int highestPriorityIndex;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[j].priority < processes[i].priority) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
    }
}

void printTable(struct Process processes[], int n) {
    int i;

    printf("PID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }
}

int main() {
    struct Process processes[] = {
        {1, 0, 10, 3},
        {2, 2, 5, 1},
        {3, 5, 2, 4},
        {4, 6, 6, 2}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    calculateMetrics(processes, n);
    printTable(processes, n);

    return 0;
}