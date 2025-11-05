#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char c) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = c;
    n->left = n->right = NULL;
    return n;
}

struct Node* stack[100];
int top = -1;

void push(struct Node* n) { stack[++top] = n; }
struct Node* pop() { return stack[top--]; }

int isOperator(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/';
}

int precedence(char c) {
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    return 0;
}

// convert simple infix to postfix (no spaces)
void infixToPostfix(char infix[], char postfix[]) {
    char opStack[100];
    int topOp = -1;
    int k = 0;
    for(int i=0; infix[i]; i++) {
        char c = infix[i];
        if(isalnum(c)) postfix[k++] = c;
        else if(c=='(') opStack[++topOp] = c;
        else if(c==')') {
            while(topOp!=-1 && opStack[topOp]!='(')
                postfix[k++] = opStack[topOp--];
            if(topOp!=-1) topOp--;
        }
        else {
            while(topOp!=-1 && precedence(opStack[topOp]) >= precedence(c))
                postfix[k++] = opStack[topOp--];
            opStack[++topOp] = c;
        }
    }
    while(topOp!=-1) postfix[k++] = opStack[topOp--];
    postfix[k] = '\0';
}

// build tree from postfix
struct Node* buildTree(char postfix[]) {
    for(int i=0; postfix[i]; i++) {
        char c = postfix[i];
        if(!isOperator(c)) push(createNode(c));
        else {
            struct Node* right = pop();
            struct Node* left = pop();
            struct Node* n = createNode(c);
            n->left = left;
            n->right = right;
            push(n);
        }
    }
    return pop();
}

void printPrefix(struct Node* r) {
    if(!r) return;
    printf("%c", r->data);
    printPrefix(r->left);
    printPrefix(r->right);
}

void printPostfix(struct Node* r) {
    if(!r) return;
    printPostfix(r->left);
    printPostfix(r->right);
    printf("%c", r->data);
}

int main() {
    char infix[100], postfix[100];
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    struct Node* root = buildTree(postfix);
    printPrefix(root); printf("\n");
    printPostfix(root); printf("\n");
    return 0;
}
