#include <bits/stdc++.h>
using namespace std;

// BST Node definition
struct TreeNode
{
    int val;         // Node value
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
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {

        // Case 1: Empty tree
        if (root == nullptr)
        {
            return new TreeNode(val);
        }

        TreeNode *current = root;

        // Traverse the tree
        while (true)
        {

            // Go left if value is smaller
            if (val < current->val)
            {

                if (current->left == nullptr)
                {
                    current->left = new TreeNode(val);
                    break;
                }
                current = current->left;
            }

            // Go right if value is larger
            else
            {

                if (current->right == nullptr)
                {
                    current->right = new TreeNode(val);
                    break;
                }
                current = current->right;
            }
        }

        // Root remains unchanged
        return root;
    }
};

int main()
{

    /*
            BST:
                8
              /   \
             5     12
            / \    / \
           4   7  10  14
    */

    TreeNode *root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(14);

    Solution sol;
    root = sol.insertIntoBST(root, 6);

    cout << "Inserted 6 into BST" << endl;

    return 0;
}
