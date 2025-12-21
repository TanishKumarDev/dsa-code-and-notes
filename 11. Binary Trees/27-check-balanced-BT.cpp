#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

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
    bool isBalanced(Node *root)
    {
        return dfsHeight(root) != -1;
    }

    int dfsHeight(Node *root)
    {

        // Base case
        if (root == nullptr)
            return 0;

        // Check left subtree
        int leftHeight = dfsHeight(root->left);
        if (leftHeight == -1)
            return -1;

        // Check right subtree
        int rightHeight = dfsHeight(root->right);
        if (rightHeight == -1)
            return -1;

        // Check balance condition
        if (abs(leftHeight - rightHeight) > 1)
            return -1;

        // Return height
        return 1 + max(leftHeight, rightHeight);
    }
};

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->left->right = new Node(3);
    root->left->right->right = new Node(4);

    Solution sol;

    cout << (sol.isBalanced(root) ? "Balanced" : "Not Balanced");
    return 0;
}
