#include <stdio.h>

void warshall(int p[10][10], int n) {
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                p[i][j] = p[i][j] || (p[i][k] && p[k][j]);
}

void printMatrix(int p[10][10], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", p[i][j]);
        printf("\n");
    }
}

int main() {
    int p[10][10], n, i, j;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &p[i][j]);
    printf("Input Matrix:\n");
    printMatrix(p, n);
    warshall(p, n);
    printf("Transitive Closure:\n");
    printMatrix(p, n);
    return 0;
}
