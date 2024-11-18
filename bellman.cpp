#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int source, destination, weight;
};

struct Graph {
    int V; 
    int E; 
    struct Edge* edge; 
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

void BellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int distance[V];
    
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;
    
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }
    
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }
    
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, distance[i]);
    }
}

int main() {
    int V, E;
    
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    struct Graph* graph = createGraph(V, E);
    
    printf("Enter source, destination, and weight for each edge:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].source, &graph->edge[i].destination,
              &graph->edge[i].weight);
    }
    
    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);
    
    BellmanFord(graph, source);
    
    free(graph->edge);
    free(graph);

    return 0;
}
