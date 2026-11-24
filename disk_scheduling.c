#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void fcfs(int req[], int n, int head) {
    int total = 0, current = head;

    printf("\nFCFS Disk Scheduling:\n");
    printf("Head Movement: %d", head);

    for (int i = 0; i < n; i++) {
        total += abs(current - req[i]);
        current = req[i];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void sstf(int req[], int n, int head) {
    int visited[MAX] = {0};
    int total = 0, current = head;

    printf("\nSSTF Disk Scheduling:\n");
    printf("Head Movement: %d", head);

    for (int i = 0; i < n; i++) {
        int minDist = 1000000;
        int index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(current - req[j]);

                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += minDist;
        current = req[index];

        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void scan(int req[], int n, int head, int diskSize) {
    int arr[MAX], total = 0, current = head;
    int count = 0;

    for (int i = 0; i < n; i++)
        arr[count++] = req[i];

    arr[count++] = head;
    arr[count++] = 0;
    arr[count++] = diskSize - 1;

    // Sort requests
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int pos = 0;

    for (int i = 0; i < count; i++) {
        if (arr[i] == head) {
            pos = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling (Moving towards higher cylinders):\n");
    printf("Head Movement: %d", head);

    for (int i = pos + 1; i < count; i++) {
        total += abs(current - arr[i]);
        current = arr[i];
        printf(" -> %d", current);
    }

    for (int i = pos - 1; i >= 0; i--) {
        total += abs(current - arr[i]);
        current = arr[i];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void cscan(int req[], int n, int head, int diskSize) {
    int arr[MAX], total = 0, current = head;
    int count = 0;

    for (int i = 0; i < n; i++)
        arr[count++] = req[i];

    arr[count++] = head;
    arr[count++] = 0;
    arr[count++] = diskSize - 1;

    // Sort requests
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int pos = 0;

    for (int i = 0; i < count; i++) {
        if (arr[i] == head) {
            pos = i;
            break;
        }
    }

    printf("\nC-SCAN Disk Scheduling (Moving towards higher cylinders):\n");
    printf("Head Movement: %d", head);

    for (int i = pos + 1; i < count; i++) {
        total += abs(current - arr[i]);
        current = arr[i];
        printf(" -> %d", current);
    }

    // Return to cylinder 0
    total += abs(current - 0);
    current = 0;
    printf(" -> %d", current);

    for (int i = 0; i < pos; i++) {
        total += abs(current - arr[i]);
        current = arr[i];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main() {
    int req[MAX], n, head, diskSize;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (number of cylinders): ");
    scanf("%d", &diskSize);

    fcfs(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, diskSize);
    cscan(req, n, head, diskSize);

    return 0;
}
