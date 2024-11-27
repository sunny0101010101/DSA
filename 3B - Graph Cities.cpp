#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <limits>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, double>>> adjList; // adjacency list

    // Helper function for DFS traversal
    void DFS(const string& city, unordered_map<string, bool>& visited) {
        visited[city] = true; // Mark the current city as visited
        for (const auto& neighbor : adjList[city]) {
            if (!visited[neighbor.first]) {
                DFS(neighbor.first, visited); // Recursively visit neighbors
            }
        }
    }

public:
    // Function to add a flight (edge) between two cities (nodes)
    void addFlight(const string& cityA, const string& cityB, double cost) {
        adjList[cityA].push_back({cityB, cost}); // Add edge from cityA to cityB
        adjList[cityB].push_back({cityA, cost}); // Add edge from cityB to cityA (bidirectional)
    }

    // Function to check if the graph is connected
    bool isConnected() {
        if (adjList.empty()) return true; // An empty graph is considered connected

        unordered_map<string, bool> visited; // Track visited cities
        for (const auto& city : adjList) {
            visited[city.first] = false; // Initialize all cities as not visited
        }

        // Start DFS from the first city in the adjacency list
        auto startCity = adjList.begin()->first;
        DFS(startCity, visited);

        // Check if all cities have been visited
        for (const auto& city : visited) {
            if (!city.second) return false; // If any city is unvisited, graph is not connected
        }
        return true; // All cities are visited, graph is connected
    }

    // Function to display the adjacency list representation of the graph
    void displayGraph() {
        for (const auto& city : adjList) {
            cout << city.first << " -> "; // Print city name
            for (const auto& neighbor : city.second) {
                // Print each neighbor and the cost associated
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl; // New line for next city
        }
    }
};

int main() {
    Graph g; // Create a Graph object
    int choice; // Menu choice
    string cityA, cityB; // Cities for the flight
    double cost; // Cost of the flight

    do {
        // Display menu options
        cout << "\nMenu:\n";
        cout << "1. Add a flight between two cities\n";
        cout << "2. Display the graph\n";
        cout << "3. Check if the graph is connected\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Add a flight between two cities
                cout << "Enter the source city: ";
                cin >> cityA;
                cout << "Enter the destination city: ";
                cin >> cityB;
                cout << "Enter the cost (time or fuel): ";
                cin >> cost;
                g.addFlight(cityA, cityB, cost);
                break;
            case 2:
                // Display the adjacency list
                g.displayGraph();
                break;
            case 3:
                // Check if the graph is connected
                if (g.isConnected()) {
                    cout << "The graph is connected.\n";
                } else {
                    cout << "The graph is not connected.\n";
                }
                break;
            case 4:
                // Exit the program
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

/*
Justification for Adjacency List:
1. Space Efficiency: An adjacency list uses space proportional to the number of edges and vertices.
   - This is advantageous for sparse graphs where the number of edges is much smaller than the square of the number of vertices.

2. Ease of Iteration: The adjacency list allows efficient traversal of neighbors for a given node.
   - This feature is particularly useful for algorithms like DFS (used in the `isConnected` function).

3. Flexibility: The adjacency list can handle weighted graphs easily by storing weights (like flight cost) alongside neighbors.
   - This flexibility is demonstrated in the implementation with `pair<string, double>` for neighbors.
*/
