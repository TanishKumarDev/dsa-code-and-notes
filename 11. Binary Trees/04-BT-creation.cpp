#include <bits/stdc++.h>
using namespace std;

// Class representing a Node in the Binary Tree
class Node
{
public:
    int data;    // Stores the value of the node
    Node *left;  // Pointer to the left child node
    Node *right; // Pointer to the right child node

    // Constructor to initialize a node
    Node(int key)
    {
        data = key;      // Assign value to node
        left = nullptr;  // No left child initially
        right = nullptr; // No right child initially
    }
};
// Class containing the logic for Binary Tree creation
class Solution
{
public:
    Node *createBinaryTree()
    {

        // Step 1: Create root node
        Node *root = new Node(1);

        // Step 2: Create left child of root
        root->left = new Node(2);

        // Step 3: Create right child of root
        root->right = new Node(3);

        // Step 4: Create left child of node 3
        root->right->left = new Node(5);

        // Return root (entry point of tree)
        return root;
    }
};

int main()
{
    Solution solution;

    // Root stores the entry point of the tree
    Node *root = solution.createBinaryTree();

    // Print the tree
    cout << "Binary Tree created:" << endl;
    cout << "Root: " << root->data << endl;
    cout << "Left child of root: " << root->left->data << endl;
    cout << "Right child of root: " << root->right->data << endl;
    
    // Tree is now created in memory
    return 0;
}
// TC = O(n)   where n = number of nodes created
// SC = O(n)

// Heap Space,
// One node object per tree node

// Stack Space
// No recursion used
// Only a few pointers
// Stack SC = O(1)
