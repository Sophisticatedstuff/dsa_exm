#include <stdio.h>
void printArray(int arr[],int low, int high) {
    for (int i=low; i<high; i++)
        printf("%d ", arr[i]);
    
}
void readArray(int arr[], int n) {
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (first element as pivot)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // last element as pivot
    int i = low;             // start pointer
    int j = high - 1;        // end pointer (just before pivot)

    while (1) {
        // Move i to the right until arr[i] > pivot
        while (i <= high - 1 && arr[i] <= pivot)
            i++;

        // Move j to the left until arr[j] < pivot
        while (j >= low && arr[j] > pivot)
            j--;

        // If pointers cross, break
        if (i >= j)
            break;

        // Swap elements on wrong sides
        swap(&arr[i], &arr[j]);
    }

    // Place pivot in correct position
    swap(&arr[i], &arr[high]);
    return i;  // return pivot position
}

// Quicksort function
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        printArray(arr,low,pivotIndex);
        printf("\t*%d\t",arr[pivotIndex]);
        printArray(arr,pivotIndex+1,high+1);
        printf("\n");
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

int main() {
    int arr[50] ;
    int n;
    
    printf("Enter the number of elements \n");
    scanf("%d",&n);
    printf("Enter the array elements\n");
    readArray(arr,n);
    
    printf("Original array: ");
    printArray(arr,0, n);
    printf("\n");
    quicksort(arr,0,n-1);

    printf("Sorted array: ");
    printArray(arr,0, n);
    printf("\n");
    return 0;
}
