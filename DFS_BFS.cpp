#include<bits/stdc++.h>

using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int v) {
        vertices = v;
        adjList.resize(v);
    }

    void addEdge(int a, int b) {
        if (a >= vertices || b >= vertices) {
            cout << "Invalid edge! Vertex out of range.\n";
            return;
        }
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    void removeEdge(int a, int b) {
        adjList[a].erase(remove(adjList[a].begin(), adjList[a].end(), b), adjList[a].end());
        adjList[b].erase(remove(adjList[b].begin(), adjList[b].end(), a), adjList[b].end());
    }

    void dfsIterative(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;
        int components = 0;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                components++;
                s.push(i);

                while (!s.empty()) {
                    int node = s.top();
                    s.pop();
                    if (!visited[node]) {
                        cout << node << " ";
                        visited[node] = true;
                        for (int neighbor : adjList[node]) {
                            if (!visited[neighbor]) s.push(neighbor);
                        }
                    }
                }
            }
        }
        cout << "\nTotal Components: " << components << endl;
    }

    void dfsRecursiveHelper(int node, vector<bool>& visited) {
        cout << node << " ";
        visited[node] = true;
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) dfsRecursiveHelper(neighbor, visited);
        }
    }

    void dfsRecursive() {
        vector<bool> visited(vertices, false);
        int components = 0;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                components++;
                dfsRecursiveHelper(i, visited);
            }
        }
        cout << "\nTotal Components: " << components << endl;
    }

    void bfs(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        int components = 0;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                components++;
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    cout << node << " ";
                    for (int neighbor : adjList[node]) {
                        if (!visited[neighbor]) {
                            q.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }
                }
            }
        }
        cout << "\nTotal Components: " << components << endl;
    }
};

int main() {
    int n, m, choice;
    cout << "Enter number of vertices: ";
    cin >> n;
    Graph g(n);

    while (true) {
        cout << "\n1. Add Edge\n2. Remove Edge\n3. DFS (Iterative)\n4. DFS (Recursive)\n5. BFS\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int a, b;
            cout << "Enter edge (u v): ";
            cin >> a >> b;
            g.addEdge(a, b);
        } 
        else if (choice == 2) {
            int a, b;
            cout << "Enter edge to remove (u v): ";
            cin >> a >> b;
            g.removeEdge(a, b);
        } 
        else if (choice == 3) {
            cout << "DFS (Iterative): ";
            g.dfsIterative(0);
        } 
        else if (choice == 4) {
            cout << "DFS (Recursive): ";
            g.dfsRecursive();
        } 
        else if (choice == 5) {
            cout << "BFS: ";
            g.bfs(0);
        } 
        else {
            break;
        }
    }

    return 0;
}
