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

// Display the linked list (print sentence)
void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

// Find and replace word in the linked list
void findAndReplace(struct Node* head, const char* target, const char* replacement) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->word, target) == 0) {
            strcpy(temp->word, replacement);
        }
        temp = temp->next;
    }
}

// Free the memory
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    char sentence[200], target[50], replacement[50];
    struct Node* head = NULL;
    char *token;

    printf("Enter a sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // Remove newline

    // Split sentence into words and build linked list
    token = strtok(sentence, " ");
    while (token != NULL) {
        head = insertEnd(head, token);
        token = strtok(NULL, " ");
    }

    printf("\nOriginal sentence:\n");
    displayList(head);

    printf("\nEnter the word to find: ");
    scanf("%s", target);
    printf("Enter the replacement word: ");
    scanf("%s", replacement);

    findAndReplace(head, target, replacement);

    printf("\nModified sentence:\n");
    displayList(head);

    freeList(head);
    return 0;
}


Enter a sentence:
Data structures are the backbone of efficient algorithms

Original sentence:
Data structures are the backbone of efficient algorithms

Enter the word to find: backbone
Enter the replacement word: pillar

Modified sentence:
Data structures are the pillar of efficient algorithms

