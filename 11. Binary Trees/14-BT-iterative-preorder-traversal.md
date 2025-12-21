# BINARY TREE — ITERATIVE PREORDER TRAVERSAL (STACK)

---

## What We Covered Here

1. Why iterative traversal is needed
2. Difference between recursive and iterative preorder
3. Core rule of preorder (Root → Left → Right)
4. Why stack is used in iterative preorder
5. Exact algorithm for iterative preorder traversal
6. Why **right child is pushed before left**
7. Step-by-step dry run (very detailed, stack-based)
8. C++ implementation (clean + deeply commented)
9. JavaScript implementation (clean + deeply commented)
10. Time & space complexity (balanced vs skewed tree)
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---
## 1. Why Do We Need Iterative Preorder? (Mindset)

Recursive preorder is simple, but:

* Recursion uses **system stack**
* Stack size is limited
* Some interviews **explicitly ban recursion**

So we must:

> **Manually manage the stack**

That’s exactly what we do here.


#### Iterative means (in simple words)

**Iterative** means solving a problem **using loops and your own data structures**
instead of using **recursion**.

---

#### Key Idea

* **Recursive approach** → system call stack is used automatically
* **Iterative approach** → **you manage the stack/queue yourself**

So:

```
Recursive = implicit stack (call stack)
Iterative = explicit stack / queue (you create it)
```

---

## 2. Preorder Rule (Recall Quickly)

```
PREORDER = ROOT → LEFT → RIGHT
```

So at every node:

1. Visit node
2. Go left
3. Go right

---

## 3. Key Insight (Most Important)

In recursion:

* Function calls go onto **call stack**

In iteration:

* We use our **own stack**

> **Stack = recursion replacement**

---

## 4. Core Idea of Iterative Preorder

1. Push root into stack
2. While stack is not empty:

   * Pop top node
   * Visit it
   * Push its **right child**
   * Push its **left child**

Why this order?

---

## 5. Why Push RIGHT Before LEFT? (Interview Trap)

Stack is **LIFO**:

```
Last In → First Out
```

We want:

```
Root → Left → Right
```

So:

* Push **right first**
* Then push **left**

This ensures:

* Left is processed before right

If you reverse this → traversal breaks.

---

## 6. Algorithm (Clear and Structured)

```
IF root is NULL:
    return empty array

Push root to stack

WHILE stack is not empty:
    node = stack.top()
    stack.pop()

    visit node

    IF node.right exists:
        push node.right
    IF node.left exists:
        push node.left
```

---

## 7. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
        / \
       4   5
```

Expected Output:

```
[1, 2, 4, 5, 3]
```

---

## 8. Dry Run — Step by Step (STACK FOCUS)

### Initial State

```
stack = [1]
output = []
```

---

### Iteration 1

* Pop `1`
* Visit `1`
* Push right `3`
* Push left `2`

```
stack = [3, 2]
output = [1]
```

---

### Iteration 2

* Pop `2`
* Visit `2`
* Push right `5`
* Push left `4`

```
stack = [3, 5, 4]
output = [1, 2]
```

---

### Iteration 3

* Pop `4`
* Visit `4`
* No children

```
stack = [3, 5]
output = [1, 2, 4]
```

---

### Iteration 4

* Pop `5`
* Visit `5`
* No children

```
stack = [3]
output = [1, 2, 4, 5]
```

---

### Iteration 5

* Pop `3`
* Visit `3`
* No children

```
stack = []
output = [1, 2, 4, 5, 3]
```

Stack empty → stop.

---

## 9. C++ — Iterative Preorder (Core Logic)

### Version 1 — Only Required Function

```cpp
vector<int> preorderTraversal(TreeNode* root) {

    vector<int> preorder;
    if (root == nullptr) return preorder;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();

        preorder.push_back(node->val);

        if (node->right != nullptr)
            st.push(node->right);

        if (node->left != nullptr)
            st.push(node->left);
    }

    return preorder;
}
```

---

## 10. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode {
    int val;                // Value of node
    TreeNode* left;         // Left child
    TreeNode* right;        // Right child

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {

        vector<int> preorder;

        // Edge case: empty tree
        if (root == nullptr) {
            return preorder;
        }

        // Stack to simulate recursion
        stack<TreeNode*> st;
        st.push(root);

        // Iterate until stack becomes empty
        while (!st.empty()) {

            // Step 1: Get top node
            TreeNode* node = st.top();
            st.pop();

            // Step 2: Visit node
            preorder.push_back(node->val);

            // Step 3: Push right child first
            if (node->right != nullptr) {
                st.push(node->right);
            }

            // Step 4: Push left child
            if (node->left != nullptr) {
                st.push(node->left);
            }
        }

        return preorder;
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
    vector<int> result = sol.preorderTraversal(root);

    cout << "Preorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
```

---

## 11. JavaScript — Iterative Preorder

```javascript
function preorderTraversal(root) {
    let result = [];
    if (root === null) return result;

    let stack = [];
    stack.push(root);

    while (stack.length > 0) {
        let node = stack.pop();
        result.push(node.data);

        if (node.right !== null) stack.push(node.right);
        if (node.left !== null) stack.push(node.left);
    }

    return result;
}
```

---

## 12. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

* Each node is:

  * Pushed once
  * Popped once
* Constant work per node

So total = **O(N)**

---

### Space Complexity — **O(H)**

* Stack holds at most height of tree
* Balanced tree → **O(log N)**
* Skewed tree → **O(N)**

Interview-safe answer:

```
Space Complexity = O(H)
```

---

## 13. Common Mistakes (Interview Traps)

1. Pushing left before right → wrong order
2. Forgetting null root check
3. Thinking stack size is always log N
4. Confusing DFS stack with BFS queue

---

## 14. Interview-Level Q&A Synthesis

### Q1. Why push right child first?

To ensure left is processed first (LIFO).

---

### Q2. Is iterative preorder faster than recursive?

No, same time complexity.

---

### Q3. When to prefer iterative?

When recursion is restricted or stack overflow risk exists.

---

### Q4. Can we do preorder without stack or recursion?

Yes — **Morris Traversal** (advanced).

---

### Q5. Difference between DFS iterative and recursive?

Only stack handling differs; logic is same.

---

## Key Takeaway (Lock This)

> **Iterative Preorder = Stack + (Right first, Left second)**
> If stack order is right, traversal is correct.
