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
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// E. Traversal (Display)
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

// A. Insert at End
void insertAtEnd(int data) {
    struct Node *newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
        printf("Inserted %d at the beginning (list was empty).\n", data);
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at the end.\n", data);
}

// B. Insert After an Element
void insertAfter(int searchData, int newData) {
    if (head == NULL) {
        printf("List is empty. Cannot insert after.\n");
        return;
    }
    struct Node *temp = head;
    // Find the node with searchData
    while (temp != NULL && temp->data != searchData) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element %d not found in the list.\n", searchData);
    } else {
        struct Node *newNode = createNode(newData);
        newNode->next = temp->next;
        temp->next = newNode;
        printf("Inserted %d after %d.\n", newData, searchData);
    }
}

// G. Insertion Before an Element
void insertBefore(int searchData, int newData) {
    if (head == NULL) {
        printf("List is empty. Cannot insert before.\n");
        return;
    }
    
    // Case 1: Insert before the head
    if (head->data == searchData) {
        struct Node *newNode = createNode(newData);
        newNode->next = head;
        head = newNode;
        printf("Inserted %d before head element %d.\n", newData, searchData);
        return;
    }

    // Case 2: Insert in the middle or end
    struct Node *temp = head;
    struct Node *prev = NULL;
    
    while (temp != NULL && temp->data != searchData) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element %d not found in the list.\n", searchData);
    } else {
        // 'prev' is the node before 'temp' (which has searchData)
        struct Node *newNode = createNode(newData);
        newNode->next = temp; // or prev->next
        prev->next = newNode;
        printf("Inserted %d before %d.\n", newData, searchData);
    }
}

// C. Delete a Particular Element
void deleteElement(int data) {
    if (head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    
    struct Node *temp = head;
    struct Node *prev = NULL;

    // Case 1: Delete head node
    if (temp != NULL && temp->data == data) {
        head = temp->next;
        free(temp);
        printf("Deleted head element %d.\n", data);
        return;
    }

    // Case 2: Search for the element
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Element %d not found in the list.\n", data);
    } else {
        // Unlink the node
        prev->next = temp->next;
        free(temp);
        printf("Deleted element %d.\n", data);
    }
}

// D. Count the Number of Elements
void countElements() {
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Number of elements in the list: %d\n", count);
}

// F. Reverse the List (Iterative)
void reverseList() {
    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next = NULL;

    while (current != NULL) {
        next = current->next; // Store next
        current->next = prev; // Reverse current node's pointer
        
        // Move pointers one position ahead
        prev = current;
        current = next;
    }
    head = prev; // 'prev' is the new head
    printf("List reversed.\n");
    displayList(); // Show the result
}

// H. Deletion of Duplicate Nodes
void deleteDuplicates() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node *ptr1, *ptr2, *dup;
    ptr1 = head;

    // Pick elements one by one
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;

        // Compare the picked element with rest of the list
        while (ptr2->next != NULL) {
            // If duplicate, delete it
            if (ptr1->data == ptr2->next->data) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            } else {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
    printf("All duplicate nodes removed.\n");
    displayList(); // Show the result
}


// --- Main Menu ---
int main() {
    int choice, data, searchData;
    while(1) {
        printf("\n--- SLL All Operations Menu ---\n");
        printf("1.  (A) Insert at End\n");
        printf("2.  (B) Insert After an Element\n");
        printf("3.  (G) Insert Before an Element\n");
        printf("4.  (C) Delete a Particular Element\n");
        printf("5.  (D) Count Elements\n");
        printf("6.  (E) Display List (Traversal)\n");
        printf("7.  (F) Reverse the List\n");
        printf("8.  (H) Delete Duplicate Nodes\n");
        printf("9.  Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(data);
                break;
            case 2:
                printf("Enter data of the element to find: ");
                scanf("%d", &searchData);
                printf("Enter new data to insert after %d: ", searchData);
                scanf("%d", &data);
                insertAfter(searchData, data);
                break;
            case 3:
                printf("Enter data of the element to find: ");
                scanf("%d", &searchData);
                printf("Enter new data to insert before %d: ", searchData);
                scanf("%d", &data);
                insertBefore(searchData, data);
                break;
            case 4:
                printf("Enter data of the element to delete: ");
                scanf("%d", &data);
                deleteElement(data);
                break;
            case 5:
                countElements();
                break;
            case 6:
                displayList();
                break;
            case 7:
                reverseList();
                break;
            case 8:
                deleteDuplicates();
                break;
            case 9:
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
