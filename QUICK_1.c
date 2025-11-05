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
    int pivot = arr[low];  // choose first element as pivot
    int i = low + 1;
    int j = high;

    while (1) {
        // move i forward while elements are <= pivot
        while (i <= high && arr[i] <= pivot) {
            i++;
        }
        // move j backward while elements are > pivot
        while (j >= low && arr[j] > pivot) {
            j--;
        }

        if (i < j) {
            swap(&arr[i], &arr[j]);
        } else {
            break;
        }
    }
    // place pivot in correct position
    swap(&arr[low], &arr[j]);
    
    return j;  // return pivot index
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

Output
Enter the number of elements 
7
Enter the array elements
8 3 1 7 0 10 2
Original array: 8 3 1 7 0 10 2 
2 3 1 7 0       *8      10 
1 0     *2      7 3 
0       *1
3       *7
Sorted array: 0 1 2 3 7 8 10 

