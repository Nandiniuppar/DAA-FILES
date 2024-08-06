#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 99999 // A value representing infinity

// Function to print the matrix
void printMatrix(int size, int **graph) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (graph[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to implement Floyd Warshall algorithm
void floydWarshall(int size, int **graph) {
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (graph[i][k] != INF && graph[k][j] != INF && graph[i][k] + graph[k][j] < graph[i][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }
}

int main() {
    // Graph 1 (size 4)
    int size1 = 4;
    int graph1[4][4] = {
        {0, INF, 3, 7},
        {2, 0, INF, INF},
        {INF, 7, 0, 1},
        {6, INF, INF, INF}
    };

    // Graph 2 (size 5)
    int size2 = 5;
    int graph2[5][5] = {
        {0, 5, INF, 10, INF},
        {INF, 0, 3, INF, 7},
        {INF, INF, 0, 1, INF},
        {INF, INF, INF, 0, 2},
        {2, INF, INF, INF, 0}
    };

    // Graph 3 (size 3)
    int size3 = 3;
    int graph3[3][3] = {
        {0, 3, INF},
        {INF, 0, INF},
        {INF, 4, 0}
    };

    int sizes[] = {size1, size2, size3};
    int *graphs[] = {(int *)graph1, (int *)graph2, (int *)graph3};

    for (int g = 0; g < 3; g++) {
        int size = sizes[g];
        int *graph = (int *)malloc(size * sizeof(int *));
        for (int i = 0; i < size; i++) {
            graph[i] = (int *)malloc(size * sizeof(int));
            for (int j = 0; j < size; j++) {
                graph[i][j] = *((int *)graphs[g] + i * size + j);
            }
        }

        printf("\nOriginal Graph %d (size %d):\n", g + 1, size);
        printMatrix(size, graph);

        // Time complexity calculation with delay
        clock_t start, end;
        double cpu_time_used;
        double delay_time = 0.001; // Delay time in seconds

        start = clock();
        floydWarshall(size, graph);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("\nShortest Paths Matrix for Graph %d (size %d):\n", g + 1, size);
        printMatrix(size, graph);

        printf("\nTime taken to compute shortest paths for Graph %d: %f seconds\n", g + 1, cpu_time_used);
        printf("Time complexity: O(%d^3)\n", size);

        // Adding delay to factor in delay time
        double total_time_with_delay = cpu_time_used + (size * size * size * delay_time);
        printf("Total time with delay factored in: %f seconds\n\n", total_time_with_delay);

        for (int i = 0; i < size; i++) {
            free(graph[i]);
        }
        free(graph);
    }

    return 0;
}
