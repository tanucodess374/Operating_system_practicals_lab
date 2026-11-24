#include <stdio.h>
#define MAX 20

typedef struct {
    int pid, at, bt, pr;
    int ct, tat, wt, rem;
} Process;

void printResult(Process p[], int n) {
    float totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
                p[i].pid, p[i].at, p[i].bt,
                p[i].ct, p[i].tat, p[i].wt);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("Average Waiting Time    = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

void fcfs(Process p[], int n) {
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printResult(p, n);
}

void sjf(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1, minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = 1;
        completed++;
    }

    printResult(p, n);
}

void priorityScheduling(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].pr < best) {
                best = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = 1;
        completed++;
    }

    printResult(p, n);
}

void roundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++)
        p[i].rem = p[i].bt;

    int queue[100], front = 0, rear = 0;
    int inQueue[MAX] = {0};

    /* Start with processes arriving at time 0 */
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;

            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && p[i].rem > 0 && p[i].at <= time) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }

            continue;
        }

        int idx = queue[front++];

        int slice = (p[idx].rem < quantum)
                    ? p[idx].rem : quantum;

        time += slice;
        p[idx].rem -= slice;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].rem > 0 &&
                p[i].at <= time && i != idx) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (p[idx].rem > 0) {
            queue[rear++] = idx;
        } else {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
            inQueue[idx] = 0;
        }
    }

    printResult(p, n);
}

int main() {
    int n, choice, quantum;
    Process p[MAX], orig[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Process %d - Arrival Time, Burst Time, Priority: ",
               i + 1);

        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }

    for (int i = 0; i < n; i++)
        orig[i] = p[i];

    printf("\nMenu:\n1. FCFS\n2. SJF (Non-preemptive)\n");
    printf("3. Priority (Non-preemptive)\n4. Round Robin\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(p, n);
            break;

        case 2:
            sjf(p, n);
            break;

        case 3:
            priorityScheduling(p, n);
            break;

        case 4:
            printf("Enter time quantum: ");
            scanf("%d", &quantum);
            roundRobin(p, n, quantum);
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}
