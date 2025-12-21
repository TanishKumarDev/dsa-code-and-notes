# BINARY TREE — POSTORDER TRAVERSAL (RECURSIVE)

---

## What We Covered Here

1. What postorder traversal means (again, clearly)
2. Exact traversal order (Left → Right → Root)
3. Why postorder is called a **bottom-up traversal**
4. Recursive algorithm breakdown
5. Base case vs recursive case clarity
6. Very deep step-by-step dry run
7. C++ recursive implementation (clean + deep comments)
8. JavaScript recursive implementation
9. Time & space complexity (with intuition)
10. Common mistakes
11. Interview-level Q&A synthesis

---

## 1. Postorder Traversal — Meaning (Reconfirm)

**Postorder traversal** means:

```
LEFT → RIGHT → ROOT
```

Interpretation:

* Do **not** touch the root first
* Completely finish **left subtree**
* Completely finish **right subtree**
* Only then process the **current node**

That’s why it’s called **post-order**
(root comes **after** children).

---

## 2. Why Postorder Is Important

Postorder is used when:

* Parent depends on children
* We want **bottom-up computation**
* We want to **delete a tree safely**
* We evaluate **expression trees**

Interview line you can say:

> “Postorder ensures children are processed before parent.”

---

## 3. Recursive Thinking (MOST IMPORTANT)

At **every node**, ask only one question:

> “Have my left and right subtrees finished?”

If **NO** → go deeper
If **YES** → process current node

Recursion naturally enforces this.

---

## 4. Recursive Algorithm (Clean)

For a node `root`:

1. Traverse left subtree
2. Traverse right subtree
3. Visit `root`

---

## 5. Pseudocode (Before Code)

```
POSTORDER(root):
    IF root is NULL:
        return

    POSTORDER(root.left)
    POSTORDER(root.right)
    visit(root)
```

Nothing extra.
Nothing fancy.
Order is everything.

---

## 6. Example Tree (Dry Run Tree)

```
            1
          /   \
         2     3
```

Expected Output:

```
[2, 3, 1]
```

---

## 7. Dry Run — Step by Step (VERY IMPORTANT)

### Call Stack Flow

```
postorder(1)
 ├─ postorder(2)
 │   ├─ postorder(NULL)
 │   ├─ postorder(NULL)
 │   └─ visit 2
 ├─ postorder(3)
 │   ├─ postorder(NULL)
 │   ├─ postorder(NULL)
 │   └─ visit 3
 └─ visit 1
```

---

### Execution Table

| Step | Current Node | Action Taken    | Output    |
| ---- | ------------ | --------------- | --------- |
| 1    | 1            | Go left         | []        |
| 2    | 2            | Go left (NULL)  | []        |
| 3    | 2            | Go right (NULL) | []        |
| 4    | 2            | Visit           | [2]       |
| 5    | 1            | Go right        | [2]       |
| 6    | 3            | Go left (NULL)  | [2]       |
| 7    | 3            | Go right (NULL) | [2]       |
| 8    | 3            | Visit           | [2, 3]    |
| 9    | 1            | Visit           | [2, 3, 1] |

---

### Key Observation

Root `1` is printed **last**, not first.

That single rule defines postorder.

---

## 8. C++ — Recursive Postorder (Core Function)

### Version 1 — Only Required Function

```cpp
void postorderTraversal(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;

    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result.push_back(root->val);
}
```

---

## 9. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Definition of TreeNode
struct TreeNode {
    int val;                 // Value stored in node
    TreeNode* left;          // Left child
    TreeNode* right;         // Right child

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    void postorderTraversal(TreeNode* root, vector<int>& result) {

        // Base case:
        // If node is NULL, nothing to process
        if (root == nullptr) {
            return;
        }

        // Step 1: Traverse left subtree
        postorderTraversal(root->left, result);

        // Step 2: Traverse right subtree
        postorderTraversal(root->right, result);

        // Step 3: Process current node
        // This happens AFTER both children
        result.push_back(root->val);
    }
};

int main() {

    /*
            Tree:
                1
              /   \
             2     3
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    Solution sol;
    vector<int> result;

    sol.postorderTraversal(root, result);

    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
```

---

## 10. JavaScript — Recursive Postorder

```javascript
function postorderTraversal(root, result) {
    if (root === null) return;

    postorderTraversal(root.left, result);
    postorderTraversal(root.right, result);
    result.push(root.data);
}

function postorder(root) {
    let result = [];
    postorderTraversal(root, result);
    return result;
}
```

---

## 11. Time & Space Complexity (Deep Intuition)

### Time Complexity — **O(N)**

* Each node is visited exactly once
* Constant work per node

So:

```
O(N)
```

---

### Space Complexity — **O(N)** (Worst Case)

Why?

* Recursion stack stores function calls
* Worst case: skewed tree → N calls

Balanced tree:

* Stack depth = O(log N)

Interview-safe answer:

```
Space = O(N)
```

---

## 12. Common Mistakes

1. Visiting root before children (becomes preorder)
2. Forgetting base case
3. Thinking postorder is rarely used
4. Confusing recursion order

---

## 13. Interview-Level Q&A Synthesis

### Q1. Why root is visited last?

Because postorder is bottom-up.

---

### Q2. Where is postorder used?

Tree deletion, expression evaluation, DP on trees.

---

### Q3. Recursive vs iterative — which is simpler?

Recursive.

---

### Q4. Which traversal is hardest to simulate iteratively?

Postorder.

---

### Q5. Can postorder be done without recursion?

Yes — using 2 stacks or 1 stack (advanced).

---

## Key Takeaway (LOCK THIS)

> **Postorder = children first, parent last**
> If this is clear, recursion feels natural.

---
