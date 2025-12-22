#include <bits/stdc++.h>
using namespace std;

/*
    ============================
    Binary Search Tree Node
    ============================

    Each node contains:
    - data  : value of the node
    - left  : pointer to left child
    - right : pointer to right child

    BST Property:
    left subtree  < node
    right subtree > node
*/
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

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
    int k;      // Counter used during traversal
    int answer; // Stores kth smallest / largest value

    /*
        ============================
        Inorder Traversal (LNR)
        ============================
        Used to find Kth SMALLEST element

        Inorder traversal of BST gives values
        in ascending sorted order.
    */
    void inorder(TreeNode *root)
    {
        // Base case: empty node or already found answer
        if (root == nullptr || k == 0)
            return;

        // Step 1: Traverse left subtree
        inorder(root->left);

        // Step 2: Visit current node
        k--;
        if (k == 0)
        {
            answer = root->data;
            return;
        }

        // Step 3: Traverse right subtree
        inorder(root->right);
    }

    /*
        ============================
        Reverse Inorder Traversal (RNL)
        ============================
        Used to find Kth LARGEST element

        Reverse inorder traversal of BST gives
        values in descending order.
    */
    void reverseInorder(TreeNode *root)
    {
        // Base case
        if (root == nullptr || k == 0)
            return;

        // Step 1: Traverse right subtree first
        reverseInorder(root->right);

        // Step 2: Visit current node
        k--;
        if (k == 0)
        {
            answer = root->data;
            return;
        }

        // Step 3: Traverse left subtree
        reverseInorder(root->left);
    }

public:
    /*
        ============================
        Find Kth Smallest
        ============================
    */
    int kthSmallest(TreeNode *root, int K)
    {
        k = K;
        answer = -1;
        inorder(root);
        return answer;
    }

    /*
        ============================
        Find Kth Largest
        ============================
    */
    int kthLargest(TreeNode *root, int K)
    {
        k = K;
        answer = -1;
        reverseInorder(root);
        return answer;
    }

    /*
        ============================
        Final Function
        Returns:
        [kth smallest, kth largest]
        ============================
    */
    vector<int> kLargesSmall(TreeNode *root, int k)
    {
        int smallest = kthSmallest(root, k);
        int largest = kthLargest(root, k);
        return {smallest, largest};
    }
};

int main()
{
    /*
        Constructing BST:

                3
               / \
              1   4
               \
                2

        Inorder traversal:
        [1, 2, 3, 4]
    */

    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right = new TreeNode(4);

    Solution sol;

    int k = 1;

    vector<int> result = sol.kLargesSmall(root, k);

    cout << "Kth Smallest: " << result[0] << endl;
    cout << "Kth Largest : " << result[1] << endl;

    return 0;
}

// TS: O(N) in worst case (skewed BST), Best case O(log N): early stop before visiting all nodes
// SC: O(H) → recursion stack, H = log N (balanced BST), H = N (skewed BST)