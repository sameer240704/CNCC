#include <bits/stdc++.h>
using namespace std;

#define MAX_VERTICES 100;

vector<int> BellmanFord(vector<vector<int>> edges, int V, int source) {
    vector<int> dist(V, 1e8);
    dist[source] = 0;

    for(int i=0 ; i<V ; i++) {
        for(vector<int> edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            if(dist[u] != 1e8 && dist[u] + w < dist[v]) {
                if(i == V-1)
                    return {-1};
                dist[v] = dist[u] + w;
            }
        }
    }

    return dist;
}

int main() {
    int V, E, source;
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the source of the graph: ";
    cin >> source;

    vector<vector<int>> edges;
    cout << "Enter the edges (u v weight):" << endl;
    for(int i=0 ; i<E ; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<int> result;
    result = BellmanFord(edges, V, source);

    if(result.size() == 1 && result[0] == -1) {
        cout << "Negative Cycle Detected" << endl;
    } else {
        cout << "Shortest distances from source " << source << ":" << endl;
        for(int i=0 ; i<V ; i++) {
            if(result[i] == 1e8)
                cout << "Vertex " << i << ": INF" << endl;
            else
                cout << "Vertex " << i << ": "<< result[i] << endl;
        }   
    }
}

/*

Input:-
Enter the number of vertices: 5
Enter the number of edges: 5
Enter the source of the graph: 0
Enter the edges (u v weight):
0 1 5
1 2 1
1 3 2
2 4 1
4 3 -1

Output:-
Shortest distances from source 0:
Vertex 0: 0
Vertex 1: 5
Vertex 2: 6
Vertex 3: 6
Vertex 4: 7

*/