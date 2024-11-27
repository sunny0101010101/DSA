#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an item in the knapsack problem
struct Item {
    int weight;   // Weight of the item
    int value;    // Value of the item
    float ratio;  // Value-to-weight ratio of the item
};

// Function to compare two items based on their value-to-weight ratio
// Used for sorting items in descending order of the ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;  // Return true if a's ratio is greater than b's ratio
}

// Function to calculate the maximum value we can obtain from the knapsack
// using a fractional knapsack approach (greedy algorithm)
float fractionalKnapsack(int capacity, vector<Item>& items, int n) {
    // Calculate value-to-weight ratio for each item
    for (int i = 0; i < n; ++i) {
        items[i].ratio = (float)items[i].value / items[i].weight;  // Value-to-weight ratio
    }
    
    // Sort items in decreasing order based on the ratio
    sort(items.begin(), items.end(), compare);  // Sorting items by ratio
    
    float totalValue = 0.0;  // Variable to store the total value accumulated in the knapsack
    int currentWeight = 0;   // Variable to track the current weight of the knapsack
    
    // Greedily pick items or fractions of items
    for (int i = 0; i < n; ++i) {
        // If the current item can be fully taken in the knapsack
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;  // Add the item weight to the knapsack
            totalValue += items[i].value;     // Add the item value to the total value
        } else {
            // Take the fraction of the item that fits in the remaining capacity
            int remainingWeight = capacity - currentWeight;  // Remaining capacity in the knapsack
            totalValue += items[i].value * ((float)remainingWeight / items[i].weight);  // Add the fractional value
            break;  // Since the knapsack is full, no more items can be added
        }
    }
    
    return totalValue;  // Return the total value of items in the knapsack
}

int main() {
    int n;  // Number of items
    cout << "Enter the number of items: ";
    cin >> n;  // Input the number of items

    vector<Item> items(n);  // Vector to store the items' details

    // Input the details of each item (weight and value)
    cout << "Enter the details of each item (weight and value):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << " (Weight Value): ";
        cin >> items[i].weight >> items[i].value;  // Input the weight and value of each item
    }

    int capacity;  // Knapsack capacity
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;  // Input the capacity of the knapsack

    int choice;  // Menu choice for user interaction
    do {
        // Display the menu to the user
        cout << "\nMenu:\n";
        cout << "1. Display Items\n";  // Option to display item details
        cout << "2. Calculate Maximum Value in Fractional Knapsack\n";  // Option to calculate max value using knapsack
        cout << "3. Exit\n";  // Option to exit the program
        cout << "Enter your choice: ";
        cin >> choice;  // Get user's choice

        switch (choice) {
            case 1:  // If the user selects to display the items
                cout << "\nItems List:\n";
                cout << "Item   Weight   Value   Value-to-Weight Ratio\n";
                for (int i = 0; i < n; ++i) {
                    // Display each item’s weight, value, and value-to-weight ratio
                    cout << items[i].weight << "     " << items[i].value << "      " 
                         << (float)items[i].value / items[i].weight << endl;
                }
                break;
            case 2:  // If the user selects to calculate the maximum value
                {
                    // Call the fractional knapsack function to compute the max value
                    float maxValue = fractionalKnapsack(capacity, items, n);
                    cout << "The maximum value in the knapsack is: " << maxValue << endl;
                }
                break;
            case 3:  // If the user selects to exit
                cout << "Exiting...\n";
                break;
            default:  // Invalid choice
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 3);  // Keep the menu running until the user chooses to exit
    
    return 0;  // Return 0 to indicate the program executed successfully
}
