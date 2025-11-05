#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    struct Node* next;
};

// Create a new node
struct Node* createNode(const char* word) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

// Insert node at end
struct Node* insertEnd(struct Node* head, const char* word) {
    struct Node* newNode = createNode(word);
    if (head == NULL)
        return newNode;
    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    return head;
}

// Count occurrences of a given word
int countOccurrences(struct Node* head, const char* target) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->word, target) == 0)
            count++;
        temp = temp->next;
    }
    return count;
}

// Display the list
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

// Free memory
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    char sentence[200], target[50];
    char *token;

    printf("Enter a sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // remove newline

    // Build linked list from words
    token = strtok(sentence, " ");
    while (token != NULL) {
        head = insertEnd(head, token);
        token = strtok(NULL, " ");
    }

    printf("\nThe sentence as stored in linked list:\n");
    displayList(head);

    printf("\nEnter the word to count: ");
    scanf("%s", target);

    int count = countOccurrences(head, target);
    printf("\nThe word '%s' occurred %d time(s).\n", target, count);

    freeList(head);
    return 0;
}
