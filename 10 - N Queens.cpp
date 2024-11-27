#include <iostream>
#include <vector>
using namespace std;

class NQueens {
public:
    // Function to check if a queen can be placed at the board[i][col]
    bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
        // Check this column on the upper side (if there's any queen already in the same column)
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1) {
                return false; // A queen is already placed in the same column
            }
        }

        // Check upper diagonal on left side (if any queen exists on the upper-left diagonal)
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false; // A queen is already placed on the upper-left diagonal
            }
        }

        // Check upper diagonal on right side (if any queen exists on the upper-right diagonal)
        for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
            if (board[i][j] == 1) {
                return false; // A queen is already placed on the upper-right diagonal
            }
        }

        return true; // No clashes, safe to place the queen
    }

    // Function to solve the N-Queens problem using backtracking
    bool solveNQueens(vector<vector<int>>& board, int row, int N) {
        // If all queens are placed (i.e., row == N), we have found a solution
        if (row == N) {
            return true;
        }

        // Try placing the queen in all columns one by one for the current row
        for (int col = 0; col < N; col++) {
            // Check if it's safe to place a queen at (row, col)
            if (isSafe(board, row, col, N)) {
                // Place the queen
                board[row][col] = 1;

                // Recur to place the rest of the queens
                if (solveNQueens(board, row + 1, N)) {
                    return true; // If placing the queen results in a solution, return true
                }

                // If placing queen at (row, col) doesn't lead to a solution, backtrack
                board[row][col] = 0; // Unmark the cell (backtrack)
            }
        }

        return false; // No place found for this row, return false
    }

    // Function to print the solution (board)
    void printSolution(const vector<vector<int>>& board, int N) {
        // Print the board with queens represented by 'Q' and empty spaces by '.'
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] == 1 ? "Q " : ". "); // Print 'Q' if the cell contains a queen, else '.'
            }
            cout << endl; // Move to the next row
        }
    }

    // Function to initiate the N-Queens problem solution
    void solve(int N) {
        vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize the board with 0s (no queens placed)

        // Call the recursive backtracking function to solve the problem
        if (solveNQueens(board, 0, N)) {
            printSolution(board, N); // If a solution exists, print the board with queens
        } else {
            cout << "Solution does not exist." << endl; // If no solution exists
        }
    }
};

int main() {
    NQueens nq; // Create an object of the NQueens class
    int N, choice;

    while (true) {
        // Menu-driven interface for the user
        cout << "\n--- N-Queens Problem Menu ---\n";
        cout << "1. Solve N-Queens\n"; // Option to solve the N-Queens problem
        cout << "2. Exit\n"; // Option to exit the program
        cout << "Enter your choice: ";
        cin >> choice; // Get user choice

        switch (choice) {
            case 1:
                cout << "Enter the value of N (number of queens): ";
                cin >> N; // Get the size of the board (N)
                nq.solve(N); // Solve the N-Queens problem
                break;

            case 2:
                cout << "Exiting program...\n"; // Exit message
                return 0; // Exit the program

            default:
                cout << "Invalid choice. Please try again.\n"; // Invalid choice handling
        }
    }

    return 0; // Return 0 to indicate successful execution of the program
}
