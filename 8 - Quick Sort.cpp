#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to represent a student
struct Student
{
    string name;
    int credits;
};

// Function to perform quick sort on the array of students based on credits
int partition(vector<Student> &students, int low, int high)
{
    int pivot = students[high].credits; // Taking the last element as pivot
    int i = low - 1;                    // Index of smaller element

    // Rearranging the students based on their credits
    for (int j = low; j < high; j++)
    {
        if (students[j].credits >= pivot)
        { // For descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]); // Move pivot to the correct position
    return (i + 1);
}

void quickSort(vector<Student> &students, int low, int high)
{
    if (low < high)
    {
        int pi = partition(students, low, high); // Partition index
        quickSort(students, low, pi - 1);        // Sorting left part
        quickSort(students, pi + 1, high);       // Sorting right part
    }
}

int main()
{
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<Student> students(n); // Vector to store students

    // Input student names and credits
    cout << "Enter the details of students (Name, Credits):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Student " << i + 1 << " (Name Credits): ";
        cin >> students[i].name >> students[i].credits;
    }

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Display All Students\n";
        cout << "2. Display Top 3 Students\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nAll Students:\n";
            for (const auto &student : students)
            {
                cout << "Name: " << student.name << ", Credits: " << student.credits << endl;
            }
            break;
        case 2:
            quickSort(students, 0, n - 1); // Sorting students by credits
            cout << "\nTop 3 Students by Credits:\n";
            for (int i = 0; i < 3 && i < n; ++i)
            {
                cout << "Name: " << students[i].name << ", Credits: " << students[i].credits << endl;
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

/*
Quick Sort Explanation:

- **Quick Sort** is a **divide and conquer** sorting algorithm that works by selecting a "pivot" element from the array and partitioning the other elements into two sub-arrays, according to whether they are smaller or greater than the pivot. The sub-arrays are then sorted recursively.

- **Partition**: The array is rearranged so that elements smaller than the pivot are placed on the left side, and elements larger than the pivot are placed on the right side. The pivot is then placed in its correct position.

- **Recursion**: The process is recursively applied to the left and right sub-arrays until the entire array is sorted.

Time Complexity of Quick Sort:
- **Best and Average Case**: The time complexity of quick sort in the best and average cases is **O(N log N)**, where N is the number of elements. This is because the partitioning process divides the array into two nearly equal halves, and each level of recursion takes linear time to process.
  
- **Worst Case**: The worst-case time complexity of quick sort is **O(N^2)**, which happens when the pivot is always the smallest or largest element (i.e., when the array is already sorted or nearly sorted). This leads to unbalanced partitioning, resulting in recursion depths proportional to N.

- **Space Complexity**: Quick Sort has a space complexity of **O(log N)**, as the recursion stack stores intermediate results. In the worst case, the space complexity can be **O(N)**.

Advantages of Quick Sort:
- Quick Sort is typically faster in practice than other O(N log N) algorithms, such as Merge Sort, due to its smaller constant factors.
- It sorts in place, requiring only a small amount of additional memory.

Disadvantages of Quick Sort:
- Quick Sort's worst-case time complexity is **O(N^2)**, which can be avoided by choosing a good pivot.
- It is not stable (i.e., equal elements may not maintain their original relative order).

Overall, Quick Sort is efficient and widely used for large datasets when the average case performance is considered.
*/
