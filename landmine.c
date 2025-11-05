#include <stdio.h>

#define N 4

int maze[N][N] = {
    {1, 0, 0, 0},
    {1, 1, 0, 1},
    {0, 1, 0, 0},
    {1, 1, 1, 1}
};

int solution[N][N];

int solve(int x, int y) {
    if (x == N - 1 && y == N - 1 && maze[x][y] == 1) {
        solution[x][y] = 1;
        return 1;
    }
    if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && solution[x][y] == 0) {
        solution[x][y] = 1;
        if (solve(x + 1, y))
            return 1;
        if (solve(x, y + 1))
            return 1;
        solution[x][y] = 0;
        return 0;
    }
    return 0;
}

int main() {
    if (solve(0, 0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%d ", solution[i][j]);
            printf("\n");
        }
    } else {
        printf("No path found\n");
    }
    return 0;
}
