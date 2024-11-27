#include <iostream>
#include <queue>
using namespace std;

// Node class represents a single node in the binary search tree
class Node {
public:
    int data;       // Data stored in the node
    Node* left;     // Pointer to the left child
    Node* right;    // Pointer to the right child

    // Constructor to initialize the node with a value and set children to null
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Binary Search Tree (BST) class
class BST {
private:
    Node* root; // Pointer to the root of the BST

    // Recursive helper function to insert a node
    Node* insert(Node* node, int data) {
        if (node == nullptr) { // Base case: if node is null, create a new node
            return new Node(data);
        }
        // If data is smaller, insert into the left subtree
        if (data < node->data) {
            node->left = insert(node->left, data);
        }
        // If data is larger, insert into the right subtree
        else {
            node->right = insert(node->right, data);
        }
        return node;
    }

    // Helper function to find the node with the minimum value in a subtree
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left; // Traverse to the leftmost node
        }
        return node;
    }

    // Recursive helper function to delete a node
    Node* deleteNode(Node* node, int data) {
        if (node == nullptr) { // Base case: if node is null, return
            return node;
        }

        // Traverse the tree to find the node to be deleted
        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else {
            // Node with one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node; // Free memory
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node; // Free memory
                return temp;
            }

            // Node with two children: replace with inorder successor
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Recursive helper function for in-order traversal
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);         // Traverse left subtree
            cout << node->data << " ";  // Print current node
            inorder(node->right);       // Traverse right subtree
        }
    }

    // Recursive helper function to search for a value
    bool search(Node* node, int data) {
        if (node == nullptr) {
            return false; // Value not found
        }
        if (data == node->data) {
            return true; // Value found
        } else if (data < node->data) {
            return search(node->left, data); // Search in left subtree
        } else {
            return search(node->right, data); // Search in right subtree
        }
    }

    // Helper function for Breadth-First Search (BFS) traversal
    void bfs(Node* node) {
        if (node == nullptr) return;

        queue<Node*> q; // Queue for BFS
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            cout << current->data << " "; // Print current node
            q.pop();

            if (current->left != nullptr) {
                q.push(current->left); // Enqueue left child
            }
            if (current->right != nullptr) {
                q.push(current->right); // Enqueue right child
            }
        }
        cout << endl;
    }

public:
    // Constructor to initialize the BST with an empty root
    BST() {
        root = nullptr;
    }

    // Public method to insert a value
    void insert(int data) {
        root = insert(root, data);
    }

    // Public method to delete a value
    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    // Public method to display the tree using in-order traversal
    void display() {
        inorder(root);
        cout << endl;
    }

    // Public method to search for a value
    void search(int data) {
        if (search(root, data)) {
            cout << data << " found in the tree." << endl;
        } else {
            cout << data << " not found in the tree." << endl;
        }
    }

    // Public method to perform BFS (level-wise traversal)
    void bfs() {
        bfs(root);
    }
};

int main() {
    BST tree; // Create a BST object
    int choice, value;

    do {
        // Menu for user interaction
        cout << "\nBinary Search Tree Operations Menu:";
        cout << "\n1. Insert";
        cout << "\n2. Delete";
        cout << "\n3. Display (In-order)";
        cout << "\n4. Search";
        cout << "\n5. BFS (Level-wise display)";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value); // Insert value
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteNode(value); // Delete value
                break;
            case 3:
                cout << "In-order display: ";
                tree.display(); // Display tree in in-order
                break;
            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                tree.search(value); // Search for value
                break;
            case 5:
                cout << "BFS (Level-wise display): ";
                tree.bfs(); // Perform BFS traversal
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
