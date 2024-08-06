#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head[MAX_VERTICES];
} Graph;

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = dest;
    newNode->next = graph->head[src];
    graph->head[src] = newNode;
}

void dfs(Graph* graph, int vertex, int* visited, int* stack, int* top) {
    visited[vertex] = 1;
    Node* temp = graph->head[vertex];
    while (temp!= NULL) {
        if (!visited[temp->data]) {
            dfs(graph, temp->data, visited, stack, top);
        }
        temp = temp->next;
    }
    stack[(*top)++] = vertex;
}

void topologicalSort(Graph* graph, int vertices) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES];
    int top = 0;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, stack, &top);
        }
    }
    printf("Topological Sort: ");
    for (int i = top - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    Graph graph;
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph.head[i] = NULL;
    }
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    topologicalSort(&graph, 5);
    return 0;
}
