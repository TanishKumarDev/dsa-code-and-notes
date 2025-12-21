# BINARY TREE — ITERATIVE INORDER TRAVERSAL (STACK)

---

## What We Covered Here

1. Why iterative inorder traversal is needed
2. Inorder rule recap (Left → Root → Right)
3. Why recursion is not allowed sometimes
4. Core idea of iterative inorder traversal
5. Role of stack in replacing recursion
6. Left-subtree exhaustion concept
7. Step-by-step dry run (very detailed)
8. C++ iterative inorder (clean + deeply commented)
9. JavaScript iterative inorder
10. Time & space complexity (balanced vs skewed tree)
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. Inorder Rule (Quick Recall)

```
INORDER = LEFT → ROOT → RIGHT
```

Meaning:

* Go as left as possible
* Then process node
* Then move to right

---

## 2. Why Iterative Inorder Is Tricky

In recursion:

* System remembers where to return

In iteration:

* **YOU must remember it**

That memory is stored in a **stack**.

---

## 3. Core Insight (MOST IMPORTANT)

> **Iterative inorder = left descent + stack + controlled backtracking**

You:

* Push nodes while going left
* Pop when left is exhausted
* Visit node
* Move to right

---

## 4. Mental Model (Lock This)

Think like this:

> “Go left until you can’t.
> Then go up one step, visit, and go right.”

Repeat this until everything is done.

---

## 5. Algorithm (Structured & Clean)

```
Initialize empty stack
node = root

WHILE stack not empty OR node != NULL:
    IF node != NULL:
        push node into stack
        node = node.left
    ELSE:
        node = stack.top()
        stack.pop()
        visit node
        node = node.right
```

This loop **never misses a node**.

---

## 6. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
        / \
       4   5
```

Expected Output:

```
[4, 2, 5, 1, 3]
```

---

## 7. Dry Run — Step by Step (STACK FOCUS)

### Initial State

```
node = 1
stack = []
output = []
```

---

### Phase 1 — Go Left

| Action | Node | Stack   | Output |
| ------ | ---- | ------- | ------ |
| Push 1 | 2    | [1]     | []     |
| Push 2 | 4    | [1,2]   | []     |
| Push 4 | null | [1,2,4] | []     |

---

### Phase 2 — Process & Backtrack

| Action       | Node | Stack | Output |
| ------------ | ---- | ----- | ------ |
| Pop 4, visit | null | [1,2] | [4]    |
| Move right   | null | [1,2] | [4]    |

---

### Continue

| Action       | Node | Stack | Output      |
| ------------ | ---- | ----- | ----------- |
| Pop 2, visit | 5    | [1]   | [4,2]       |
| Push 5       | null | [1,5] | [4,2]       |
| Pop 5, visit | null | [1]   | [4,2,5]     |
| Pop 1, visit | 3    | []    | [4,2,5,1]   |
| Push 3       | null | [3]   | [4,2,5,1]   |
| Pop 3, visit | null | []    | [4,2,5,1,3] |

Stack empty & node null → stop.

---

## 8. C++ — Iterative Inorder (Core Logic)

### Version 1 — Only Required Function

```cpp
vector<int> inorder(TreeNode* root) {

    vector<int> inorder;
    stack<TreeNode*> st;
    TreeNode* node = root;

    while (!st.empty() || node != nullptr) {

        if (node != nullptr) {
            st.push(node);
            node = node->left;
        }
        else {
            node = st.top();
            st.pop();
            inorder.push_back(node->data);
            node = node->right;
        }
    }

    return inorder;
}
```

---

## 9. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode {
    int data;              // Value of node
    TreeNode* left;        // Left child
    TreeNode* right;       // Right child

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    vector<int> inorder(TreeNode* root) {

        vector<int> inorder;         // Result
        stack<TreeNode*> st;          // Stack for simulation
        TreeNode* node = root;        // Current pointer

        // Continue until all nodes processed
        while (!st.empty() || node != nullptr) {

            // Step 1: Go left as much as possible
            if (node != nullptr) {
                st.push(node);
                node = node->left;
            }
            else {
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

int main() {

    /*
            Tree:
                1
              /   \
             2     3
            / \
           4   5
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<int> result = sol.inorder(root);

    cout << "Inorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
```

---

## 10. JavaScript — Iterative Inorder

```javascript
function inorderTraversal(root) {
    let result = [];
    let stack = [];
    let node = root;

    while (stack.length > 0 || node !== null) {

        if (node !== null) {
            stack.push(node);
            node = node.left;
        } else {
            node = stack.pop();
            result.push(node.data);
            node = node.right;
        }
    }

    return result;
}
```

---

## 11. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

* Every node is:

  * Pushed once
  * Popped once
* Constant work per node

So:

```
Time = O(N)
```

---

### Space Complexity — **O(H)**

* Stack holds at most height of tree
* Balanced tree → O(log N)
* Skewed tree → O(N)

Interview-safe answer:

```
Space = O(H)
```

---

## 12. Common Mistakes (Interview Traps)

1. Forgetting `while(stack || node)` condition
2. Visiting node before left (becomes preorder)
3. Moving right too early
4. Thinking space is always log N

---

## 13. Interview-Level Q&A Synthesis

### Q1. Why do we go left first?

Because inorder demands left subtree first.

---

### Q2. Why stack is needed?

To remember return points after left subtree.

---

### Q3. Recursive vs iterative — which is better?

Same complexity; iterative avoids stack overflow.

---

### Q4. Can inorder be done without stack or recursion?

Yes — **Morris Traversal** (advanced).

---

### Q5. Inorder traversal of BST gives?

**Sorted order**.

---

## Key Takeaway (Lock This)

> **Iterative Inorder = Left descent + Stack + Controlled Backtracking**

If this mental model is clear, you will **never forget inorder traversal**.