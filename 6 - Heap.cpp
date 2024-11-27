#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to heapify a subtree rooted at index i (for Min-Heap and Max-Heap)
void heapify(vector<int>& heap, int n, int i, bool isMaxHeap) {
    int largestOrSmallest = i; // Initialize the largest/smallest as root
    int left = 2 * i + 1;      // Left child
    int right = 2 * i + 2;     // Right child

    // Compare for Max-Heap or Min-Heap
    if (isMaxHeap) {
        // If left child is greater than the root
        if (left < n && heap[left] > heap[largestOrSmallest]) {
            largestOrSmallest = left;
        }
        // If right child is greater than the current largest
        if (right < n && heap[right] > heap[largestOrSmallest]) {
            largestOrSmallest = right;
        }
    } else {
        // If left child is smaller than the root
        if (left < n && heap[left] < heap[largestOrSmallest]) {
            largestOrSmallest = left;
        }
        // If right child is smaller than the current smallest
        if (right < n && heap[right] < heap[largestOrSmallest]) {
            largestOrSmallest = right;
        }
    }

    // If the largest/smallest is not root, swap and continue heapifying
    if (largestOrSmallest != i) {
        swap(heap[i], heap[largestOrSmallest]);
        // Recursively heapify the affected subtree
        heapify(heap, n, largestOrSmallest, isMaxHeap);
    }
}

// Function to build a heap from an array (Max-Heap or Min-Heap)
void buildHeap(vector<int>& heap, bool isMaxHeap) {
    int n = heap.size();
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(heap, n, i, isMaxHeap);
    }
}

// Function to extract the root element of the heap (for Max-Heap and Min-Heap)
int extractRoot(vector<int>& heap, bool isMaxHeap) {
    int root = heap[0]; // Store the root element
    int n = heap.size();
    heap[0] = heap[n - 1]; // Replace the root with the last element
    heap.pop_back();       // Remove the last element
    // Heapify the reduced heap to maintain heap property
    heapify(heap, n - 1, 0, isMaxHeap);
    return root;
}

// Menu-driven program to work with student marks using heaps
int main() {
    vector<int> marks;  // Vector to store student marks
    int choice, n, mark;

    do {
        // Display the menu
        cout << "\nMenu:\n";
        cout << "1. Enter student marks\n";
        cout << "2. Find maximum mark using Max-Heap\n";
        cout << "3. Find minimum mark using Min-Heap\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Option to input marks of students
                cout << "Enter number of students: ";
                cin >> n;
                marks.clear(); // Clear previous data
                cout << "Enter the marks of " << n << " students:\n";
                for (int i = 0; i < n; ++i) {
                    cout << "Student " << i + 1 << " mark: ";
                    cin >> mark;
                    marks.push_back(mark); // Store marks in vector
                }
                break;
            }
            case 2: {
                // Option to find maximum mark using Max-Heap
                if (marks.empty()) {
                    // If no marks are entered
                    cout << "No marks entered yet. Please input marks first.\n";
                    break;
                }

                vector<int> maxHeap = marks; // Copy marks for heap processing
                buildHeap(maxHeap, true);    // Build Max-Heap
                int maxMark = extractRoot(maxHeap, true); // Extract max
                cout << "Maximum mark obtained: " << maxMark << endl;
                break;
            }
            case 3: {
                // Option to find minimum mark using Min-Heap
                if (marks.empty()) {
                    // If no marks are entered
                    cout << "No marks entered yet. Please input marks first.\n";
                    break;
                }

                vector<int> minHeap = marks; // Copy marks for heap processing
                buildHeap(minHeap, false);   // Build Min-Heap
                int minMark = extractRoot(minHeap, false); // Extract min
                cout << "Minimum mark obtained: " << minMark << endl;
                break;
            }
            case 4:
                // Exit the program
                cout << "Exiting program...\n";
                break;
            default:
                // Handle invalid input
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4); // Continue until the user chooses to exit

    return 0;
}
