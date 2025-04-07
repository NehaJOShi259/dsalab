#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(V, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

int main() {
    int V, E;
    cout << "Enter number of cities and routes: ";
    cin >> V >> E;

    Graph g(V);
    cout << "Enter routes (city1 city2 distance):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int S, F;
    cout << "Enter starting and destination city: ";
    cin >> S >> F;

    vector<int> dist = g.dijkstra(S);

    if (dist[F] == INF)
        cout << "No path exists from " << S << " to " << F << "." << endl;
    else
        cout << "Shortest distance from " << S << " to " << F << " is: " << dist[F] << endl;

    return 0;
}
