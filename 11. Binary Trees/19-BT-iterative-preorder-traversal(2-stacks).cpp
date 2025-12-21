#include <bits/stdc++.h>
using namespace std;

// Node structure
struct Node
{
    int data;    // Value of node
    Node *left;  // Left child
    Node *right; // Right child

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

vector<int> postOrder(Node *root)
{

    vector<int> postorder;

    // Edge case
    if (root == nullptr)
    {
        return postorder;
    }

    // Two stacks
    stack<Node *> st1, st2;

    // Push root to first stack
    st1.push(root);

    // Process all nodes
    while (!st1.empty())
    {

        // Pop from stack1
        Node *node = st1.top();
        st1.pop();

        // Push into stack2
        st2.push(node);

        // Push children into stack1
        if (node->left != nullptr)
        {
            st1.push(node->left);
        }
        if (node->right != nullptr)
        {
            st1.push(node->right);
        }
    }

    // stack2 now contains reverse postorder
    while (!st2.empty())
    {
        postorder.push_back(st2.top()->data);
        st2.pop();
    }

    return postorder;
}

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

    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    vector<int> result = postOrder(root);

    cout << "Postorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }

    return 0;
}
