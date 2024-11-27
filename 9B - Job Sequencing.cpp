#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a job
struct Job {
    char id;    // Job identifier (e.g., 'A', 'B', 'C', ...)
    int deadline;  // Deadline by which the job should be completed
    int profit;    // Profit associated with the job
};

// Function to compare two jobs based on their profit (used for sorting jobs in descending order)
bool compareJobs(Job j1, Job j2) {
    // Sort jobs by profit in descending order (higher profit jobs should come first)
    return j1.profit > j2.profit;
}

// Function to schedule jobs to maximize profit
void jobScheduling(vector<Job>& jobs, int n) {
    // Sort jobs by profit in descending order
    sort(jobs.begin(), jobs.end(), compareJobs);

    // Vector to keep track of which slots are occupied (initialized to false)
    vector<bool> slots(n, false);
    // Vector to store the result jobs that will be scheduled
    vector<char> result(n, ' ');

    int totalProfit = 0;  // Variable to accumulate total profit

    // Iterate through the jobs and find an available slot for each job
    for (int i = 0; i < n; ++i) {
        // Find a slot for job[i] starting from its deadline (or before it)
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; --j) {
            if (!slots[j]) {  // If the slot is free
                // Assign this job to the slot
                slots[j] = true;
                result[j] = jobs[i].id;
                totalProfit += jobs[i].profit;  // Add the job's profit to total profit
                break;  // No need to check other slots once the job is assigned
            }
        }
    }

    // Output the selected jobs and their total profit
    cout << "Selected jobs: ";
    for (int i = 0; i < n; ++i) {
        if (result[i] != ' ') {  // If the slot is occupied
            cout << result[i] << " ";  // Print the job id
        }
    }
    cout << endl;
    cout << "Total profit: " << totalProfit << endl;  // Output the total profit
}

int main() {
    int n;  // Number of jobs
    cout << "Enter the number of jobs: ";
    cin >> n;  // Input the number of jobs

    vector<Job> jobs(n);  // Array to store the jobs

    // Input the details of each job (ID, Deadline, Profit)
    cout << "Enter the job details (ID, Deadline, Profit):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Job " << i + 1 << " (ID Deadline Profit): ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;  // Input each job's details
    }

    int choice;  // Menu choice for user interaction
    do {
        // Display the menu options to the user
        cout << "\nMenu:\n";
        cout << "1. Display Job Details\n";  // Option to display job details
        cout << "2. Calculate and Display Selected Jobs\n";  // Option to schedule jobs and display selected jobs
        cout << "3. Exit\n";  // Option to exit the program
        cout << "Enter your choice: ";
        cin >> choice;  // Get user's choice

        switch (choice) {
            case 1:  // If the user selects to display the job details
                cout << "\nJob Details:\n";
                cout << "ID Deadline Profit\n";
                // Display each job's ID, deadline, and profit
                for (int i = 0; i < n; ++i) {
                    cout << jobs[i].id << " " << jobs[i].deadline << " " << jobs[i].profit << endl;
                }
                break;
            case 2:  // If the user selects to calculate and display selected jobs
                jobScheduling(jobs, n);  // Call the job scheduling function
                break;
            case 3:  // If the user selects to exit
                cout << "Exiting...\n";
                break;
            default:  // If the user enters an invalid choice
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 3);  // Repeat until the user chooses to exit
    
    return 0;  // Return 0 to indicate the program executed successfully
}
