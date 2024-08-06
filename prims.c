#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure for a graph
typedef struct Graph {
    int numVertices;
    int** adjMatrix;
} Graph;

// Function to create a new graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjMatrix = (int**) malloc(numVertices * sizeof(int*));

    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (int*) malloc(numVertices * sizeof(int));

        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

// Function to print the minimum spanning tree
void printMST(int* parent, int numVertices, Graph* graph) {
    printf("Edge\tcost\n");

    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d\t%d\n", parent[i], i, graph->adjMatrix[i][parent[i]]);
    }
}

// Function to find the vertex with the minimum key value
int minKey(int* key, int* mstSet, int numVertices) {
    int minKey = INT_MAX;
    int minVertex = -1;

    for (int i = 0; i < numVertices; i++) {
        if (!mstSet[i] && key[i] < minKey) {
            minKey = key[i];
            minVertex = i;
        }
    }

    return minVertex;
}

// Function to implement Prim's algorithm
void primMST(Graph* graph) {
    int* key = (int*) malloc(graph->numVertices * sizeof(int));
    int* parent = (int*) malloc(graph->numVertices * sizeof(int));
    int* mstSet = (int*) malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int u = minKey(key, mstSet, graph->numVertices);
        mstSet[u] = 1;

        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjMatrix[u][v] > 0 && !mstSet[v] && graph->adjMatrix[u][v] < key[v]) {
                key[v] = graph->adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    printMST(parent, graph->numVertices, graph);

    free(key);
    free(parent);
    free(mstSet);
}

int main() {
    int numVertices = 5;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);

    primMST(graph);

    return 0;
}
