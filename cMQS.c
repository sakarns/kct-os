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

void calculateMetrics(struct Process processes[], int n, int queue1[], int n1, int queue2[], int n2) {
    int i, j;
    int currentTime = 0;
    int highestPriorityIndex;

    for (i = 0; i < n; i++) {
        if (processes[i].priority == 1) {
            queue1[n1++] = i;
        } else {
            queue2[n2++] = i;
        }
    }

    for (i = 0; i < n1; i++) {
        if (currentTime < processes[queue1[i]].arrivalTime) {
            currentTime = processes[queue1[i]].arrivalTime;
        }

        processes[queue1[i]].completionTime = currentTime + processes[queue1[i]].burstTime;
        processes[queue1[i]].turnaroundTime = processes[queue1[i]].completionTime - processes[queue1[i]].arrivalTime;
        processes[queue1[i]].waitingTime = processes[queue1[i]].turnaroundTime - processes[queue1[i]].burstTime;

        currentTime = processes[queue1[i]].completionTime;
    }

    for (i = 0; i < n2; i++) {
        if (currentTime < processes[queue2[i]].arrivalTime) {
            currentTime = processes[queue2[i]].arrivalTime;
        }

        processes[queue2[i]].completionTime = currentTime + processes[queue2[i]].burstTime;
        processes[queue2[i]].turnaroundTime = processes[queue2[i]].completionTime - processes[queue2[i]].arrivalTime;
        processes[queue2[i]].waitingTime = processes[queue2[i]].turnaroundTime - processes[queue2[i]].burstTime;

        currentTime = processes[queue2[i]].completionTime;
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
        {1, 0, 10, 1},
        {2, 2, 5, 2},
        {3, 5, 2, 2},
        {4, 6, 6, 1}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    int queue1[n], queue2[n];
    int n1 = 0, n2 = 0;

    calculateMetrics(processes, n, queue1, n1, queue2, n2);
    printTable(processes, n);

    return 0;
}