#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 50 // Max non-zero terms
#define MAX_ROWS 10
#define MAX_COLS 10

// --- 3-Tuple (Triplet) Structure ---
struct Term {
    int row;
    int col;
    int value;
};

// --- Sparse Matrix Structure ---
struct SparseMatrix {
    int rows;       // Total number of rows
    int cols;       // Total number of columns
    int numTerms;   // Number of non-zero terms
    struct Term terms[MAX_TERMS];
};

// --- Function to create a sparse matrix from a 2D array ---
void createSparseMatrix(struct SparseMatrix *sm, int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    sm->rows = rows;
    sm->cols = cols;
    sm->numTerms = 0; // Reset count
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                if (sm->numTerms >= MAX_TERMS) {
                    printf("Error: Too many terms. Increase MAX_TERMS.\n");
                    return;
                }
                sm->terms[sm->numTerms].row = i;
                sm->terms[sm->numTerms].col = j;
                sm->terms[sm->numTerms].value = matrix[i][j];
                sm->numTerms++;
            }
        }
    }
}

// --- Function to display in 3-Tuple (Triplet) format ---
void displaySparseTriplets(struct SparseMatrix *sm, char *title) {
    printf("\n--- %s (Triplet Format) ---\n", title);
    printf("Rows: %d, Cols: %d, Non-Zero: %d\n", sm->rows, sm->cols, sm->numTerms);
    printf("Row | Col | Value\n");
    printf("-----------------\n");
    for (int i = 0; i < sm->numTerms; i++) {
        printf("%-3d | %-3d | %-5d\n", 
            sm->terms[i].row, 
            sm->terms[i].col, 
            sm->terms[i].value);
    }
}

// --- Function to display as a full 2D matrix ---
void displayAsMatrix(struct SparseMatrix *sm, char *title) {
    printf("\n--- %s (Full Matrix Format) ---\n", title);
    
    int matrix[MAX_ROWS][MAX_COLS] = {0}; // Initialize a full zero-matrix
    
    // Fill in the non-zero values
    for (int i = 0; i < sm->numTerms; i++) {
        matrix[sm->terms[i].row][sm->terms[i].col] = sm->terms[i].value;
    }
    
    // Print the full matrix
    for (int i = 0; i < sm->rows; i++) {
        for (int j = 0; j < sm->cols; j++) {
            printf("%-3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// --- 1. Merge (Add) two sparse matrices ---
void mergeImages(struct SparseMatrix *sm1, struct SparseMatrix *sm2, struct SparseMatrix *result) {
    if (sm1->rows != sm2->rows || sm1->cols != sm2->cols) {
        printf("Error: Matrices must have the same dimensions to merge (add).\n");
        return;
    }

    result->rows = sm1->rows;
    result->cols = sm1->cols;
    result->numTerms = 0;
    
    int i = 0; // Pointer for sm1->terms
    int j = 0; // Pointer for sm2->terms
    int k = 0; // Pointer for result->terms

    while (i < sm1->numTerms && j < sm2->numTerms) {
        if (sm1->terms[i].row < sm2->terms[j].row ||
           (sm1->terms[i].row == sm2->terms[j].row && sm1->terms[i].col < sm2->terms[j].col)) {
            // sm1's term comes first
            result->terms[k++] = sm1->terms[i++];
        } 
        else if (sm1->terms[i].row > sm2->terms[j].row ||
                (sm1->terms[i].row == sm2->terms[j].row && sm1->terms[i].col > sm2->terms[j].col)) {
            // sm2's term comes first
            result->terms[k++] = sm2->terms[j++];
        } 
        else {
            // Both matrices have a term at the same (row, col)
            int sum = sm1->terms[i].value + sm2->terms[j].value;
            if (sum != 0) { // Only store if sum is non-zero
                result->terms[k].row = sm1->terms[i].row;
                result->terms[k].col = sm1->terms[i].col;
                result->terms[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }
    
    // Copy remaining terms from sm1 (if any)
    while (i < sm1->numTerms) {
        result->terms[k++] = sm1->terms[i++];
    }
    // Copy remaining terms from sm2 (if any)
    while (j < sm2->numTerms) {
        result->terms[k++] = sm2->terms[j++];
    }
    
    result->numTerms = k;
}

// --- Helper: Sort terms (needed after rotation) ---
// Simple bubble sort by row, then col
void sortTerms(struct SparseMatrix *sm) {
    for (int i = 0; i < sm->numTerms - 1; i++) {
        for (int j = 0; j < sm->numTerms - i - 1; j++) {
            // Compare row
            int row1 = sm->terms[j].row;
            int row2 = sm->terms[j+1].row;
            // Compare col
            int col1 = sm->terms[j].col;
            int col2 = sm->terms[j+1].col;

            if (row1 > row2 || (row1 == row2 && col1 > col2)) {
                // Swap
                struct Term temp = sm->terms[j];
                sm->terms[j] = sm->terms[j+1];
                sm->terms[j+1] = temp;
            }
        }
    }
}

// --- 2. Rotate the resultant image vertically ---
void rotateVertically(struct SparseMatrix *sm) {
    int totalRows = sm->rows;
    
    for (int i = 0; i < sm->numTerms; i++) {
        sm->terms[i].row = (totalRows - 1) - sm->terms[i].row;
    }
    
    // After rotation, the terms are no longer in row-major order.
    // We must re-sort them.
    sortTerms(sm);
    printf("\nMatrix has been rotated vertically.\n");
}


// --- Main Function ---
int main() {
    // Example Image 1 (4x4)
    int img1[MAX_ROWS][MAX_COLS] = {
        {0, 0, 0, 5},
        {0, 2, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 3, 0}
    };

    // Example Image 2 (4x4)
    int img2[MAX_ROWS][MAX_COLS] = {
        {0, 0, 1, 0},
        {0, 2, 0, 0},
        {0, 0, 0, 9},
        {0, 0, 0, 0}
    };

    int rows = 4, cols = 4;
    
    struct SparseMatrix sparseImg1, sparseImg2, mergedImg, rotatedImg;

    // --- Create ---
    createSparseMatrix(&sparseImg1, img1, rows, cols);
    displayAsMatrix(&sparseImg1, "Image 1");
    displaySparseTriplets(&sparseImg1, "Image 1");

    createSparseMatrix(&sparseImg2, img2, rows, cols);
    displayAsMatrix(&sparseImg2, "Image 2");
    displaySparseTriplets(&sparseImg2, "Image 2");
    
    // --- Merge ---
    mergeImages(&sparseImg1, &sparseImg2, &mergedImg);
    displayAsMatrix(&mergedImg, "Merged Image (Image 1 + Image 2)");
    displaySparseTriplets(&mergedImg, "Merged Image");

    // --- Rotate ---
    // We copy mergedImg to rotatedImg to preserve the original merged one
    rotatedImg = mergedImg; 
    rotateVertically(&rotatedImg);
    displayAsMatrix(&rotatedImg, "Rotated Merged Image");
    displaySparseTriplets(&rotatedImg, "Rotated Merged Image");

    return 0;
}
