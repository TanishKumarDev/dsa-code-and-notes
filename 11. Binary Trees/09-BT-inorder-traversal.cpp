#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode
{
    int data;        // Value stored in node
    TreeNode *left;  // Left child
    TreeNode *right; // Right child

    TreeNode(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
private:
    void recursiveInorder(TreeNode *root, vector<int> &arr)
    {

        // Base case: if node is NULL, stop
        if (root == nullptr)
        {
            return;
        }

        // Step 1: Traverse left subtree
        recursiveInorder(root->left, arr);

        // Step 2: Visit current node
        arr.push_back(root->data);

        // Step 3: Traverse right subtree
        recursiveInorder(root->right, arr);
    }

public:
    vector<int> inorder(TreeNode *root)
    {
        vector<int> arr; // Stores result
        recursiveInorder(root, arr);
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

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<int> result = sol.inorder(root);

    cout << "Inorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
