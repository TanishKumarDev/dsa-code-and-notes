#include <bits/stdc++.h>
using namespace std;

// BST Node definition
struct TreeNode
{
    int val;         // Value stored
    TreeNode *left;  // Left child
    TreeNode *right; // Right child

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
    TreeNode *searchBST(TreeNode *root, int key)
    {

        // Start from root and move down
        while (root != nullptr)
        {

            // If key matches current node
            if (root->val == key)
            {
                return root;
            }

            // If key is smaller, go left
            if (key < root->val)
            {
                root = root->left;
            }
            // If key is larger, go right
            else
            {
                root = root->right;
            }
        }

        // Key not found
        return nullptr;
    }
};

int main()
{

    /*
            BST:
                4
              /   \
             2     7
            / \
           1   3
    */

    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    TreeNode *result = sol.searchBST(root, 3);

    if (result)
        cout << "Node found: " << result->val << endl;
    else
        cout << "Node not found" << endl;

    return 0;
}
