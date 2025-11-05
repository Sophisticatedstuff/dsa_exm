#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constants ---
#define MAX_NAME_LEN 50

// --- Node Structure ---
struct Node {
    char name[MAX_NAME_LEN];
    int indexNo;
    int value;
    
    struct Node *prev; // Previous node pointer
    struct Node *next; // Next node pointer
};

// --- Global Pointers ---
struct Node *head = NULL;
struct Node *tail = NULL;

// --- Helper: Create a New Node ---
struct Node* createNode(const char *n, int i, int v) {
    struct Node newNode = (struct Node)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Exiting.\n");
        exit(1);
    }
    strncpy(newNode->name, n, MAX_NAME_LEN - 1);
    newNode->name[MAX_NAME_LEN - 1] = '\0';
    newNode->indexNo = i;
    newNode->value = v;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// --- Utility: Get Input Data ---
void getNodeData(char *n, int *i, int *v) {
    printf("Enter Name (str): ");
    // Clear buffer and read string
    while (getchar() != '\n'); 
    if (fgets(n, MAX_NAME_LEN, stdin) == NULL) {
        *i = -1; // Sentinel value to indicate error
        return;
    }
    n[strcspn(n, "\n")] = 0; // Remove newline
    
    printf("Enter Index Number (int): ");
    if (scanf("%d", i) != 1) {
        printf("Invalid input. Try again.\n");
        *i = -1;
        while (getchar() != '\n'); 
        return;
    }
    
    printf("Enter Value (int): ");
    if (scanf("%d", v) != 1) {
        printf("Invalid input. Try again.\n");
        *i = -1;
        while (getchar() != '\n'); 
        return;
    }
}

// --- Utility: Get List Length ---
int getLength() {
    int count = 0;
    struct Node *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

// ==========================================================
// --- INSERTION OPERATIONS (ADD) ---
// ==========================================================

void insertAtFront(const char *n, int i, int v) {
    struct Node *newNode = createNode(n, i, v);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    printf("Node added at the FRONT.\n");
}

void insertAtLast(const char *n, int i, int v) {
    struct Node *newNode = createNode(n, i, v);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    printf("Node added at the LAST.\n");
}

void insertAtIndex(const char *n, int i, int v, int index) {
    int len = getLength();
    
    if (index < 0 || index > len) {
        printf("Error: Index %d is out of bounds (0 to %d).\n", index, len);
        return;
    }
    
    if (index == 0) {
        insertAtFront(n, i, v);
        return;
    }
    
    if (index == len) {
        insertAtLast(n, i, v);
        return;
    }
    
    struct Node *newNode = createNode(n, i, v);
    struct Node *curr = head;
    
    // Traverse to the node before the desired index
    for (int k = 0; k < index - 1; k++) {
        curr = curr->next;
    }
    
    // Link the new node in
    newNode->next = curr->next;
    newNode->prev = curr;
    curr->next->prev = newNode;
    curr->next = newNode;
    
    printf("Node added at index %d.\n", index);
}

// ==========================================================
// --- DELETION OPERATIONS ---
// ==========================================================

void deleteNode(struct Node *delNode) {
    if (delNode == NULL) return;

    if (delNode == head) {
        head = delNode->next;
    }
    if (delNode == tail) {
        tail = delNode->prev;
    }
    
    // Bypass the node
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }
    
    printf("Deleted record: %s (Index: %d, Value: %d)\n", delNode->name, delNode->indexNo, delNode->value);
    free(delNode);
}

void deleteFirst() {
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    deleteNode(head);
}

void deleteLast() {
    if (tail == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    deleteNode(tail);
}

void deleteAtIndex(int index) {
    int len = getLength();
    
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    
    if (index < 0 || index >= len) {
        printf("Error: Index %d is out of bounds (0 to %d).\n", index, len - 1);
        return;
    }
    
    if (index == 0) {
        deleteFirst();
        return;
    }
    
    struct Node *curr = head;
    for (int k = 0; k < index; k++) {
        curr = curr->next;
    }
    
    deleteNode(curr);
}

// ==========================================================
// --- UNIQUE OPERATION: CLRDELETE ---
// ==========================================================

void clrDelete(int index) {
    int len = getLength();
    
    if (head == NULL) {
        printf("List is empty. Nothing to clear.\n");
        return;
    }
    
    if (index < 0 || index >= len) {
        printf("Error: Index %d is out of bounds (0 to %d).\n", index, len - 1);
        return;
    }
    
    struct Node *start = head;
    
    // 1. Find the node to start deleting from
    for (int k = 0; k < index; k++) {
        start = start->next;
    }
    
    // 2. Adjust the list structure
    if (start->prev != NULL) {
        start->prev->next = NULL; // The node before 'start' becomes the new tail
        tail = start->prev;
    } else {
        // If index 0 is chosen, the list becomes empty
        head = NULL;
        tail = NULL;
    }
    
    // 3. Free all nodes starting from 'start'
    struct Node *curr = start;
    struct Node *temp;
    int count = 0;
    
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
        count++;
    }
    
    printf("\nCLRDELETE complete. %d nodes (from index %d to the end) were deleted.\n", count, index);
}

// ==========================================================
// --- SEARCH OPERATIONS ---
// ==========================================================

