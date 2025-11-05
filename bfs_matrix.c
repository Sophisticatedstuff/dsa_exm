#include<stdio.h>
#include<stdlib.h>

int queue[100], front = -1, rear = -1;
int visited[100];

// Enqueue
void enqueue(int value) {
    if (rear == 99)
        printf("Queue Overflow\n");
    else {
        if (front == -1)
            front = 0;
        queue[++rear] = value;
    }
}

// Dequeue
int dequeue() {
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

// BFS Function
void bfs(int adj[10][10], int start, int n) {
    int i;
    enqueue(start);
    visited[start] = 1;
    printf("BFS Traversal: ");
    
    while (front <= rear) {
        int current = dequeue();
        printf("%d ", current);
        
        for (i = 0; i < n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                enqueue(i);
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
    
    bfs(adj, start, n);
    
    return 0;
}
