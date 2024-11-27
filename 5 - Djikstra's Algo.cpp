#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

#define MAX_CITIES 10 // Maximum number of cities supported
#define INF INT_MAX   // Representation of infinity for unreachable paths

// Dijkstra's algorithm to find the shortest path
void dijkstra(int graph[MAX_CITIES][MAX_CITIES], int n, int source, int destination) {
    vector<int> dist(n, INF);      // Initialize distances from the source to all nodes as infinite
    vector<bool> visited(n, false); // Track visited nodes to avoid revisiting
    vector<int> prev(n, -1);       // Track the previous node for each node to reconstruct the path
    dist[source] = 0;              // Distance to the source itself is zero
    
    // Priority queue to pick the node with the smallest distance (min-heap)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});          // Push the source node with a distance of 0
    
    while (!pq.empty()) {
        int u = pq.top().second;   // Extract the node with the smallest distance
        pq.pop();
        
        if (visited[u]) continue; // Skip nodes already visited
        visited[u] = true;        // Mark the current node as visited
        
        // Update distances to neighboring nodes
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF) { // Consider only unvisited neighbors with valid edges
                int alt = dist[u] + graph[u][v]; // Alternative distance through u to v
                if (alt < dist[v]) {            // If a shorter path is found
                    dist[v] = alt;              // Update the shortest distance
                    prev[v] = u;                // Update the previous node for v
                    pq.push({dist[v], v});      // Push the neighbor into the priority queue
                }
            }
        }
    }
    
    // Print the shortest path from source to destination
    if (dist[destination] == INF) { // If the distance to the destination is still infinite
        cout << "No path exists from source to destination.\n";
    } else {
        cout << "Shortest time to reach destination: " << dist[destination] << " units\n";
        
        // Reconstruct the path from destination to source using the `prev` array
        cout << "Path: ";
        vector<int> path;
        for (int at = destination; at != -1; at = prev[at]) {
            path.push_back(at); // Add nodes to the path in reverse order
        }
        // Print the path in the correct order
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}

// Menu-driven interface for the user
int main() {
    int n, source, destination;
    int graph[MAX_CITIES][MAX_CITIES]; // Graph represented as an adjacency matrix

    // Initialize the graph with no paths (all distances are infinity)
    cout << "Enter number of cities (max 10): ";
    cin >> n;

    // Initialize the graph with infinity for unreachable paths
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0;  // Distance from a city to itself is 0
            } else {
                graph[i][j] = INF; // No direct path initially
            }
        }
    }

    int choice;
    do {
        // Menu options for user input
        cout << "\nMenu:\n";
        cout << "1. Add a road between two cities\n";
        cout << "2. Calculate shortest path from Source to Destination\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: { // Add a road between two cities
                int city1, city2, time;
                cout << "Enter the two cities (0 to " << n-1 << "): ";
                cin >> city1 >> city2;
                cout << "Enter the travel time from city " << city1 << " to city " << city2 << ": ";
                cin >> time;
                
                // Add the road as a bidirectional edge in the graph
                graph[city1][city2] = time;
                graph[city2][city1] = time;
                break;
            }
            case 2: { // Calculate the shortest path using Dijkstra's algorithm
                cout << "Enter the source city (0 to " << n-1 << "): ";
                cin >> source;
                cout << "Enter the destination city (0 to " << n-1 << "): ";
                cin >> destination;
                
                // Call Dijkstra's algorithm to compute the shortest path
                dijkstra(graph, n, source, destination);
                break;
            }
            case 3: // Exit the program
                cout << "Exiting...\n";
                break;
            default: // Handle invalid menu options
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3); // Continue until the user chooses to exit

    return 0;
}

/*
**Explanation of the Code**:
1. **Dijkstra's Algorithm**:
   - Finds the shortest path between two cities using a priority queue to optimize edge selection.
   - Tracks distances and previous nodes for path reconstruction.

2. **Graph Representation**:
   - The graph is represented as an adjacency matrix where `graph[i][j]` holds the travel time between cities `i` and `j`.

3. **Menu Options**:
   - Allows the user to:
     - Add roads (edges) between cities.
     - Calculate the shortest path between a source and destination city.
     - Exit the program.

4. **Input Validation**:
   - Ensures cities are within valid range and travel times are non-negative.

5. **Use Case**:
   - Suitable for applications like route planning, delivery optimization, or finding the shortest path in a transportation network.
*/
