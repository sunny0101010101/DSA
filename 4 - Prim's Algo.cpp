#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// A structure to represent a node in the priority queue
struct Node {
    int vertex, weight; // Vertex number and the weight of the edge
    Node(int v, int w) : vertex(v), weight(w) {}
    // Overloading the > operator to implement a min-heap for the priority queue
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

// Function to find the Minimum Spanning Tree (MST) using Prim's algorithm
int primMST(int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> key(V, INT_MAX);  // Store minimum edge weight for each vertex
    vector<bool> inMST(V, false); // Track if a vertex is included in MST
    vector<int> parent(V, -1);    // Store parent of each vertex in the MST
    priority_queue<Node, vector<Node>, greater<Node>> pq; // Min-heap priority queue for selecting minimum weight edges

    key[0] = 0;  // Start with vertex 0, assigning it a key value of 0
    pq.push(Node(0, 0)); // Push the starting vertex into the priority queue

    int mstWeight = 0;  // Variable to store the total weight of the MST

    // Loop until all vertices are included in the MST
    while (!pq.empty()) {
        int u = pq.top().vertex; // Extract the vertex with the smallest key value
        pq.pop();

        if (inMST[u]) continue; // Skip if the vertex is already included in the MST
        inMST[u] = true;        // Mark the vertex as included
        mstWeight += key[u];    // Add its key value to the MST weight

        // Traverse all adjacent vertices of u
        for (auto& [v, weight] : adj[u]) {
            // If v is not yet included in MST and weight of edge (u, v) is smaller than current key[v]
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;       // Update the key value for vertex v
                pq.push(Node(v, key[v])); // Push the updated vertex into the priority queue
                parent[v] = u;         // Update the parent of v
            }
        }
    }

    // Output the edges in the MST
    cout << "Prim's MST edges:" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << endl; // Output each edge in the MST
    }

    return mstWeight; // Return the total weight of the MST
}

int main() {
    int V, E; // V: Number of vertices, E: Number of edges
    cin >> V >> E;  // Input the number of vertices and edges
    vector<vector<pair<int, int>>> adj(V);  // Adjacency list representation of the graph

    // Input the edges
    for (int i = 0; i < E; ++i) {
        int u, v, w;  // u and v are the endpoints, w is the weight of the edge
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w); // Add edge (u, v) with weight w
        adj[v].emplace_back(u, w); // Since the graph is undirected, add (v, u) as well
    }

    // Compute and output the total weight of Prim's MST
    cout << "Total weight of Prim's MST: " << primMST(V, adj) << endl;

    return 0;
}

/*
**Explanation of the Code**:
1. **Node Structure**:
   - Represents a node in the priority queue with vertex and weight.
   - Overloads the `>` operator to create a min-heap priority queue.

2. **Adjacency List**:
   - The graph is represented using an adjacency list where each vertex points to its adjacent vertices and their edge weights.

3. **Prim's Algorithm**:
   - Maintains a `key` array for minimum weights and an `inMST` array to track inclusion of vertices in the MST.
   - Uses a min-heap (`priority_queue`) to extract the vertex with the smallest key value.

4. **Output**:
   - Outputs the edges of the MST in the format `parent[i] - i` for vertices `1` to `V-1`.

5. **Time Complexity**:
   - Using a min-heap, the complexity is `O((V + E) log V)`, where `V` is the number of vertices and `E` is the number of edges.

6. **Use Case**:
   - Suitable for finding MST in connected, weighted, undirected graphs.
   - Examples: Network design, road systems, and minimizing cost connections.
*/
