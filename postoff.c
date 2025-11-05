#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define node
struct Node {
    char name[100];
    int priority;
    struct Node* next;
};

struct Node* front = NULL;

// Create a new node
struct Node* createNode(char name[], int priority) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(temp->name, name);
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

// Insert based on priority
void enqueue(char name[], int priority) {
    struct Node* newNode = createNode(name, priority);

    if (front == NULL || priority > front->priority) {
        newNode->next = front;
        front = newNode;
    } else {
        struct Node* temp = front;
        while (temp->next != NULL && temp->next->priority >= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    printf("Customer %s added with priority %d\n", name, priority);
}

// Remove from front
void dequeue() {
    if (front == NULL) {
        printf("No customers to serve.\n");
    } else {
        struct Node* temp = front;
        printf("Serving Customer: %s (Priority: %d)\n", front->name, front->priority);
        front = front->next;
        free(temp);
    }
}

// Display queue
void displayQueue() {
    struct Node* temp = front;
    if (temp == NULL) {
        printf("No customers in queue.\n");
    } else {
        printf("\nQueue:\n");
        while (temp != NULL) {
            printf("%s (Priority: %d) -> ", temp->name, temp->priority);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}


int main() {
    int choice;
    char name[100], category[100];
    int priority;

    do {
        printf("\nMenu\n----\n");
        printf("1. Add Customer\n");
        printf("2. Serve Customer\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume leftover newline

        switch(choice) {
            case 1:
                printf("Enter customer name: ");
                gets(name);
                printf("Enter customer category(Differently Abled-4/Senior Citizen-3/Defence Personnel-2/Ordinary-1): ");
                scanf("%d",&priority);
                enqueue(name, priority);
                displayQueue();
                break;
            case 2:
                dequeue();
                displayQueue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 4);

    return 0;
}
