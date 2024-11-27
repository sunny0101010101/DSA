#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to represent a student
struct Student {
    string name;    // Name of the student
    int credits;    // Number of credits the student has earned
};

// Function to merge two halves of the array in sorted order
void merge(vector<Student>& students, int left, int mid, int right) {
    int n1 = mid - left + 1;    // Size of left subarray
    int n2 = right - mid;       // Size of right subarray

    // Temporary vectors to store left and right subarrays
    vector<Student> leftArray(n1), rightArray(n2);

    // Copy data to temporary subarrays
    for (int i = 0; i < n1; ++i)
        leftArray[i] = students[left + i];   // Copy left part
    for (int i = 0; i < n2; ++i)
        rightArray[i] = students[mid + 1 + i];   // Copy right part

    // Merge the temporary subarrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // Compare credits of students from left and right subarrays
        if (leftArray[i].credits >= rightArray[j].credits) {
            students[k] = leftArray[i];  // Take element from leftArray if its credits are greater or equal
            ++i;
        } else {
            students[k] = rightArray[j]; // Otherwise, take element from rightArray
            ++j;
        }
        ++k;  // Move to the next position in the merged array
    }

    // Copy remaining elements of leftArray if any
    while (i < n1) {
        students[k] = leftArray[i];  // Copy remaining elements of the left subarray
        ++i;
        ++k;
    }

    // Copy remaining elements of rightArray if any
    while (j < n2) {
        students[k] = rightArray[j]; // Copy remaining elements of the right subarray
        ++j;
        ++k;
    }
}

// Merge Sort function to sort students by credits
void mergeSort(vector<Student>& students, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Find the middle index

        // Recursively sort the first and second halves
        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);

        // Merge the sorted halves
        merge(students, left, mid, right);
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;  // Input the number of students

    vector<Student> students(n);  // Vector to store student details

    // Input student names and credits
    cout << "Enter the details of students (Name, Credits):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Student " << i + 1 << " (Name Credits): ";
        cin >> students[i].name >> students[i].credits;  // Input student name and credits
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display All Students\n";  // Option to display all students
        cout << "2. Sort Students by Credits and Display\n";  // Option to sort and display students by credits
        cout << "3. Exit\n";  // Exit option
        cout << "Enter your choice: ";
        cin >> choice;  // Input user's menu choice

        switch (choice) {
            case 1:
                // Display all students' details
                cout << "\nAll Students:\n";
                for (const auto& student : students) {
                    cout << "Name: " << student.name << ", Credits: " << student.credits << endl;
                }
                break;
            case 2:
                // Sort students by credits and display them
                mergeSort(students, 0, n - 1);  // Sorting students by credits using merge sort
                cout << "\nSorted Students by Credits:\n";
                for (const auto& student : students) {
                    cout << "Name: " << student.name << ", Credits: " << student.credits << endl;
                }
                break;
            case 3:
                cout << "Exiting...\n";  // Exit the program
                break;
            default:
                cout << "Invalid choice! Please try again.\n";  // Handle invalid menu choices
                break;
        }
    } while (choice != 3);  // Continue until the user chooses to exit

    return 0;  // Return 0 to indicate successful execution
}

/*
Merge Sort Explanation:

- Merge Sort is a **divide and conquer** sorting algorithm. It divides the input array into two halves, recursively sorts each half, and then merges the sorted halves back together in sorted order.

- **Divide**: The array is repeatedly split into two halves until each subarray has only one element, which is trivially sorted.

- **Conquer**: The merge function is used to combine two sorted subarrays into one sorted array. The merging process compares elements of both subarrays and arranges them in the correct order.

- **Combine**: Once all subarrays are merged, the result is a completely sorted array.

Time Complexity of Merge Sort:
- The time complexity of merge sort is **O(N log N)**, where N is the number of elements to be sorted.
- **Reason**: 
  - The array is divided into two halves at each step, which takes **log N** recursive calls (depth of recursion tree).
  - Each level of recursion involves merging, which takes **O(N)** time, as each element is compared and moved to its correct position during the merge.
  - Therefore, the overall time complexity is **O(N log N)**.

Space Complexity:
- Merge Sort has a space complexity of **O(N)** because it requires additional space to store the temporary subarrays during the merge step.

Advantages of Merge Sort:
- Merge Sort is stable, meaning that it preserves the relative order of elements with equal keys.
- It guarantees **O(N log N)** performance even in the worst case, unlike other algorithms like QuickSort, which may degrade to **O(N^2)** under certain conditions.

Disadvantages:
- Merge Sort requires extra space for the temporary subarrays, which can be inefficient if memory usage is a concern.
*/
