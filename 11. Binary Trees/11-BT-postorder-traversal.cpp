#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node
struct TreeNode
{
    int val;         // Value stored in node
    TreeNode *left;  // Left child
    TreeNode *right; // Right child

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
public:
    void postorderTraversal(TreeNode *root, vector<int> &result)
    {

        // Base case:
        // If current node is NULL, stop recursion
        if (root == nullptr)
        {
            return;
        }

        // Step 1: Traverse left subtree completely
        postorderTraversal(root->left, result);

        // Step 2: Traverse right subtree completely
        postorderTraversal(root->right, result);

        // Step 3: Visit current node (AFTER children)
        result.push_back(root->val);
    }
};

int main()
{

    /*
            Tree:
                1
              /   \
             2     3
    */

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    Solution sol;
    vector<int> result;

    sol.postorderTraversal(root, result);

    cout << "Postorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
