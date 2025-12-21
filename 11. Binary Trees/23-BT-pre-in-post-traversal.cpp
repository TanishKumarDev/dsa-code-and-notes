#include <bits/stdc++.h>
using namespace std;

/*
    Node structure for Binary Tree
    Each node contains:
    - data  : value stored in node
    - left  : pointer to left child
    - right : pointer to right child
*/
struct Node
{
    int data;
    Node *left;
    Node *right;

    // Constructor to initialize a node
    Node(int val)
    {
        data = val;      // assign value
        left = nullptr;  // initially no left child
        right = nullptr; // initially no right child
    }
};

class Solution
{
public:
    /*
        Function to get Preorder, Inorder and Postorder
        traversal in ONE ITERATION using a stack.

        Return format:
        {
            preorder vector,
            inorder vector,
            postorder vector
        }
    */
    vector<vector<int>> preInPostTraversal(Node *root)
    {
        // Vectors to store traversal results
        vector<int> pre;  // Preorder result
        vector<int> in;   // Inorder result
        vector<int> post; // Postorder result

        // Edge case: empty tree
        if (root == nullptr)
            return {};

        /*
            Stack stores:
            pair<node, state>

            state = 1 → node just visited (Preorder)
            state = 2 → left subtree done (Inorder)
            state = 3 → both subtrees done (Postorder)
        */
        stack<pair<Node *, int>> st;

        // Start traversal with root node, state = 1
        st.push({root, 1});

        // Process stack until empty
        while (!st.empty())
        {
            // Get top element
            auto it = st.top();
            st.pop();

            /*
                STATE 1 → PREORDER
                Action:
                - Visit node
                - Move state to 2
                - Push left child
            */
            if (it.second == 1)
            {
                // Preorder visit
                pre.push_back(it.first->data);

                // Increment state
                it.second = 2;

                // Push current node back with updated state
                st.push(it);

                // If left child exists, process it first
                if (it.first->left != nullptr)
                {
                    st.push({it.first->left, 1});
                }
            }

            /*
                STATE 2 → INORDER
                Action:
                - Visit node
                - Move state to 3
                - Push right child
            */
            else if (it.second == 2)
            {
                // Inorder visit
                in.push_back(it.first->data);

                // Increment state
                it.second = 3;

                // Push current node back with updated state
                st.push(it);

                // If right child exists, process it
                if (it.first->right != nullptr)
                {
                    st.push({it.first->right, 1});
                }
            }

            /*
                STATE 3 → POSTORDER
                Action:
                - Visit node
                - Do NOT push back (processing complete)
            */
            else
            {
                // Postorder visit
                post.push_back(it.first->data);
            }
        }

        // Return all three traversals
        return {pre, in, post};
    }
};

int main()
{
    /*
        Creating the binary tree:

                1
               / \
              2   3
             / \
            4   5
    */

    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    // Solution object
    Solution sol;

    // Get traversals
    auto res = sol.preInPostTraversal(root);

    // Print Preorder
    cout << "Preorder: ";
    for (int x : res[0])
        cout << x << " ";
    cout << endl;

    // Print Inorder
    cout << "Inorder: ";
    for (int x : res[1])
        cout << x << " ";
    cout << endl;

    // Print Postorder
    cout << "Postorder: ";
    for (int x : res[2])
        cout << x << " ";
    cout << endl;

    return 0;
}
