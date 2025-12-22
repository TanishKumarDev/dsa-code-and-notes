# INSERT INTO A BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. Problem restatement (clear and simple)
2. Why insertion uses the **same logic as search**
3. Core BST rule revisited
4. Step-by-step insertion intuition
5. Iterative insertion (interview preferred)
6. Recursive insertion (conceptual clarity)
7. Dry run (successful insert)
8. C++ implementation (clean + deep commented)
9. JavaScript implementation
10. Time & space complexity (best, worst)
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. Problem Restatement (Simple Words)

You are given:

* The **root of a Binary Search Tree**
* A **value to insert**

Your task:

* Insert the value **at the correct position**
* **Maintain BST property**
* Return the **root** of the tree

---

## 2. Very Important Rule (Insertion NEVER Breaks This)

For every node:

```
Left Subtree < Node < Right Subtree
```

Insertion must **respect this rule at every step**.

---

## 3. Key Insight (MOST IMPORTANT)

> **Insertion in BST is just SEARCH until you hit NULL**

That’s it.

* While searching:

  * If value < node → go left
  * If value > node → go right
* When you reach `null`

  * Insert new node there

---

## 4. High-Level Insertion Strategy

1. If tree is empty → new node becomes root
2. Start from root
3. Compare value with current node
4. Move left or right accordingly
5. Stop when child pointer is `null`
6. Attach new node there

---

## 5. Example Tree (We Will Insert Into This)

Initial BST:

```
            8
          /   \
         5     12
        / \    / \
       4   7  10  14
```

Insert value = **6**

---

## 6. Dry Run (Step-by-Step)

| Step | Current Node | Comparison | Move        |
| ---- | ------------ | ---------- | ----------- |
| 1    | 8            | 6 < 8      | Left        |
| 2    | 5            | 6 > 5      | Right       |
| 3    | 7            | 6 < 7      | Left        |
| 4    | null         | —          | Insert here |

Final BST:

```
            8
          /   \
         5     12
        / \    / \
       4   7  10  14
          /
         6
```

---

## 7. Pseudocode (Think Before Code)

```
INSERT(root, value):

IF root is null:
    return new node(value)

current = root

WHILE true:
    IF value < current.value:
        IF current.left is null:
            current.left = new node(value)
            break
        current = current.left
    ELSE:
        IF current.right is null:
            current.right = new node(value)
            break
        current = current.right

RETURN root
```

---

## 8. C++ — Iterative Insert (Core Function)

### Version 1 — Only Required Function

```cpp
TreeNode* insertIntoBST(TreeNode* root, int val) {

    // If tree is empty, new node becomes root
    if (root == nullptr) {
        return new TreeNode(val);
    }

    TreeNode* current = root;

    while (true) {

        // Move to left subtree
        if (val < current->val) {

            // If empty spot found, insert here
            if (current->left == nullptr) {
                current->left = new TreeNode(val);
                break;
            }
            current = current->left;
        }

        // Move to right subtree
        else {

            // If empty spot found, insert here
            if (current->right == nullptr) {
                current->right = new TreeNode(val);
                break;
            }
            current = current->right;
        }
    }

    return root;
}
```

---

## 9. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// BST Node definition
struct TreeNode {
    int val;                // Node value
    TreeNode* left;         // Left child
    TreeNode* right;        // Right child

    TreeNode(int data) {
        val = data;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {

        // Case 1: Empty tree
        if (root == nullptr) {
            return new TreeNode(val);
        }

        TreeNode* current = root;

        // Traverse the tree
        while (true) {

            // Go left if value is smaller
            if (val < current->val) {

                if (current->left == nullptr) {
                    current->left = new TreeNode(val);
                    break;
                }
                current = current->left;
            }

            // Go right if value is larger
            else {

                if (current->right == nullptr) {
                    current->right = new TreeNode(val);
                    break;
                }
                current = current->right;
            }
        }

        // Root remains unchanged
        return root;
    }
};

int main() {

    /*
            BST:
                8
              /   \
             5     12
            / \    / \
           4   7  10  14
    */

    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(14);

    Solution sol;
    root = sol.insertIntoBST(root, 6);

    cout << "Inserted 6 into BST" << endl;

    return 0;
}
```

---

## 10. JavaScript — Insert into BST

```javascript
function insertIntoBST(root, val) {

    if (root === null) {
        return new Node(val);
    }

    let current = root;

    while (true) {

        if (val < current.data) {

            if (current.left === null) {
                current.left = new Node(val);
                break;
            }
            current = current.left;
        } else {

            if (current.right === null) {
                current.right = new Node(val);
                break;
            }
            current = current.right;
        }
    }

    return root;
}
```

---

## 11. Recursive Insert (Conceptual Clarity)

```cpp
TreeNode* insertIntoBST(TreeNode* root, int val) {

    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }

    return root;
}
```

---

## 12. Time & Space Complexity

### Time Complexity

* **Average (balanced BST):** `O(log N)`
* **Worst case (skewed BST):** `O(N)`

---

### Space Complexity

* Iterative → `O(1)`
* Recursive → `O(H)` (height of tree)

---

## 13. Common Mistakes (Interview Traps)

1. Forgetting to return root
2. Breaking BST ordering
3. Trying to insert at wrong position
4. Using traversal instead of comparison logic
5. Not handling empty tree

---

## 14. Interview-Level Q&A Synthesis

### Q1. Why insertion uses search logic?

Because we need to **find the correct null position**.

---

### Q2. Can insertion rebalance the tree?

No — normal BST insertion does **not** balance.

---

### Q3. What happens with duplicates?

Usually ignored or placed consistently (depends on definition).

---

### Q4. Why iterative preferred?

No recursion stack, simpler control.

---

### Q5. One-line intuition?

**Search until null, then attach node.**

---

## Key Takeaway (LOCK THIS)

> **Insert = Search + Attach**
> If search logic is clear, insertion is trivial.
