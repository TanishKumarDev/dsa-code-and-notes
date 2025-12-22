# CEIL IN A BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. What “Ceil” means in BST (clear definition)
2. Why BST ordering makes ceil efficient
3. Core intuition (how to think, not code)
4. Step-by-step algorithm
5. Dry run with clear traversal path
6. Iterative solution (interview-preferred)
7. Recursive alternative (conceptual)
8. C++ code (clean + deeply commented)
9. JavaScript code (same logic)
10. Time & space complexity
11. Common mistakes
12. Interview-level Q&A synthesis

---

## 1. What Is Ceil in a BST?

**Ceil of a key `X`** =
👉 **Smallest value in the BST such that value ≥ X**

If **no such value exists**, return **-1 / nullptr**.

---

### Simple Example

BST (inorder):

```
2 3 4 5 6 9 10 11 13 14
```

| Key | Ceil |
| --- | ---- |
| 8   | 9    |
| 5   | 5    |
| 15  | -1   |
| 1   | 2    |

---

## 2. Why BST Makes Ceil Easy

Because BST has **sorted structure**:

```
Left subtree  <  Node  <  Right subtree
```

So:

* If key is **smaller** than node → node is a **possible ceil**
* If key is **greater** → ceil must be on the **right**

No full traversal needed.

---

## 3. Core Intuition (MOST IMPORTANT)

> **While searching for the key, keep track of the best possible answer.**

We:

* Move like **BST search**
* Update `ceil` only when we go **left**

---

## 4. Step-By-Step Thinking

At every node:

1. If `node.val == key`

   * This is the **exact ceil**
   * Return immediately

2. If `key < node.val`

   * Current node is a **candidate ceil**
   * Store it
   * Move **left** (to find smaller valid ceil)

3. If `key > node.val`

   * Ceil must be **greater**
   * Move **right**

---

## 5. Pseudocode (Mindset First)

```
ceil = -1
current = root

WHILE current != null:
    IF current.value == key:
        ceil = current.value
        BREAK
    ELSE IF key < current.value:
        ceil = current.value
        current = current.left
    ELSE:
        current = current.right

RETURN ceil
```

---

## 6. Dry Run (Step-by-Step, No Skips)

### BST

```
            10
          /    \
         5      13
        / \     / \
       3   6   11  14
      / \   \
     2   4   9
```

### Target = **8**

| Step | Node | Comparison | Ceil | Move  |
| ---- | ---- | ---------- | ---- | ----- |
| 1    | 10   | 8 < 10     | 10   | Left  |
| 2    | 5    | 8 > 5      | 10   | Right |
| 3    | 6    | 8 > 6      | 10   | Right |
| 4    | 9    | 8 < 9      | 9    | Left  |
| 5    | null | stop       | 9    | —     |

**Answer: 9**

---

## 7. C++ Code — Required Function (Clean)

```cpp
int findCeil(TreeNode* root, int key) {
    int ceil = -1;

    while (root != nullptr) {

        // Exact match
        if (root->val == key) {
            return root->val;
        }

        // Possible ceil found
        if (key < root->val) {
            ceil = root->val;
            root = root->left;
        }
        // Move right to find bigger values
        else {
            root = root->right;
        }
    }

    return ceil;
}
```

---

## 8. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// BST Node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    int findCeil(TreeNode* root, int key) {

        int ceil = -1; // stores best answer so far

        while (root != nullptr) {

            // Case 1: exact match
            if (root->val == key) {
                return root->val;
            }

            // Case 2: key is smaller → possible ceil
            if (key < root->val) {
                ceil = root->val;
                root = root->left;
            }
            // Case 3: key is larger → move right
            else {
                root = root->right;
            }
        }

        return ceil;
    }
};

int main() {

    TreeNode* root = new TreeNode(10);
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

    cout << "Ceil of " << key << " is: "
         << sol.findCeil(root, key) << endl;

    return 0;
}
```

---

## 9. JavaScript Code (Same Logic)

```javascript
function findCeil(root, key) {
    let ceil = -1;

    while (root !== null) {

        if (root.data === key) {
            return root.data;
        }

        if (key < root.data) {
            ceil = root.data;
            root = root.left;
        } else {
            root = root.right;
        }
    }

    return ceil;
}
```

---

## 10. Time & Space Complexity

### Time Complexity

* **Average (balanced BST):** `O(log N)`
* **Worst (skewed BST):** `O(N)`

---

### Space Complexity

* Iterative approach → **O(1)**

---

## 11. Common Mistakes

1. Updating ceil when moving right ❌
2. Traversing whole tree ❌
3. Confusing floor and ceil ❌
4. Returning root instead of value ❌

---

## 12. Interview-Level Q&A Synthesis

### Q1. Why update ceil only when moving left?

Because current node is **greater than key**, so it’s a valid candidate.

---

### Q2. Can inorder traversal solve this?

Yes, but it’s **O(N)**, not optimal.

---

### Q3. What if key exists?

Key itself is the **ceil**.

---

### Q4. One-line intuition?

> **Search like BST, remember the last bigger value.**

---

## Key Takeaway (LOCK THIS)

> **Ceil = nearest greater-or-equal value
> found while moving left during BST search**
