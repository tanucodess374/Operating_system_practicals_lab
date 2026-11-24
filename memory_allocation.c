#include <stdio.h>

#define MAX 20

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    int temp[MAX];

    for (int i = 0; i < m; i++)
        temp[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp[j] >= processSize[i]) {
                allocation[i] = j;
                temp[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int temp[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < m; i++)
        temp[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int best = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= processSize[i]) {
                if (best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }

        if (best != -1) {
            allocation[i] = best;
            temp[best] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int temp[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < m; i++)
        temp[i] = blockSize[i];

    for (int i = 0; i < n; i++) {
        int worst = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= processSize[i]) {
                if (worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            allocation[i] = worst;
            temp[worst] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX], processSize[MAX];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);

    return 0;
}
