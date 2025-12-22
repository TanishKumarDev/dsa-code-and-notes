#include <bits/stdc++.h>
using namespace std;

// BST Node
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

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
    int findFloor(TreeNode *root, int key)
    {

        int floor = -1; // stores best answer so far

        while (root != nullptr)
        {

            // Case 1: exact match
            if (root->val == key)
            {
                return root->val;
            }

            // Case 2: key is greater → possible floor
            if (key > root->val)
            {
                floor = root->val;
                root = root->right;
            }
            // Case 3: key is smaller → move left
            else
            {
                root = root->left;
            }
        }

        return floor;
    }
};

int main()
{

    TreeNode *root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(13);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(6);
    root->left->left->left = new TreeNode(2);
    root->left->left->right = new TreeNode(4);
    root->left->right->right = new TreeNode(9);
    root->right->left = new TreeNode(11);
    root->right->right = new TreeNode(14);

    Solution sol;
    int key = 8;

    cout << "Floor of " << key << " is: "
         << sol.findFloor(root, key) << endl;

    return 0;
}
