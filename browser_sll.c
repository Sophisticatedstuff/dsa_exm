#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 100

// --- Singly Linked List Node ---
struct Node {
    char url[MAX_URL_LENGTH];
    struct Node *next;
};

// --- Stack (implemented using SLL) ---
// We wrap the SLL head in a 'Stack' struct for clarity
struct Stack {
    struct Node *head; // 'head' is the 'top' of the stack
};

// --- Global Stacks and Current Page ---
struct Stack backStack = {NULL};
struct Stack forwardStack = {NULL};
char currentPage[MAX_URL_LENGTH] = "Home Page"; // Start at a default page

// --- Stack Operations ---

// Push a URL onto a stack (add to head of SLL)
void push(struct Stack *stack, const char *url) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    strncpy(newNode->url, url, MAX_URL_LENGTH);
    
    newNode->next = stack->head;
    stack->head = newNode;
}

// Pop a URL from a stack (remove from head of SLL)
// Returns 1 on success (and fills 'poppedUrl'), 0 on failure (empty stack)
int pop(struct Stack *stack, char *poppedUrl) {
    if (stack->head == NULL) {
        return 0; // Stack is empty
    }
    
    struct Node *temp = stack->head;
    strncpy(poppedUrl, temp->url, MAX_URL_LENGTH); // Copy data out
    
    stack->head = stack->head->next; // Move head
    free(temp); // Free old top node
    
    return 1;
}

// Clear an entire stack (free all nodes in the SLL)
void clearStack(struct Stack *stack) {
    printf("  (Clearing forward history...)\n");
    char tempUrl[MAX_URL_LENGTH];
    while (pop(stack, tempUrl)) {
        // The pop function handles freeing memory
        printf("    - Cleared %s\n", tempUrl);
    }
    printf("  (Forward history cleared)\n");
}

// --- Browser Navigation Functions ---

void visitNewPage(const char *url) {
    // 1. Push the old 'currentPage' onto the backStack
    push(&backStack, currentPage);
    
    // 2. Set the 'currentPage' to the new URL
    strncpy(currentPage, url, MAX_URL_LENGTH);
    
    // 3. Visiting a new page clears the forward history
    if (forwardStack.head != NULL) {
        clearStack(&forwardStack);
    }
    
    printf("\nVisited new page: %s\n", currentPage);
}

void navigateBack() {
    char newUrl[MAX_URL_LENGTH];
    
    // 1. Pop from backStack to get the new page
    if (pop(&backStack, newUrl)) {
        // 2. Push the current (soon-to-be old) page onto forwardStack
        push(&forwardStack, currentPage);
        // 3. Set currentPage to the one we popped
        strncpy(currentPage, newUrl, MAX_URL_LENGTH);
        printf("\nNavigated BACK to: %s\n", currentPage);
    } else {
        printf("\nCannot navigate back. No history.\n");
    }
}

void navigateForward() {
    char newUrl[MAX_URL_LENGTH];
    
    // 1. Pop from forwardStack to get the new page
    if (pop(&forwardStack, newUrl)) {
        // 2. Push the current (soon-to-be old) page onto backStack
        push(&backStack, currentPage);
        // 3. Set currentPage to the one we popped
        strncpy(currentPage, newUrl, MAX_URL_LENGTH);
        printf("\nNavigated FORWARD to: %s\n", currentPage);
    } else {
        printf("\nCannot navigate forward. No forward pages.\n");
    }
}

void showCurrentPage() {
    printf("\n--- Browser State ---\n");
    if (backStack.head != NULL) {
        printf("  [Back]   <- ");
    } else {
        printf("  [    ]   <- ");
    }

    printf("CURRENT: %s", currentPage);

    if (forwardStack.head != NULL) {
        printf(" -> [Forward]\n");
    } else {
        printf(" -> [       ]\n");
    }
    printf("---------------------\n");
}

int main() {
    int choice;
    char url[MAX_URL_LENGTH];

    // Start with a default page so logic is simpler
    // visitNewPage("google.com"); 
    // We'll use the default "Home Page"

    while (1) {
        showCurrentPage();
        printf("\nMenu:\n");
        printf("1. Visit a new page\n");
        printf("2. Navigate Back\n");
        printf("3. Navigate Forward\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear invalid input
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter URL to visit: ");
                scanf("%99s", url);
                visitNewPage(url);
                break;
            case 2:
                navigateBack();
                break;
            case 3:
                navigateForward();
                break;
            case 4:
                // Free all memory before exiting
                clearStack(&backStack);
                clearStack(&forwardStack);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
