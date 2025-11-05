#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int pow;
    struct Node* next;
};

// Global heads
struct Node* poly1 = NULL;
struct Node* poly2 = NULL;
struct Node* result = NULL;

// Insert node into Polynomial 1
void insertPoly1(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;

    if (poly1 == NULL) {
        poly1 = newNode;
    } else {
        struct Node* temp = poly1;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Insert node into Polynomial 2
void insertPoly2(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;

    if (poly2 == NULL) {
        poly2 = newNode;
    } else {
        struct Node* temp = poly2;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Insert node into Result polynomial
void insertResult(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;

    if (result == NULL) {
        result = newNode;
    } else {
        struct Node* temp = result;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Display any polynomial
void display(struct Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    struct Node* temp = poly;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->pow);
        if (temp->next != NULL)
            printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

// Addition of poly1 and poly2 → result
void addPolynomials() {
    result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->pow == p2->pow) {
            insertResult(p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->pow > p2->pow) {
            insertResult(p1->coeff, p1->pow);
            p1 = p1->next;
        } else {
            insertResult(p2->coeff, p2->pow);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        insertResult(p1->coeff, p1->pow);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertResult(p2->coeff, p2->pow);
        p2 = p2->next;
    }
}

// Multiplication of poly1 and poly2 → result
void multiplyPolynomials() {
    result = NULL;

    for (struct Node* t1 = poly1; t1 != NULL; t1 = t1->next) {
        for (struct Node* t2 = poly2; t2 != NULL; t2 = t2->next) {
            int c = t1->coeff * t2->coeff;
            int p = t1->pow + t2->pow;

            // Check if power already exists in result
            struct Node* temp = result;
            struct Node* prev = NULL;
            while (temp != NULL && temp->pow != p) {
                prev = temp;
                temp = temp->next;
            }

            if (temp != NULL) {
                temp->coeff += c;
            } else {
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->coeff = c;
                newNode->pow = p;
                newNode->next = NULL;

                if (prev == NULL)
                    result = newNode;
                else
                    prev->next = newNode;
            }
        }
    }
}

// Main menu
int main() {
    int choice, coeff, pow;

    do {
        printf("\n--- Polynomial Menu ---\n");
        printf("1. Insert term in Polynomial 1\n");
        printf("2. Insert term in Polynomial 2\n");
        printf("3. Display Polynomial 1\n");
        printf("4. Display Polynomial 2\n");
        printf("5. Add Polynomials\n");
        printf("6. Multiply Polynomials\n");
        printf("7. Display Result Polynomial\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter coefficient and power: ");
                scanf("%d%d", &coeff, &pow);
                insertPoly1(coeff, pow);
                break;
            case 2:
                printf("Enter coefficient and power: ");
                scanf("%d%d", &coeff, &pow);
                insertPoly2(coeff, pow);
                break;
            case 3:
                printf("Polynomial 1: ");
                display(poly1);
                break;
            case 4:
                printf("Polynomial 2: ");
                display(poly2);
                break;
            case 5:
                addPolynomials();
                printf("Addition done.\n");
                break;
            case 6:
                multiplyPolynomials();
                printf("Multiplication done.\n");
                break;
            case 7:
                printf("Result Polynomial: ");
                display(result);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 8);

    return 0;
}