void searchByName() {
    char searchName[MAX_NAME_LEN];
    struct Node *curr = head;
    int found = 0;
    
    printf("\n--- Search By Name ---\n");
    printf("Enter Name to search (case sensitive): ");
    
    // Clear buffer and read string
    while (getchar() != '\n'); 
    if (fgets(searchName, MAX_NAME_LEN, stdin) == NULL) return;
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline
    
    printf("\nSearch Results for '%s':\n", searchName);
    printf("%-5s | %-20s | %-8s | %-5s\n", "IDX", "NAME", "INDEX NO", "VALUE");
    printf("--------------------------------------------------\n");

    int k = 0;
    while (curr != NULL) {
        // Use strcmp for case-sensitive comparison
        if (strcmp(curr->name, searchName) == 0) {
            printf("%-5d | %-20s | %-8d | %-5d\n", k, curr->name, curr->indexNo, curr->value);
            found = 1;
        }
        curr = curr->next;
        k++;
    }
    
    if (!found) {
        printf("No student found with the name '%s'.\n", searchName);
    }
    printf("--------------------------------------------------\n");
}

// ==========================================================
// --- DISPLAY OPERATIONS ---
// ==========================================================

// Display all records (Forward Traversal)
void displayForward() {
    struct Node *curr = head;
    if (head == NULL) {
        printf("\nList is empty.\n");
        return;
    }
    
    printf("\n--- Student Records (Forward Traversal) ---\n");
    printf("%-5s | %-20s | %-8s | %-5s\n", "IDX", "NAME", "INDEX NO", "VALUE");
    printf("--------------------------------------------------\n");
    
    int k = 0;
    while (curr != NULL) {
        printf("%-5d | %-20s | %-8d | %-5d\n", k++, curr->name, curr->indexNo, curr->value);
        curr = curr->next;
    }
    printf("--------------------------------------------------\n");
}

// Display all records (Backward Traversal)
void displayBackward() {
    struct Node *curr = tail;
    if (tail == NULL) {
        printf("\nList is empty.\n");
        return;
    }
    
    printf("\n--- Student Records (Backward Traversal) ---\n");
    printf("%-5s | %-20s | %-8s | %-5s\n", "IDX", "NAME", "INDEX NO", "VALUE");
    printf("--------------------------------------------------\n");
    
    int k = getLength() - 1;
    while (curr != NULL) {
        printf("%-5d | %-20s | %-8d | %-5d\n", k--, curr->name, curr->indexNo, curr->value);
        curr = curr->prev;
    }
    printf("--------------------------------------------------\n");
}

// ==========================================================
// --- MAIN MENU ---
// ==========================================================

void printMenu() {
    printf("\n\n--- Doubly Linked List Menu (Length: %d) ---\n", getLength());
    printf("--- INSERTION ---\n");
    printf("1. Add at FRONT\n");
    printf("2. Add at LAST\n");
    printf("3. Add at SPECIFIC INDEX\n");
    printf("--- DISPLAY ---\n");
    printf("4. Display ALL (Forward)\n");
    printf("5. Display ALL (Backward)\n");
    printf("--- DELETION ---\n");
    printf("6. Delete FIRST Node\n");
    printf("7. Delete LAST Node\n");
    printf("8. Delete at SPECIFIC INDEX\n");
    printf("9. CLRDELETE (Delete from index X to the end)\n");
    printf("--- SEARCH ---\n");
    printf("10. Search By Name\n");
    printf("11. Exit\n");
    printf("Enter your choice: ");
}

void cleanup() {
    struct Node *curr = head;
    struct Node *temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    head = NULL;
    tail = NULL;
}

int main() {
    int choice, index;
    char n[MAX_NAME_LEN];
    int i, v;

    // Initial data for testing
    insertAtLast("First", 10, 100);
    insertAtLast("Second", 20, 200);
    insertAtLast("Third", 30, 300);

    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid choice. Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: // Add at FRONT
                getNodeData(n, &i, &v);
                if (i != -1) insertAtFront(n, i, v);
                break;
            case 2: // Add at LAST
                getNodeData(n, &i, &v);
                if (i != -1) insertAtLast(n, i, v);
                break;
            case 3: // Add at SPECIFIC INDEX
                printf("Enter index to insert at: ");
                if (scanf("%d", &index) != 1) break;
                getNodeData(n, &i, &v);
                if (i != -1) insertAtIndex(n, i, v, index);
                break;
            case 4: // Display Forward
                displayForward();
                break;
            case 5: // Display Backward
                displayBackward();
                break;
            case 6: // Delete FIRST
                deleteFirst();
                break;
            case 7: // Delete LAST
                deleteLast();
                break;
            case 8: // Delete at SPECIFIC INDEX
                printf("Enter index to delete: ");
                if (scanf("%d", &index) != 1) break;
                deleteAtIndex(index);
                break;
            case 9: // CLRDELETE
                printf("Enter starting index for CLRDELETE (will delete this node and all after it): ");
                if (scanf("%d", &index) != 1) break;
                clrDelete(index);
                break;
            case 10: // Search By Name (New)
                searchByName();
                break;
            case 11:
                printf("\nExiting program. Cleaning up memory.\n");
                cleanup();
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 11);

    return 0;
}
