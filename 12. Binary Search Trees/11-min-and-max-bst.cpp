#include <bits/stdc++.h>
using namespace std;

// BST Node
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data)
    {
        val = data;
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
public:
    // Find minimum value node
    TreeNode *findMin(TreeNode *root)
    {

        // Edge case: empty tree
        if (root == nullptr)
            return nullptr;

        // Move to leftmost node
        while (root->left != nullptr)
        {
            root = root->left;
        }

        return root;
    }

    // Find maximum value node
    TreeNode *findMax(TreeNode *root)
    {

        // Edge case: empty tree
        if (root == nullptr)
            return nullptr;

        // Move to rightmost node
        while (root->right != nullptr)
        {
            root = root->right;
        }

        return root;
    }
};

int main()
{

    /*
            8
          /   \
         5     12
        / \    / \
       2   7  10  14
    */

    TreeNode *root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(14);

    Solution sol;

    TreeNode *minNode = sol.findMin(root);
    TreeNode *maxNode = sol.findMax(root);

    cout << "Minimum value: " << minNode->val << endl;
    cout << "Maximum value: " << maxNode->val << endl;

    return 0;
}
