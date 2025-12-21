#include <bits/stdc++.h>
using namespace std;

// Node structure for Binary Tree
struct Node
{
    int data;    // Value of node
    Node *left;  // Pointer to left child
    Node *right; // Pointer to right child

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Solution class
class Solution
{
public:
    // Recursive preorder traversal
    void preorder(Node *root, vector<int> &arr)
    {

        // Base case:
        // If node is NULL, stop recursion
        if (root == nullptr)
        {
            return;
        }

        // Step 1: Visit root
        arr.push_back(root->data);

        // Step 2: Traverse left subtree
        preorder(root->left, arr);

        // Step 3: Traverse right subtree
        preorder(root->right, arr);
    }

    // Function called by user
    vector<int> preOrder(Node *root)
    {
        vector<int> arr;     // Stores traversal result
        preorder(root, arr); // Start recursion
        return arr;
    }
};

int main()
{

    /*
            Tree:
                1
              /   \
             2     3
            / \
           4   5
    */

    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    Solution sol;
    vector<int> result = sol.preOrder(root);

    cout << "Preorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
