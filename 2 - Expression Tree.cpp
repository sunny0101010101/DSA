#include <iostream>
#include <cctype>  // For isalnum
#include <stack>
#include <string>

using namespace std;

// Node structure for the expression tree
struct Node {
    char data;         // Data stored in the node
    Node* left;        // Pointer to the left child
    Node* right;       // Pointer to the right child
    Node(char val) : data(val), left(nullptr), right(nullptr) {} // Constructor
};

// Construct an expression tree from a prefix expression
Node* constructFromPrefix(const string& expr) {
    stack<Node*> st;  // Stack to hold nodes during construction
    // Traverse the prefix expression from right to left
    for (int i = expr.length() - 1; i >= 0; --i) {
        if (isalnum(expr[i])) {  // If operand, create a node and push to the stack
            st.push(new Node(expr[i]));
        } else {  // If operator, create a node and attach two top elements as children
            Node* node = new Node(expr[i]);
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
            st.push(node);  // Push the newly formed subtree back to the stack
        }
    }
    return st.top();  // Return the root of the expression tree
}

// Construct an expression tree from a postfix expression
Node* constructFromPostfix(const string& expr) {
    stack<Node*> st;  // Stack to hold nodes during construction
    // Traverse the postfix expression from left to right
    for (char ch : expr) {
        if (isalnum(ch)) {  // If operand, create a node and push to the stack
            st.push(new Node(ch));
        } else {  // If operator, create a node and attach top two elements as children
            Node* node = new Node(ch);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);  // Push the newly formed subtree back to the stack
        }
    }
    return st.top();  // Return the root of the expression tree
}

// In-order traversal using a stack (iterative method)
void inOrderTraversal(Node* root) {
    stack<Node*> st;
    Node* current = root;
    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {  // Reach the leftmost node
            st.push(current);
            current = current->left;
        }
        current = st.top(); st.pop();  // Visit the node
        cout << current->data << " ";
        current = current->right;  // Move to the right subtree
    }
}

// Pre-order traversal using a stack (iterative method)
void preOrderTraversal(Node* root) {
    if (root == nullptr) return;  // Base case
    stack<Node*> st;
    st.push(root);  // Start with the root node
    while (!st.empty()) {
        Node* current = st.top(); st.pop();  // Visit the node
        cout << current->data << " ";
        // Push right child first so that left child is processed first
        if (current->right) st.push(current->right);
        if (current->left) st.push(current->left);
    }
}

// Post-order traversal using two stacks (iterative method)
void postOrderTraversal(Node* root) {
    if (root == nullptr) return;  // Base case
    stack<Node*> st1, st2;
    st1.push(root);  // Start with the root node
    while (!st1.empty()) {
        Node* current = st1.top(); st1.pop();
        st2.push(current);  // Push the node to the second stack
        // Push left and right children to the first stack
        if (current->left) st1.push(current->left);
        if (current->right) st1.push(current->right);
    }
    // Print nodes from the second stack (post-order sequence)
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Helper function to determine operator precedence
int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    return 0;
}

// Convert an infix expression to a postfix expression
string infixToPostfix(const string& expr) {
    stack<char> st;       // Stack to hold operators
    string postfix;       // Resultant postfix expression
    bool expectOperand = true;  // Flag to handle unary operators

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        if (isalnum(ch)) {  // If operand, add to postfix expression
            postfix += ch;
            expectOperand = false;  // Operand found
        } else if (ch == '(') {  // If '(', push to the stack
            st.push(ch);
            expectOperand = true;
        } else if (ch == ')') {  // If ')', pop until '(' is found
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();  // Remove '('
            expectOperand = false;
        } else {  // Operator encountered
            if (ch == '-' && expectOperand) {
                postfix += '0';  // Handle unary minus by adding '0'
            }
            // Pop operators with higher or equal precedence
            while (!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);  // Push current operator
            expectOperand = true;  // After operator, expect an operand
        }
    }

    // Pop remaining operators from the stack
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;  // Return the postfix expression
}

// Main function
int main() {
    string expression;  // Input expression
    char choice;        // Type of expression (prefix, infix, postfix)
    int trav;           // Choice for traversal

    cout << "Enter the expression: ";
    cin >> expression;

    cout << "Is the expression prefix (p), infix (i), or postfix (o)? ";
    cin >> choice;

    Node* root = nullptr;

    // Construct the tree based on the type of expression
    if (choice == 'p') {
        root = constructFromPrefix(expression);
    } else if (choice == 'o') {
        root = constructFromPostfix(expression);
    } else if (choice == 'i') {
        string postfix = infixToPostfix(expression);  // Convert infix to postfix
        root = constructFromPostfix(postfix);        // Build tree from postfix
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    // Menu for tree traversal
    while (true) {
        cout << "\nChoose from the following options:\n";
        cout << "1. In-order traversal\n";
        cout << "2. Pre-order traversal\n";
        cout << "3. Post-order traversal\n";
        cout << "4. Exit\n";
        cin >> trav;

        switch (trav) {
            case 1:
                cout << "In-order traversal: ";
                inOrderTraversal(root);
                break;
            case 2:
                cout << "Pre-order traversal: ";
                preOrderTraversal(root);
                break;
            case 3:
                cout << "Post-order traversal: ";
                postOrderTraversal(root);
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please select a valid option." << endl;
                break;
        }
    }
    return 0;
}
