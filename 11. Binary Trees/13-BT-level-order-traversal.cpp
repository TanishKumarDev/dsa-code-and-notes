#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode
{
    int data;        // Value stored
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {

        vector<vector<int>> ans;

        // Edge case: empty tree
        if (root == nullptr)
        {
            return ans;
        }

        // Queue for BFS
        queue<TreeNode *> q;
        q.push(root);

        // BFS traversal
        while (!q.empty())
        {

            // Number of nodes at current level
            int size = q.size();
            vector<int> level;

            // Process one full level
            for (int i = 0; i < size; i++)
            {

                TreeNode *node = q.front();
                q.pop();

                // Store node value
                level.push_back(node->data);

                // Push children for next level
                if (node->left != nullptr)
                {
                    q.push(node->left);
                }
                if (node->right != nullptr)
                {
                    q.push(node->right);
                }
            }

            // Store current level
            ans.push_back(level);
        }

        return ans;
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
    vector<vector<int>> result = sol.levelOrder(root);

    for (auto level : result)
    {
        for (int val : level)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
