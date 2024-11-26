#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// A structure to represent a node in the priority queue
struct Node {
    int vertex, weight;
    Node(int v, int w) : vertex(v), weight(w) {}
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

int primMST(int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> key(V, INT_MAX);  // Key values to pick minimum weight edge
    vector<bool> inMST(V, false); // To track vertices included in MST
    vector<int> parent(V, -1);    // Array to store constructed MST
    priority_queue<Node, vector<Node>, greater<Node>> pq; // Min-heap priority queue

    key[0] = 0;  // Start from vertex 0
    pq.push(Node(0, 0)); // First node to start

    int mstWeight = 0;  // Store total weight of MST

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        if (inMST[u]) continue; // Skip if the vertex is already in MST
        inMST[u] = true;
        mstWeight += key[u];  // Add edge weight to total weight

        // Traverse all adjacent vertices of u
        for (auto& [v, weight] : adj[u]) {
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(Node(v, key[v]));
                parent[v] = u;
            }
        }
    }

    // Output the MST
    cout << "Prim's MST edges:" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << endl;
    }

    return mstWeight;
}

int main() {
    int V, E;
    cin >> V >> E;  // Number of vertices and edges
    vector<vector<pair<int, int>>> adj(V);  // Adjacency list representation

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);  // Since the graph is undirected
    }

    cout << "Total weight of Prim's MST: " << primMST(V, adj) << endl;

    return 0;
}
