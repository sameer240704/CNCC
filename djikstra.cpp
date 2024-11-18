#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100

int minDistance(int dist[], bool Q[], int V) {
    int minDist = INT_MAX, minIndex;

    for (int i = 0; i < V; i++) {
        if (Q[i] && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int V, int source) {
    int dist[MAX_VERTICES]; 
    int prev[MAX_VERTICES]; 
    bool Q[MAX_VERTICES];   

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        Q[i] = true; 
    }

    dist[source] = 0; 

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, Q, V); 
        Q[u] = false;                   

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && Q[v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) 
        printf("%d\t\t%d\n", i, dist[i]);
}

int main() {
    int V, source;
    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, V, source);

    return 0;
}
