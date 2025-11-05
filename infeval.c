#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

// --- Character Stack for Infix to Postfix Conversion ---

struct CharStack {
    int top;
    char items[MAX_SIZE];
};

void char_push(struct CharStack *s, char c) {
    if (s->top == MAX_SIZE - 1) {
        printf("Char Stack Overflow!\n");
    } else {
        s->items[++(s->top)] = c;
    }
}

char char_pop(struct CharStack *s) {
    if (s->top == -1) {
        return '\0'; // Return null char for empty stack
    } else {
        return s->items[(s->top)--];
    }
}

char char_peek(struct CharStack *s) {
    if (s->top == -1) {
        return '\0';
    } else {
        return s.items[s->top];
    }
}

int isEmptyChar(struct CharStack *s) {
    return s->top == -1;
}

// --- Integer Stack for Postfix Evaluation ---

struct IntStack {
    int top;
    int items[MAX_SIZE];
};

void int_push(struct IntStack *s, int val) {
    if (s->top == MAX_SIZE - 1) {
        printf("Int Stack Overflow!\n");
    } else {
        s.items[++(s->top)] = val;
    }
}

int int_pop(struct IntStack *s) {
    if (s->top == -1) {
        return -1; // Return -1 for empty stack (can be problematic if -1 is a valid num)
    } else {
        return s->items[(s->top)--];
    }
}

int isEmptyInt(struct IntStack *s) {
    return s->top == -1;
}


// --- Core Logic ---

// Function to return precedence of operators
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0; // For parentheses
    }
}

// Function to convert Infix expression to Postfix
void infixToPostfix(char *infix, char *postfix) {
    struct CharStack s;
    s.top = -1;
    int i = 0; // Infix counter
    int j = 0; // Postfix counter

    while (infix[i] != '\0') {
        char token = infix[i];

        // If operand (a-z, A-Z, 0-9), add to postfix
        if (isalnum(token)) {
            postfix[j++] = token;
        }
        // If '(', push to stack
        else if (token == '(') {
            char_push(&s, token);
        }
        // If ')', pop and add to postfix until '(' is found
        else if (token == ')') {
            while (!isEmptyChar(&s) && char_peek(&s) != '(') {
                postfix[j++] = char_pop(&s);
            }
            char_pop(&s); // Pop '('
        }
        // If operator
        else {
            // Pop operators with higher or equal precedence
            while (!isEmptyChar(&s) && precedence(char_peek(&s)) >= precedence(token)) {
                postfix[j++] = char_pop(&s);
            }
            char_push(&s, token);
        }
        i++;
    }

    // Pop all remaining operators from the stack
    while (!isEmptyChar(&s)) {
        postfix[j++] = char_pop(&s);
    }
    postfix[j] = '\0'; // Null-terminate the postfix string
}

// Function to evaluate Postfix expression
int evaluatePostfix(char *postfix) {
    struct IntStack s;
    s.top = -1;
    int i = 0;

    while (postfix[i] != '\0') {
        char token = postfix[i];

        // If operand (digit), push to int stack
        if (isdigit(token)) {
            // Convert char digit to int
            int_push(&s, token - '0');
        }
        // If operator, pop two operands, perform operation, and push result
        else {
            int op2 = int_pop(&s);
            int op1 = int_pop(&s);

            switch (token) {
                case '+': int_push(&s, op1 + op2); break;
                case '-': int_push(&s, op1 - op2); break;
                case '*': int_push(&s, op1 * op2); break;
                case '/': int_push(&s, op1 / op2); break;
                case '^': int_push(&s, (int)pow(op1, op2)); break;
            }
        }
        i++;
    }
    // The final result is the last item on the stack
    return int_pop(&s);
}

// --- Main Function ---

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an Infix expression (e.g., (2+3)*(4-1)): ");
    fgets(infix, MAX_SIZE, stdin);
    // Remove newline character from fgets
    infix[strcspn(infix, "\n")] = 0;

    // 1. Conversion
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // 2. Evaluation
    int result = evaluatePostfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}
