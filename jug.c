#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000

typedef struct {
    int a, b, c;  // State of three jugs
} State;

typedef struct Node {
    State state;
    struct Node* parent;
} Node;

typedef struct {
    Node* items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

bool isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Node* value) {
    q->items[q->rear++] = value;
}

Node* dequeue(Queue* q) {
    return q->items[q->front++];
}

bool visited[11][8][5];  // capacities (10,7,4)

// Pour from one jug to another
State pour(State s, int fromCap, int toCap, int from, int to) {
    int amount = (from < (toCap - to)) ? from : (toCap - to);
    from -= amount;
    to += amount;

    State newState = s;
    if (fromCap == 10) newState.a = from;
    if (fromCap == 7) newState.b = from;
    if (fromCap == 4) newState.c = from;

    if (toCap == 10) newState.a = to;
    if (toCap == 7) newState.b = to;
    if (toCap == 4) newState.c = to;

    return newState;
}

// Check goal
bool isGoal(State s) {
    return (s.b == 2 || s.c == 2);
}

// Print the path
void printPath(Node* node) {
    if (node == NULL) return;
    printPath(node->parent);
    printf("(%d, %d, %d)\n", node->state.a, node->state.b, node->state.c);
}

void BFS(State start) {
    Queue q;
    initQueue(&q);

    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->state = start;
    startNode->parent = NULL;
    enqueue(&q, startNode);
    visited[start.a][start.b][start.c] = true;

    while (!isEmpty(&q)) {
        Node* current = dequeue(&q);
        State s = current->state;

        if (isGoal(s)) {
            printf("Goal reached!\n");
            printPath(current);
            return;
        }

        // All possible pourings
        State nextStates[6];
        nextStates[0] = pour(s, 10, 7, s.a, s.b); // A → B
        nextStates[1] = pour(s, 10, 4, s.a, s.c); // A → C
        nextStates[2] = pour(s, 7, 10, s.b, s.a); // B → A
        nextStates[3] = pour(s, 7, 4, s.b, s.c);  // B → C
        nextStates[4] = pour(s, 4, 10, s.c, s.a); // C → A
        nextStates[5] = pour(s, 4, 7, s.c, s.b);  // C → B

        for (int i = 0; i < 6; i++) {
            State ns = nextStates[i];
            if (!visited[ns.a][ns.b][ns.c]) {
                visited[ns.a][ns.b][ns.c] = true;
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = ns;
                newNode->parent = current;
                enqueue(&q, newNode);
            }
        }
    }
    printf("No solution found.\n");
}

int main() {
    State start = {0, 7, 4};  // (10L empty, 7L full, 4L full)
    BFS(start);
    return 0;
}
