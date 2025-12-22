#include <bits/stdc++.h>
using namespace std;

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
    TreeNode *deleteNode(TreeNode *root, int key)
    {

        if (root == nullptr)
        {
            return nullptr;
        }

        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            // Node to delete found

            // Case 1: No left child
            if (root->left == nullptr)
            {
                return root->right;
            }

            // Case 2: No right child
            if (root->right == nullptr)
            {
                return root->left;
            }

            // Case 3: Two children
            TreeNode *successor = root->right;

            // Find inorder successor
            while (successor->left != nullptr)
            {
                successor = successor->left;
            }

            // Replace value
            root->val = successor->val;

            // Delete successor node
            root->right = deleteNode(root->right, successor->val);
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
        / \    /
       4   7  10
    */

    TreeNode *root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(10);

    Solution sol;
    root = sol.deleteNode(root, 8);

    cout << "Deleted node 8 from BST" << endl;

    return 0;
}
