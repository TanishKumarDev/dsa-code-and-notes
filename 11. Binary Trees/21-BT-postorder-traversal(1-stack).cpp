#include <bits/stdc++.h>
using namespace std;

// Definition of TreeNode
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
        // If node is NULL, nothing to process
        if (root == nullptr)
        {
            return;
        }

        // Step 1: Traverse left subtree
        postorderTraversal(root->left, result);

        // Step 2: Traverse right subtree
        postorderTraversal(root->right, result);

        // Step 3: Process current node
        // This happens AFTER both children
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

    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
