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
    bool isValidBST(TreeNode *root)
    {
        return check(root, LONG_MIN, LONG_MAX);
    }

private:
    bool check(TreeNode *node, long minVal, long maxVal)
    {

        // Empty tree is valid
        if (node == nullptr)
        {
            return true;
        }

        // Current node must lie in (min, max)
        if (node->val <= minVal || node->val >= maxVal)
        {
            return false;
        }

        // Left subtree: max bound becomes current value
        // Right subtree: min bound becomes current value
        return check(node->left, minVal, node->val) &&
               check(node->right, node->val, maxVal);
    }
};

int main()
{

    /*
            10
           /  \
          5    15
              /
             6   -> INVALID BST
    */

    TreeNode *root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(6);

    Solution sol;

    if (sol.isValidBST(root))
        cout << "Valid BST" << endl;
    else
        cout << "Invalid BST" << endl;

    return 0;
}
