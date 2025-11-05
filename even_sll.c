#include <stdio.h>
#include <stdlib.h>

// --- Node Structure ---
struct Node {
    int data;
    struct Node *next;
};

// Global head pointer
struct Node *head = NULL;

// --- Helper: Create Node ---
struct Node* createNode(int data) {
    structNode *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// --- Helper: Insert at End (to populate the list) ---
void insertAtEnd(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// --- Helper: Display List ---
void displayList() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node *temp = head;
    printf("List: head -> ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 1. Display even numbers
void displayEven() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    printf("Even numbers in the list: ");
    struct Node *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->data % 2 == 0) {
            printf("%d ", temp->data);
            found = 1;
        }
        temp = temp->next;
    }
    
    if (!found) {
        printf("None");
    }
    printf("\n");
}

// 2. Count even numbers
void countEven() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        if (temp->data % 2 == 0) {
            count++;
        }
        temp = temp->next;
    }
    printf("Total count of even numbers: %d\n", count);
}

// 3. Delete even nos. and insert them at the end of the list
void moveEvenToEnd() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty or has only one element. No changes made.\n");
        return;
    }

    struct Node *oddHead = NULL, *oddTail = NULL;
    struct Node *evenHead = NULL, *evenTail = NULL;
    struct Node *current = head;

    while (current != NULL) {
        // Store the next node before we detach 'current'
        struct Node *nextNode = current->next;

        // Isolate the current node
        current->next = NULL;

        if (current->data % 2 == 0) {
            // It's even. Add to the even list.
            if (evenHead == NULL) {
                evenHead = evenTail = current;
            } else {
                evenTail->next = current;
                evenTail = current;
            }
        } else {
            // It's odd. Add to the odd list.
            if (oddHead == NULL) {
                oddHead = oddTail = current;
            } else {
                oddTail->next = current;
                oddTail = current;
            }
        }
        // Move to the next node in the original list
        current = nextNode;
    }

    // Now, link the odd list and the even list
    if (oddHead == NULL) {
        // List had only even numbers
        head = evenHead;
    } else {
        // List had some odd numbers
        head = oddHead;
        oddTail->next = evenHead; // Link end of odds to start of evens
    }

    printf("Even numbers moved to the end of the list.\n");
    displayList();
}


// --- Main Menu ---
int main() {
    int choice, data;
    while(1) {
        printf("\n--- Even/Odd SLL Operations ---\n");
        printf("1. Add number to list (at end)\n");
        printf("2. Display full list\n");
        printf("3. Display EVEN numbers\n");
        printf("4. Count EVEN numbers\n");
        printf("5. Move EVEN numbers to end\n");
        printf("6. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtEnd(data);
                printf("%d inserted.\n", data);
                break;
            case 2:
                displayList();
                break;
            case 3:
                displayEven();
                break;
            case 4:
                countEven();
                break;
            case 5:
                moveEvenToEnd();
                break;
            case 6:
                // Free all memory
                printf("Exiting and cleaning up memory...\n");
                struct Node *temp;
                while (head != NULL) {
                    temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
