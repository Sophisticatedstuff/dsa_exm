#include<stdio.h>

int visited[100];

// DFS function (recursive)
void dfs(int adj[10][10], int start, int n) {
    int i;
    printf("%d ", start);
    visited[start] = 1;
    
    for (i = 0; i < n; i++) {
        if (adj[start][i] == 1 && !visited[i])
            dfs(adj, i, n);
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
    
    printf("DFS Traversal: ");
    dfs(adj, start, n);
    
    return 0;
}
