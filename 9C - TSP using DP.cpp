#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int tspHelper(int mask, int pos, vector<vector<int>>& dist, vector<vector<int>>& dp, int n) {
    // If all cities have been visited, return the cost to return to the starting city
    if (mask == (1 << n) - 1) {
        return dist[pos][0];  // Return to the start city
    }
    
    // Check if this subproblem has already been solved
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }
    
    int ans = INT_MAX;  // Initialize the answer to a very large value
    
    // Try all possible next cities
    for (int city = 0; city < n; ++city) {
        if ((mask & (1 << city)) == 0 && dist[pos][city] != -1) {  // If the city has not been visited
            int newAns = dist[pos][city] + tspHelper(mask | (1 << city), city, dist, dp, n);
            ans = min(ans, newAns);  // Minimize the cost
        }
    }
    
    return dp[mask][pos] = ans;  // Store the result and return it
}

int solveTSP(vector<vector<int>>& dist, int n) {
    // Create a DP table to store the minimum cost for each subset of cities
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    
    // Start the TSP from the first city (0th city)
    return tspHelper(1, 0, dist, dp, n);
}

int main() {
    int n;  // Number of cities
    cout << "Enter the number of cities: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));  // Distance matrix

    // Input the distance matrix
    cout << "Enter the distance matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
        }
    }
    
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display the Distance Matrix\n";
        cout << "2. Calculate Minimum Cost of TSP\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nDistance Matrix:\n";
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        cout << dist[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            case 2:
                {
                    int minCost = solveTSP(dist, n);
                    cout << "The minimum cost of the TSP cycle is: " << minCost << endl;
                }
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 3);
    
    return 0;
}
