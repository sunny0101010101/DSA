#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure to represent an edge
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// A class to represent Union-Find (Disjoint Set)
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                ++rank[rootU];
            }
        }
    }
};

int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // Sort edges by weight

    UnionFind uf(V);  // Create Union-Find for V vertices
    vector<Edge> mstEdges;  // Store MST edges
    int mstWeight = 0;

    for (auto& edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mstEdges.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    // Output the MST
    cout << "Kruskal's MST edges:" << endl;
    for (auto& edge : mstEdges) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }

    return mstWeight;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;  // Number of vertices and edges
    vector<Edge> edges(E);  // List of all edges

    for (int i = 0; i < E; ++i) {
        cout << "Enter edge " << i + 1 << " (u, v, weight): ";
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    cout << "Total weight of Kruskal's MST: " << kruskalMST(V, edges) << endl;

    return 0;
}
