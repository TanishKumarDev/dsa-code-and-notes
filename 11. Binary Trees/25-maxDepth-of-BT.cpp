#include <bits/stdc++.h>
using namespace std;

// Node structure for the binary tree
struct Node
{
    int data;    // Value of node
    Node *left;  // Left child
    Node *right; // Right child

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
public:
    int maxDepth(Node *root)
    {

        // Base case:
        // If tree is empty, depth is 0
        if (root == nullptr)
        {
            return 0;
        }

        // Recursively find height of left subtree
        int leftHeight = maxDepth(root->left);

        // Recursively find height of right subtree
        int rightHeight = maxDepth(root->right);

        // Height of current node =
        // 1 (current node) + max of both subtrees
        return 1 + max(leftHeight, rightHeight);
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
                \
                 6
                  \
                   7
    */

    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);

    Solution sol;
    int depth = sol.maxDepth(root);

    cout << "Maximum depth of the binary tree: " << depth << endl;

    return 0;
}
