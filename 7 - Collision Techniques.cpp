#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to heapify a subtree rooted at index i (for Min-Heap and Max-Heap)
void heapify(vector<int>& heap, int n, int i, bool isMaxHeap) {
    int largestOrSmallest = i; // Initialize the largest/smallest as root
    int left = 2 * i + 1;      // Left child index
    int right = 2 * i + 2;     // Right child index

    // Compare for Max-Heap or Min-Heap based on the flag isMaxHeap
    if (isMaxHeap) {
        // If left child is greater than the root, update largestOrSmallest
        if (left < n && heap[left] > heap[largestOrSmallest]) {
            largestOrSmallest = left;
        }
        // If right child is greater than the current largest element
        if (right < n && heap[right] > heap[largestOrSmallest]) {
            largestOrSmallest = right;
        }
    } else {
        // If left child is smaller than the root, update largestOrSmallest
        if (left < n && heap[left] < heap[largestOrSmallest]) {
            largestOrSmallest = left;
        }
        // If right child is smaller than the current smallest element
        if (right < n && heap[right] < heap[largestOrSmallest]) {
            largestOrSmallest = right;
        }
    }

    // If the largest/smallest is not root, swap and continue heapifying
    if (largestOrSmallest != i) {
        swap(heap[i], heap[largestOrSmallest]);  // Swap root with largest/smallest
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
    int root = heap[0]; // Store the root element (maximum or minimum)
    int n = heap.size();
    heap[0] = heap[n - 1]; // Replace the root with the last element
    heap.pop_back();       // Remove the last element
    // Heapify the reduced heap to maintain heap property
    heapify(heap, n - 1, 0, isMaxHeap);
    return root; // Return the extracted root
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
                int maxMark = extractRoot(maxHeap, true); // Extract max mark
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
                int minMark = extractRoot(minHeap, false); // Extract min mark
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

/*
Theory:

The program demonstrates the use of heaps, specifically Max-Heaps and Min-Heaps, for processing student marks. A heap is a special tree-based data structure that satisfies the heap property. There are two types of heaps:

1. Max-Heap:
   - In a Max-Heap, the key of each node is greater than or equal to the keys of its children, making the root node the largest element.
   - The program uses a Max-Heap to find the maximum mark of students. The root of the Max-Heap holds the maximum value.

2. Min-Heap:
   - In a Min-Heap, the key of each node is less than or equal to the keys of its children, making the root node the smallest element.
   - The program uses a Min-Heap to find the minimum mark of students. The root of the Min-Heap holds the minimum value.

Concepts used in the code:
1. **Heapify**: A function to maintain the heap property by comparing the current node with its children and swapping if necessary. It is called recursively to ensure the heap property is satisfied.
2. **Building the heap**: The function `buildHeap` transforms an unsorted array into a heap by calling `heapify` on each non-leaf node, starting from the last non-leaf node down to the root.
3. **Extracting the root**: The function `extractRoot` removes the root of the heap (the maximum or minimum element), replaces it with the last element in the heap, and then heapifies the heap to maintain the heap property.

This program helps in efficiently managing and retrieving the maximum and minimum student marks by using heap data structures. The time complexity of building a heap is O(n), and extracting the root element is O(log n), where n is the number of elements in the heap.
*/
