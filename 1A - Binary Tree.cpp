#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

// Class definition for a tree node
class node {
public:
    int data;        // Data contained in the node
    node* left;      // Pointer to the left child
    node* right;     // Pointer to the right child

    // Constructor to initialize a node with data
    node(int val) {
        this->data = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Function to build a binary tree recursively
node* buildTree() {
    cout << "Enter the data (-1 to stop): ";
    int data;
    cin >> data;

    // Base case: If data is -1, return nullptr to stop tree construction
    if (data == -1) {
        return nullptr;
    }

    // Create a new node with the entered data
    node* root = new node(data);

    // Recursively build the left subtree
    cout << "Enter data for inserting in left of " << data << endl;
    root->left = buildTree();

    // Recursively build the right subtree
    cout << "Enter data for inserting in right of " << data << endl;
    root->right = buildTree();

    return root; // Return the root of the subtree
}

// Function to perform level order traversal (breadth-first traversal)
void levelOrderTraversal(node* root) {
    if (root == nullptr) {
        return; // If the tree is empty, return
    }

    queue<node*> q; // Queue to facilitate level order traversal
    q.push(root);   // Start with the root node
    q.push(nullptr); // Marker for end of level

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp == nullptr) { // If a level ends
            cout << endl;
            if (!q.empty()) { // Add marker for the next level
                q.push(nullptr);
            }
        } else {
            cout << temp->data << " "; // Print the current node's data
            // Enqueue the left child
            if (temp->left) {
                q.push(temp->left);
            }
            // Enqueue the right child
            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

// Function to perform in-order traversal (left, root, right)
void inorder(node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left); // Traverse the left subtree
    cout << root->data << " "; // Print the current node's data
    inorder(root->right); // Traverse the right subtree
}

// Function to display all the leaf nodes of the tree
void displayLeaves(node* root) {
    if (root == nullptr) {
        return;
    }

    // If the current node is a leaf node, print its data
    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << " ";
    }

    // Recursively check for leaf nodes in left and right subtrees
    displayLeaves(root->left);
    displayLeaves(root->right);
}

// Function to create a copy of a binary tree
node* copyTree(node* root) {
    if (root == nullptr) {
        return nullptr; // If the tree is empty, return nullptr
    }

    // Create a new node with the same data as the current node
    node* newRoot = new node(root->data);
    // Recursively copy the left and right subtrees
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot; // Return the root of the copied tree
}

// Function to calculate the depth (height) of the binary tree
int depth(node* root) {
    if (root == nullptr) {
        return 0; // Base case: If the tree is empty, depth is 0
    }

    // Calculate the depth of the left and right subtrees
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);

    // Return the maximum of the two depths plus 1
    return max(leftDepth, rightDepth) + 1;
}

// Main function to drive the program
int main() {
    node* root = nullptr; // Initialize the root of the tree to nullptr
    char choice; // Variable to store user's menu choice

    do {
        // Display the menu
        cout << "\nMenu:\n";
        cout << "a. Insert a new node\n";
        cout << "b. Display level order traversal\n";
        cout << "c. Find depth of the tree\n";
        cout << "d. Display leaf nodes\n";
        cout << "e. Create a copy of the tree\n";
        cout << "f. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'a': {
                // Create the binary tree
                cout << "Creating Binary Tree:\n";
                root = buildTree();
                break;
            }
            case 'b': {
                // Display the tree in level order
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Level Order Traversal:\n";
                    levelOrderTraversal(root);
                }
                break;
            }
            case 'c': {
                // Find and display the depth of the tree
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Depth of the Tree: " << depth(root) << endl;
                }
                break;
            }
            case 'd': {
                // Display all the leaf nodes of the tree
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Leaf Nodes: ";
                    displayLeaves(root);
                    cout << endl;
                }
                break;
            }
            case 'e': {
                // Create and display a copy of the tree
                if (root == nullptr) {
                    cout << "Tree is empty. Please create a tree first.\n";
                } else {
                    cout << "Copying Tree:\n";
                    node* copiedTree = copyTree(root);
                    cout << "Level Order Traversal of Copied Tree:\n";
                    levelOrderTraversal(copiedTree);
                }
                break;
            }
            case 'f': {
                // Exit the program
                cout << "Exiting...\n";
                break;
            }
            default: {
                // Handle invalid input
                cout << "Invalid choice. Please enter again.\n";
                break;
            }
        }
    } while (choice != 'f'); // Repeat until user chooses to exit

    return 0;
}
