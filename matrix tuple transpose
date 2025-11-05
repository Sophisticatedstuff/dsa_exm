#include <stdio.h>

struct Term {
    int row;
    int col;
    int value;
};

void transpose(struct Term sparse[], struct Term transpose[]) {
    int i, j, n;
    n = sparse[0].value; // number of non-zero elements

    // Step 1: Metadata for transpose
    transpose[0].row = sparse[0].col;
    transpose[0].col = sparse[0].row;
    transpose[0].value = sparse[0].value;

    // Step 2: Swap row and col for each non-zero element
    int k = 1; // index for transpose array
    for (i = 0; i < sparse[0].col; i++) { // for each column of original
        for (j = 1; j <= n; j++) {         // check all elements
            if (sparse[j].col == i) {
                transpose[k].row = sparse[j].col;
                transpose[k].col = sparse[j].row;
                transpose[k].value = sparse[j].value;
                k++;
            }
        }
    }
}

void display(struct Term sparse[]) {
    int n = sparse[0].value; // number of non-zero elements
    printf("Row  Col  Value\n");
    for (int i = 0; i <= n; i++) {
        printf("%3d %4d %5d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }
}

int main() {
    int rows, cols, n;

    printf("Enter number of rows, columns, and non-zero elements: ");
    scanf("%d %d %d", &rows, &cols, &n);

    struct Term sparse[50], transposed[50];

    sparse[0].row = rows;
    sparse[0].col = cols;
    sparse[0].value = n;

    printf("Enter the non-zero elements (row column value):\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &sparse[i].row, &sparse[i].col, &sparse[i].value);
    }

    printf("\nOriginal Sparse Matrix Representation:\n");
    display(sparse);

    transpose(sparse, transposed);

    printf("\nTransposed Sparse Matrix Representation:\n");
    display(transposed);

    return 0;
}
