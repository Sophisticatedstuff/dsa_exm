#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// --- Structure for a queue element ---
struct QueueItem {
    int data;
    int priority; // Lower value means higher priority
};

// --- Global Priority Queue ---
struct QueueItem priorityQueue[MAX_SIZE];
int size = 0; // Tracks the number of elements in the queue

// --- Helper: Check if queue is full ---
int isFull() {
    return size == MAX_SIZE;
}

// --- Helper: Check if queue is empty ---
int isEmpty() {
    return size == 0;
}

// --- 1. Insert an element ---
void insert() {
    if (isFull()) {
        printf("Priority Queue is full. Cannot insert.\n");
        return;
    }

    int data, priority;
    printf("Enter data: ");
    scanf("%d", &data);
    printf("Enter priority (lower number is higher priority): ");
    scanf("%d", &priority);

    // Add the new item to the end of the array
    priorityQueue[size].data = data;
    priorityQueue[size].priority = priority;
    size++;

    printf("Data (%d) with priority (%d) inserted.\n", data, priority);
}

// --- 2. Delete the highest priority element ---
// (This means deleting the element with the LOWEST priority value)
void deleteHighestPriority() {
    if (isEmpty()) {
        printf("Priority Queue is empty. Cannot delete.\n");
        return;
    }

    int highestPriority = priorityQueue[0].priority;
    int elementIndex = 0;

    // 1. Find the index of the element with the highest priority (lowest value)
    for (int i = 1; i < size; i++) {
        if (priorityQueue[i].priority < highestPriority) {
            highestPriority = priorityQueue[i].priority;
            elementIndex = i;
        }
    }

    // 2. Store the element to be deleted (for display)
    struct QueueItem deletedItem = priorityQueue[elementIndex];

    // 3. Shift all elements after the deleted one
    for (int i = elementIndex; i < size - 1; i++) {
        priorityQueue[i] = priorityQueue[i + 1];
    }

    // 4. Decrement the size
    size--;

    printf("Deleted data (%d) with highest priority (%d).\n", 
           deletedItem.data, deletedItem.priority);
}

// --- 3. Display the queue ---
void display() {
    if (isEmpty()) {
        printf("\nPriority Queue is empty.\n");
        return;
    }

    printf("\n--- Priority Queue Contents ---\n");
    printf("(Index) | Data | Priority\n");
    printf("------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("  (%d)   | %-4d | %-8d\n", 
               i, priorityQueue[i].data, priorityQueue[i].priority);
    }
}

// --- Main Menu ---
int main() {
    int choice;
    while(1) {
        printf("\n--- Priority Queue Menu ---\n");
        printf("1. Insert element\n");
        printf("2. Delete highest priority element\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                deleteHighestPriority();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
