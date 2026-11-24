#include <stdio.h>

#define MAX 100

void fifo(int pages[], int n, int frames) {
    int frame[MAX], faults = 0, next = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[next] = pages[i];
            next = (next + 1) % frames;
            faults++;
        }

        printf("Page %d: ", pages[i]);

        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        if (!found)
            printf(" Page Fault");
        else
            printf(" Hit");

        printf("\n");
    }

    printf("Total Page Faults (FIFO) = %d\n", faults);
}

void lru(int pages[], int n, int frames) {
    int frame[MAX], lastUsed[MAX];
    int faults = 0, time = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = -1;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            lastUsed[found] = time++;
        } else {
            int replace = -1;

            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replace = j;
                    break;
                }
            }

            if (replace == -1) {
                replace = 0;

                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[replace])
                        replace = j;
                }
            }

            frame[replace] = pages[i];
            lastUsed[replace] = time++;
            faults++;
        }

        printf("Page %d: ", pages[i]);

        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        if (found == -1)
            printf(" Page Fault");
        else
            printf(" Hit");

        printf("\n");
    }

    printf("Total Page Faults (LRU) = %d\n", faults);
}

void optimal(int pages[], int n, int frames) {
    int frame[MAX], faults = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replace = -1;

            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replace = j;
                    break;
                }
            }

            if (replace == -1) {
                int farthest = -1;

                for (int j = 0; j < frames; j++) {
                    int k;

                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == pages[k])
                            break;
                    }

                    if (k == n) {
                        replace = j;
                        break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }
            }

            frame[replace] = pages[i];
            faults++;
        }

        printf("Page %d: ", pages[i]);

        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        if (!found)
            printf(" Page Fault");
        else
            printf(" Hit");

        printf("\n");
    }

    printf("Total Page Faults (Optimal) = %d\n", faults);
}

int main() {
    int pages[MAX], n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
