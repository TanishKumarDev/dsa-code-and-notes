#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode
{
    int data;        // Value of node
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
public:
    vector<int> inorder(TreeNode *root)
    {

        vector<int> inorder;   // Result
        stack<TreeNode *> st;  // Stack for simulation
        TreeNode *node = root; // Current pointer

        // Continue until all nodes processed
        while (!st.empty() || node != nullptr)
        {

            // Step 1: Go left as much as possible
            if (node != nullptr)
            {
                st.push(node);
                node = node->left;
            }
            else
            {
                // Step 2: Backtrack
                node = st.top();
                st.pop();

                // Step 3: Visit node
                inorder.push_back(node->data);

                // Step 4: Move to right subtree
                node = node->right;
            }
        }

        return inorder;
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
