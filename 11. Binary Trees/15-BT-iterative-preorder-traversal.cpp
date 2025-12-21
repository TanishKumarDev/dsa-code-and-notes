#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode
{
    int val;         // Value of node
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
    vector<int> preorderTraversal(TreeNode *root)
    {

        vector<int> preorder;

        // Edge case: empty tree
        if (root == nullptr)
        {
            return preorder;
        }

        // Stack to simulate recursion
        stack<TreeNode *> st;
        st.push(root);

        // Iterate until stack becomes empty
        while (!st.empty())
        {

            // Step 1: Get top node
            TreeNode *node = st.top();
            st.pop();

            // Step 2: Visit node
            preorder.push_back(node->val);

            // Step 3: Push right child first
            if (node->right != nullptr)
            {
                st.push(node->right);
            }

            // Step 4: Push left child
            if (node->left != nullptr)
            {
                st.push(node->left);
            }
        }

        return preorder;
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
    vector<int> result = sol.preorderTraversal(root);

    cout << "Iterative Preorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
