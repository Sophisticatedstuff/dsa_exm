#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ---------- Stack implemented using Linked List ----------
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// push a character
Node* push(Node* top, char x) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->next = top;
    return temp;
}

// pop top element
Node* pop(Node* top, char* popped) {
    if (!top) return NULL;
    *popped = top->data;
    Node* temp = top;
    top = top->next;
    free(temp);
    return top;
}

// view top element
char peek(Node* top) {
    return (top) ? top->data : '\0';
}

int isEmpty(Node* top) {
    return (top == NULL);
}

// ---------- Helper functions ----------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void reverse(char* exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char t = exp[i];
        exp[i] = exp[len - i - 1];
        exp[len - i - 1] = t;
    }
}

void swapParentheses(char* exp) {
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }
}

// ---------- Infix → Postfix ----------
void infixToPostfix(char infix[], char postfix[]) {
    Node* stack = NULL;
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            stack = push(stack, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                char temp;
                stack = pop(stack, &temp);
                postfix[k++] = temp;
            }
            char dummy;
            stack = pop(stack, &dummy); // remove '('
        }
        else { // operator
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(ch)) {
                char temp;
                stack = pop(stack, &temp);
                postfix[k++] = temp;
            }
            stack = push(stack, ch);
        }
    }
    while (!isEmpty(stack)) {
        char temp;
        stack = pop(stack, &temp);
        postfix[k++] = temp;
    }
    postfix[k] = '\0';
}

// ---------- Infix → Prefix ----------
void infixToPrefix(char infix[], char prefix[]) {
    char tempInfix[100], postfix[100];
    strcpy(tempInfix, infix);
    reverse(tempInfix);
    swapParentheses(tempInfix);
    infixToPostfix(tempInfix, postfix);
    reverse(postfix);
    strcpy(prefix, postfix);
}

// ---------- Menu ----------
int main() {
    char infix[100], postfix[100], prefix[100];
    int choice;

    while (1) {
        printf("\n========== Expression Conversion ==========\n");
        printf("1. Infix to Postfix\n");
        printf("2. Infix to Prefix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Exiting program...\n");
            break;
        }

        printf("Enter infix expression: ");
        scanf("%s", infix);

        switch (choice) {
            case 1:
                infixToPostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 2:
                infixToPrefix(infix, prefix);
                printf("Prefix Expression:  %s\n", prefix);
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
