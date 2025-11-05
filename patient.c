#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient node structure
struct Patient {
    int id;
    char name[100];
    int age;
    char disease[100];
    struct Patient *next;
};

// Global head pointer
struct Patient *head = NULL;

// Helper function to clear the input buffer
// This is crucial after using scanf to read a number before using fgets
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. Add a new patient (at the end of the list)
void addPatient() {
    // 1. Allocate memory for the new node
    struct Patient *newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    if (newPatient == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // 2. Get data from user
    printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);
    clearInputBuffer(); // Clear buffer after scanf

    printf("Enter Patient Name: ");
    fgets(newPatient->name, 100, stdin);
    newPatient->name[strcspn(newPatient->name, "\n")] = 0; // Remove newline

    printf("Enter Patient Age: ");
    scanf("%d", &newPatient->age);
    clearInputBuffer(); // Clear buffer after scanf

    printf("Enter Patient Disease: ");
    fgets(newPatient->disease, 100, stdin);
    newPatient->disease[strcspn(newPatient->disease, "\n")] = 0; // Remove newline

    newPatient->next = NULL;

    // 3. Add to list
    if (head == NULL) {
        // List is empty, new patient is the head
        head = newPatient;
    } else {
        // Traverse to the end of the list
        struct Patient *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Link the last node to the new patient
        temp->next = newPatient;
    }

    printf("Patient record added successfully!\n");
}

// 2. Display all patient records
void displayPatients() {
    if (head == NULL) {
        printf("\nNo patient records found.\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    struct Patient *temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("Record %d:\n", count++);
        printf("  ID      : %d\n", temp->id);
        printf("  Name    : %s\n", temp->name);
        printf("  Age     : %d\n", temp->age);
        printf("  Disease : %s\n", temp->disease);
        printf("----------------------------\n");
        temp = temp->next;
    }
}

// 3. Delete a patient record by name or id
void deletePatient() {
    if (head == NULL) {
        printf("\nList is empty. Nothing to delete.\n");
        return;
    }

    int choice;
    printf("Delete by 1. ID or 2. Name? ");
    scanf("%d", &choice);
    clearInputBuffer();

    struct Patient *temp = head;
    struct Patient *prev = NULL;
    int found = 0;

    if (choice == 1) {
        int id;
        printf("Enter Patient ID to delete: ");
        scanf("%d", &id);
        clearInputBuffer();

        // Check if head node is the one to delete
        if (temp != NULL && temp->id == id) {
            head = temp->next; // Move head
            free(temp);        // Free old head
            printf("Patient with ID %d deleted.\n", id);
            return;
        }

        // Search for the patient in the rest of the list
        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
    } else if (choice == 2) {
        char name[100];
        printf("Enter Patient Name to delete: ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline

        // Check head node
        if (temp != NULL && strcmp(temp->name, name) == 0) {
            head = temp->next;
            free(temp);
            printf("Patient with Name '%s' deleted.\n", name);
            return;
        }
        
        // Search in rest of the list
        while (temp != NULL && strcmp(temp->name, name) != 0) {
            prev = temp;
            temp = temp->next;
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    // At this point, 'temp' is the node to be deleted (or NULL if not found)
    
    if (temp == NULL) {
        printf("Patient not found.\n");
    } else {
        // Unlink the node from the list
        prev->next = temp->next;
        free(temp); // Free the memory
        printf("Patient record deleted successfully.\n");
    }
}

// 4. Search a patient record by id or name
void searchPatient() {
     if (head == NULL) {
        printf("\nList is empty. Nothing to search.\n");
        return;
    }

    int choice;
    printf("Search by 1. ID or 2. Name? ");
    scanf("%d", &choice);
    clearInputBuffer();

    struct Patient *temp = head;
    int found = 0;

    if (choice == 1) {
        int id;
        printf("Enter Patient ID to search: ");
        scanf("%d", &id);
        clearInputBuffer();

        while (temp != NULL) {
            if (temp->id == id) {
                found = 1;
                break; // Found it
            }
            temp = temp->next;
        }
    } else if (choice == 2) {
        char name[100];
        printf("Enter Patient Name to search: ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline

        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0) {
                found = 1;
                break; // Found it
            }
            temp = temp->next;
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    // Display result
    if (found) {
        printf("\n--- Patient Found ---\n");
        printf("  ID      : %d\n", temp->id);
        printf("  Name    : %s\n", temp->name);
        printf("  Age     : %d\n", temp->age);
        printf("  Disease : %s\n", temp->disease);
        printf("-----------------------\n");
    } else {
        printf("\nPatient not found.\n");
    }
}


int main() {
    int choice;
    while(1) {
        printf("\n--- Patient Record System ---\n");
        printf("1. Add a new patient\n");
        printf("2. Display all patient records\n");
        printf("3. Delete a patient record\n");
        printf("4. Search for a patient record\n");
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
                addPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                deletePatient();
                break;
            case 4:
                searchPatient();
                break;
            case 5:
                // Free all allocated memory before exiting
                printf("Exiting and cleaning up memory...\n");
                struct Patient *temp;
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
