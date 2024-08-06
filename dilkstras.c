#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure for a graph node
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Define the structure for a graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Function to create a new graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (Node**) malloc(numVertices * sizeof(Node*));

    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Function to print the shortest distances from the source vertex
void printDistances(int* distances, int numVertices) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\n", i, distances[i]);
    }
}

// Function to implement Dijkstra's algorithm
void dijkstra(Graph* graph, int src) {
    int* distances = (int*) malloc(graph->numVertices * sizeof(int));
    int* visited = (int*) malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    distances[src] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++) {
        int minDistance = INT_MAX;
        int minVertex = -1;

        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minVertex = j;
            }
        }

        visited[minVertex] = 1;

        Node* temp = graph->adjLists[minVertex];

        while (temp != NULL) {
            if (!visited[temp->vertex] && distances[minVertex] + temp->weight < distances[temp->vertex]) {
                distances[temp->vertex] = distances[minVertex] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printDistances(distances, graph->numVertices);

    free(distances);
    free(visited);
}

int main() {
    int numVertices = 5;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 3, 4, 3);

    int src = 0;
    dijkstra(graph, src);

    return 0;
}
