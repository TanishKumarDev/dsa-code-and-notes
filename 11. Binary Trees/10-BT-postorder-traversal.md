# BINARY TREE — POSTORDER TRAVERSAL (DFS)

---

## What We Covered Here

1. What postorder traversal means
2. Core rule of postorder traversal (Left → Right → Root)
3. Why postorder is considered the trickiest traversal
4. Recursive algorithm and intuition
5. Base case vs recursive case clarity
6. Step-by-step dry run (very detailed)
7. C++ recursive implementation (clean + deeply commented)
8. JavaScript recursive implementation
9. Role of recursion stack in postorder
10. Time & space complexity (balanced vs skewed tree)
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. What Is Postorder Traversal? (Mindset First)

**Postorder traversal** means:

> Visit nodes in the order
> **LEFT → RIGHT → ROOT**

So for every node:

1. First finish the **entire left subtree**
2. Then finish the **entire right subtree**
3. Finally process the **current node**

---

## 2. Why Postorder Feels Difficult

Because:

* Root is visited **last**
* You don’t see output until children are done
* Requires strong recursion understanding

But once recursion clicks, postorder becomes automatic.

---

## 3. Postorder Traversal Rule (Lock This)

```
LEFT → RIGHT → ROOT
```

Compare all three:

| Traversal | Order               |
| --------- | ------------------- |
| Preorder  | Root → Left → Right |
| Inorder   | Left → Root → Right |
| Postorder | Left → Right → Root |

> **Root comes at the end in postorder**

---

## 4. Where Postorder Is Used (Interview Gold)

* Deleting a tree (children first, then parent)
* Expression tree evaluation
* Bottom-up computations
* Memory deallocation problems

---

## 5. Recursive Algorithm (Clear Thinking)

At any node `root`:

1. Traverse left subtree
2. Traverse right subtree
3. Visit current node

---

## 6. Pseudocode (Before Code)

```
POSTORDER(node):
    IF node is NULL:
        return

    POSTORDER(node.left)
    POSTORDER(node.right)
    visit(node)
```

This order **must not change**.

---

## 7. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
```

---

## 8. Dry Run — Step by Step (Very Deep)

### Expected Output

```
[2, 3, 1]
```

---

### Step-by-Step Execution Table

| Step | Current Node | Action Taken    | Output  |
| ---- | ------------ | --------------- | ------- |
| 1    | 1            | Go left         | []      |
| 2    | 2            | Go left (null)  | []      |
| 3    | 2            | Go right (null) | []      |
| 4    | 2            | Visit node      | [2]     |
| 5    | 1            | Go right        | [2]     |
| 6    | 3            | Go left (null)  | [2]     |
| 7    | 3            | Go right (null) | [2]     |
| 8    | 3            | Visit node      | [2,3]   |
| 9    | 1            | Visit node      | [2,3,1] |

---

### Call Stack Visualization (Very Important)

```
postorder(1)
 ├── postorder(2)
 │    ├── postorder(NULL)
 │    ├── postorder(NULL)
 │    └── visit 2
 ├── postorder(3)
 │    ├── postorder(NULL)
 │    ├── postorder(NULL)
 │    └── visit 3
 └── visit 1
```

This explains **why root is printed last**.

---

## 9. C++ — Recursive Postorder (Core Logic)

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

## 10. C++ — Recursive Postorder (Full Program, Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;               // Value stored in node
    TreeNode* left;        // Left child
    TreeNode* right;       // Right child

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
        // If current node is NULL, stop recursion
        if (root == nullptr) {
            return;
        }

        // Step 1: Traverse left subtree completely
        postorderTraversal(root->left, result);

        // Step 2: Traverse right subtree completely
        postorderTraversal(root->right, result);

        // Step 3: Visit current node (AFTER children)
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

## 11. JavaScript — Recursive Postorder

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

## 12. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

Why?

* Every node is visited exactly once
* Constant work per node

So total work = N → **O(N)**

---

### Space Complexity — **O(N)** (Worst Case)

Why?

* Recursion stack stores nodes
* Worst case (skewed tree) → N recursive calls

Balanced tree:

* Stack height = O(log N)

Interview-safe answer:

```
Space Complexity = O(N)
```

---

## 13. Common Mistakes (Interview Traps)

1. Visiting root too early (becomes inorder/preorder)
2. Forgetting base case
3. Confusing left-right order
4. Assuming postorder is rarely used (it is important)

---

## 14. Interview-Level Q&A Synthesis

### Q1. Why is postorder useful?

Because children are processed before parent.

---

### Q2. When should we prefer postorder?

When solving **bottom-up** problems.

---

### Q3. Can postorder be iterative?

Yes, but it is more complex (two stacks or modified preorder).

---

### Q4. Which traversal is hardest?

Postorder (conceptually).

---

### Q5. Which traversal deletes a tree safely?

Postorder.

---

## Key Takeaway (Lock This)

> **Postorder = children first, parent last**
> If recursion flow is clear, postorder becomes natural.
