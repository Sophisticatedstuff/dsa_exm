#include <stdio.h>

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n-1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (arr[mid] == key)
            return mid;
        else if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    
    return -1; // Key not found
}

int main() {
    int arr[100], n, key, result;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    printf("Enter sorted elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    printf("Enter the key to search: ");
    scanf("%d", &key);
    
    result = binarySearch(arr, n, key);
    
    if (result == -1)
        printf("Key not found.\n");
    else
        printf("Key found at index %d.\n", result);
    
    return 0;
}

C Program - Binary Search Recursive

#include <stdio.h>

// Recursive binary search function
int binarySearch(int arr[], int low, int high, int key) {
    if (low > high)
        return -1; // Key not found

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;
    else if (key < arr[mid])
        return binarySearch(arr, low, mid - 1, key); // Search left half
    else
        return binarySearch(arr, mid + 1, high, key); // Search right half
}

int main() {
    int arr[100], n, key, result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter sorted elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the key to search: ");
    scanf("%d", &key);

    result = binarySearch(arr, 0, n-1, key);

    if (result == -1)
        printf("Key not found.\n");
    else
        printf("Key found at index %d.\n", result);

    return 0;
}
