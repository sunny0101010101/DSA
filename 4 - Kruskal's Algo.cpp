#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure to represent an edge
struct Edge {
    int u, v, weight; // u and v are the vertices connected by the edge, and weight is the cost
    bool operator<(const Edge& other) const {
        // Overload the < operator to sort edges by weight
        return weight < other.weight;
    }
};

// A class to represent Union-Find (Disjoint Set)
class UnionFind {
    vector<int> parent, rank; // Parent array for tracking roots, rank for optimization
public:
    // Constructor to initialize Union-Find for 'n' elements
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0); // Rank initialized to 0
        for (int i = 0; i < n; ++i) parent[i] = i; // Each node is its own parent
    }

    // Find operation with path compression
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    // Union operation with rank optimization
    void unite(int u, int v) {
        int rootU = find(u); // Find root of u
        int rootV = find(v); // Find root of v

        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV; // Attach tree of rootU under rootV
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU; // Attach tree of rootV under rootU
            } else {
                parent[rootV] = rootU; // Attach tree of rootV under rootU
                ++rank[rootU]; // Increment rank of rootU
            }
        }
    }
};

// Function to find Minimum Spanning Tree (MST) using Kruskal's Algorithm
int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // Sort edges by weight in ascending order

    UnionFind uf(V);  // Initialize Union-Find for V vertices
    vector<Edge> mstEdges;  // Vector to store edges included in the MST
    int mstWeight = 0; // Total weight of the MST

    // Iterate over sorted edges
    for (auto& edge : edges) {
        // If the current edge does not form a cycle
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v); // Union the sets containing u and v
            mstEdges.push_back(edge); // Add the edge to MST
            mstWeight += edge.weight; // Add the weight of the edge to the MST weight
        }
    }

    // Output the edges in the MST
    cout << "Kruskal's MST edges:" << endl;
    for (auto& edge : mstEdges) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }

    return mstWeight; // Return the total weight of the MST
}

int main() {
    int V, E; // V: Number of vertices, E: Number of edges
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E; // Input the number of vertices and edges
    vector<Edge> edges(E); // Vector to store all edges

    // Input the edges
    for (int i = 0; i < E; ++i) {
        cout << "Enter edge " << i + 1 << " (u, v, weight): ";
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Compute and output the total weight of Kruskal's MST
    cout << "Total weight of Kruskal's MST: " << kruskalMST(V, edges) << endl;

    return 0;
}

/*
Explanation of the Code:
1. **Edge Representation**:
   - Each edge is represented by a structure containing its two endpoints (`u` and `v`) and the weight (`weight`).

2. **Union-Find**:
   - This data structure efficiently handles connected component queries using `find` (with path compression) and `unite` (with rank optimization).

3. **Kruskal's Algorithm**:
   - Sort edges by weight.
   - Process edges in ascending order of weight, adding each edge to the MST if it does not form a cycle (using Union-Find).

4. **Output**:
   - Prints the edges in the MST and their total weight.
   - The MST edges are listed as `u - v : weight`.

5. **Time Complexity**:
   - Sorting edges: `O(E log E)`
   - Union-Find operations: nearly `O(E)`.
   - Overall complexity: `O(E log E)`.

6. **Use Case**:
   - The program is suitable for calculating the MST of a graph with weighted edges, such as road networks or communication links.
*/
