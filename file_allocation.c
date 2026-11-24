#include <stdio.h>

#define MAX 100

void contiguous() {
    int start, length;

    printf("\n--- Contiguous Allocation ---\n");

    printf("Enter starting block: ");
    scanf("%d", &start);

    printf("Enter file length (number of blocks): ");
    scanf("%d", &length);

    printf("File allocated blocks:\n");

    for (int i = 0; i < length; i++)
        printf("%d ", start + i);

    printf("\n");
}

void linked() {
    int n, blocks[MAX];

    printf("\n--- Linked Allocation ---\n");

    printf("Enter number of blocks in file: ");
    scanf("%d", &n);

    printf("Enter block numbers:\n");

    for (int i = 0; i < n; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    printf("\nFile block chain:\n");

    for (int i = 0; i < n; i++) {
        if (i < n - 1)
            printf("%d -> ", blocks[i]);
        else
            printf("%d -> NULL\n", blocks[i]);
    }
}

void indexed() {
    int indexBlock, n, blocks[MAX];

    printf("\n--- Indexed Allocation ---\n");

    printf("Enter index block number: ");
    scanf("%d", &indexBlock);

    printf("Enter number of data blocks: ");
    scanf("%d", &n);

    printf("Enter data block numbers:\n");

    for (int i = 0; i < n; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    printf("\nIndex Block: %d\n", indexBlock);
    printf("Index block stores addresses of:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", blocks[i]);

    printf("\n");
}

int main() {
    int choice;

    do {
        printf("\n===== FILE ALLOCATION METHODS =====\n");
        printf("1. Contiguous Allocation\n");
        printf("2. Linked Allocation\n");
        printf("3. Indexed Allocation\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                contiguous();
                break;

            case 2:
                linked();
                break;

            case 3:
                indexed();
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
