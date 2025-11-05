#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Employee Node Structure ---
struct Employee {
    int id;
    char name[100];
    float salary;
    struct Employee *next;
};

// Global head pointer
struct Employee *head = NULL;

// Helper function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// a) Create employee record (adds to the end of the list)
void createEmployee() {
    // 1. Allocate memory
    struct Employee *newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    if (newEmployee == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // 2. Get data
    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee->id);
    clearInputBuffer(); // Clear buffer after scanf

    printf("Enter Employee Name: ");
    fgets(newEmployee->name, 100, stdin);
    newEmployee->name[strcspn(newEmployee->name, "\n")] = 0; // Remove newline

    printf("Enter Employee Salary: ");
    scanf("%f", &newEmployee->salary);
    clearInputBuffer(); // Clear buffer after scanf

    newEmployee->next = NULL;

    // 3. Add to list
    if (head == NULL) {
        // List is empty
        head = newEmployee;
    } else {
        // Traverse to the end
        struct Employee *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newEmployee;
    }
    printf("Employee record (ID: %d) created successfully!\n", newEmployee->id);
}

// b) Display all employees
void displayEmployees() {
    if (head == NULL) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\n--- All Employee Records ---\n");
    struct Employee *temp = head;
    while (temp != NULL) {
        printf("  ID     : %d\n", temp->id);
        printf("  Name   : %s\n", temp->name);
        printf("  Salary : %.2f\n", temp->salary);
        printf("----------------------------\n");
        temp = temp->next;
    }
}

// c) Search employee by id
void searchEmployee() {
    if (head == NULL) {
        printf("\nList is empty. Nothing to search.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    clearInputBuffer();

    struct Employee *temp = head;
    int found = 0;

    while (temp != NULL) {
        if (temp->id == id) {
            found = 1;
            break; // Found it
        }
        temp = temp->next;
    }

    // Display result
    if (found) {
        printf("\n--- Employee Found ---\n");
        printf("  ID     : %d\n", temp->id);
        printf("  Name   : %s\n", temp->name);
        printf("  Salary : %.2f\n", temp->salary);
        printf("----------------------\n");
    } else {
        printf("\nEmployee with ID %d not found.\n", id);
    }
}

// d) Delete employee by id
void deleteEmployee() {
    if (head == NULL) {
        printf("\nList is empty. Nothing to delete.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    struct Employee *temp = head;
    struct Employee *prev = NULL;

    // Case 1: Delete head node
    if (temp != NULL && temp->id == id) {
        head = temp->next; // Move head
        free(temp);        // Free old head
        printf("Employee with ID %d deleted.\n", id);
        return;
    }

    // Case 2: Search for the employee in the rest of the list
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If 'temp' is NULL, employee was not found
    if (temp == NULL) {
        printf("Employee with ID %d not found.\n", id);
    } else {
        // Unlink the node 'temp' from the list
        prev->next = temp->next;
        free(temp); // Free the memory
        printf("Employee with ID %d deleted successfully.\n", id);
    }
}


// --- Main Menu ---
int main() {
    int choice;
    while(1) {
        printf("\n--- Employee Record System ---\n");
        printf("1. Create employee record\n");
        printf("2. Display all employees\n");
        printf("3. Search employee by ID\n");
        printf("4. Delete employee by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // Clear newline after scanf

        switch (choice) {
            case 1:
                createEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                // Free all allocated memory before exiting
                printf("Exiting and cleaning up memory...\n");
                struct Employee *temp;
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
