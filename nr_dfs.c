#include<stdio.h>

int stack[100], top = -1;
int visited[100];

// Push operation
void push(int value) {
    stack[++top] = value;
}

// Pop operation
int pop() {
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

// DFS without recursion
void dfs_non_recursive(int adj[10][10], int start, int n) {
    int i;
    push(start);
    visited[start] = 1;
    printf("DFS Traversal (non-recursive): ");
    
    while (top != -1) {
        int current = pop();
        printf("%d ", current);
        
        for (i = n-1; i >= 0; i--) {  // Traverse neighbors in reverse order
            if (adj[current][i] == 1 && !visited[i]) {
                push(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n, adj[10][10], i, j, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter adjacency matrix:\n");
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            scanf("%d", &adj[i][j]);
            
    printf("Enter starting vertex (0 to %d): ", n-1);
    scanf("%d", &start);
    
    dfs_non_recursive(adj, start, n);
    
    return 0;
}
