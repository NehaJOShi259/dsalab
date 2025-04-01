#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

map<int, vector<int>> g; // Graph to store routes

void addRoute(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u); // Bidirectional routes
}

void showRoutes() {
    for (const auto& p : g) {
        cout << "City " << p.first << " -> ";
        for (int c : p.second) cout << c << " ";
        cout << endl;
    }
}

// BFS to find if there's a path from start to finish
bool bfs(int start, int finish) {
    if (start == finish) return true; // No need to search if start is the same as finish
    
    map<int, bool> visited;
    queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int city = q.front();
        q.pop();
        
        for (int neighbor : g[city]) {
            if (!visited[neighbor]) {
                if (neighbor == finish) return true; // Path found
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    
    return false; // No path found
}

void findRoute(int s, int f) {
    if (g.find(s) == g.end() || g.find(f) == g.end()) {
        cout << "Route not found!\n";
        return;
    }

    if (bfs(s, f)) {
        cout << "There is a path from " << s << " to " << f << endl;
    } else {
        cout << "No path exists from " << s << " to " << f << endl;
    }
}

int main() {
    int ch, u, v, s, f;
    while (true) {
        cout << "\n1. Add Route\n2. Show Routes\n3. Find Route\n4. Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Enter cities (u v): ";
            cin >> u >> v;
            addRoute(u, v);
        } else if (ch == 2) {
            showRoutes();
        } else if (ch == 3) {
            cout << "Enter start & end: ";
            cin >> s >> f;
            findRoute(s, f);
        } else if (ch == 4) break;
        else cout << "Invalid choice!\n";
    }
    return 0;
}
