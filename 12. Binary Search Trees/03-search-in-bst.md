# SEARCH IN A BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. Problem restatement in simple words
2. Why BST search is faster than Binary Tree search
3. Core BST rule used in searching
4. Step-by-step search intuition
5. Iterative approach (most preferred in interviews)
6. Recursive approach (for conceptual clarity)
7. Detailed dry run (successful + unsuccessful search)
8. C++ implementation (clean + deeply commented)
9. JavaScript implementation
10. Time & space complexity (average vs worst case)
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. Problem Restatement (Simple Words)

You are given:

* The **root of a Binary Search Tree**
* A **key (target value)**

Your task:

* If a node with value = `key` exists → **return that node**
* Otherwise → **return null**

---

## 2. Why Searching in BST Is Special

In a **normal Binary Tree**:

* No ordering
* You may need to check **all nodes** → `O(N)`

In a **BST**:

* Values are ordered
* At each step, you **discard half of the tree**

That’s the advantage.

---

## 3. BST Rule Used in Searching (Lock This)

At any node with value `X`:

```
if key < X  → go LEFT
if key > X  → go RIGHT
if key == X → FOUND
```

This rule alone defines the entire algorithm.

---

## 4. Search Strategy (High-Level Intuition)

1. Start from the **root**
2. Compare `key` with current node value
3. Move left or right based on comparison
4. Repeat until:

   * Key is found
   * Or you reach `null` (not found)

---

## 5. Algorithm (Iterative — Interview Preferred)

```
node = root

WHILE node is not null AND node.value != key:
    IF key < node.value:
        node = node.left
    ELSE:
        node = node.right

RETURN node   // either found node or null
```

Why iterative?

* No recursion stack
* Cleaner
* O(1) extra space

---

## 6. Example Tree (We Will Dry Run This)

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

## 7. Dry Run — Case 1 (Key FOUND)

### Search `key = 10`

| Step | Current Node | Comparison | Move  |
| ---- | ------------ | ---------- | ----- |
| 1    | 8            | 10 > 8     | Right |
| 2    | 12           | 10 < 12    | Left  |
| 3    | 10           | 10 == 10   | Found |

✔ **Node found**

---

## 8. Dry Run — Case 2 (Key NOT FOUND)

### Search `key = 3`

| Step | Current Node | Comparison | Move |
| ---- | ------------ | ---------- | ---- |
| 1    | 8            | 3 < 8      | Left |
| 2    | 5            | 3 < 5      | Left |
| 3    | 4            | 3 < 4      | Left |
| 4    | null         | —          | Stop |

❌ **Node not found**

---

## 9. C++ — Iterative Search (Core Logic)

### Version 1 — Only Required Function

```cpp
TreeNode* searchBST(TreeNode* root, int key) {

    // Traverse until node becomes null or key is found
    while (root != nullptr && root->val != key) {

        // If key is smaller, move to left subtree
        if (key < root->val) {
            root = root->left;
        }
        // If key is larger, move to right subtree
        else {
            root = root->right;
        }
    }

    // Returns found node or nullptr
    return root;
}
```

---

## 10. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// BST Node definition
struct TreeNode {
    int val;                // Value stored
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
    TreeNode* searchBST(TreeNode* root, int key) {

        // Start from root and move down
        while (root != nullptr) {

            // If key matches current node
            if (root->val == key) {
                return root;
            }

            // If key is smaller, go left
            if (key < root->val) {
                root = root->left;
            }
            // If key is larger, go right
            else {
                root = root->right;
            }
        }

        // Key not found
        return nullptr;
    }
};

int main() {

    /*
            BST:
                4
              /   \
             2     7
            / \
           1   3
    */

    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    TreeNode* result = sol.searchBST(root, 3);

    if (result)
        cout << "Node found: " << result->val << endl;
    else
        cout << "Node not found" << endl;

    return 0;
}
```

---

## 11. JavaScript — Iterative Search

```javascript
function searchBST(root, key) {

    let node = root;

    while (node !== null && node.data !== key) {

        if (key < node.data) {
            node = node.left;
        } else {
            node = node.right;
        }
    }

    return node; // found node or null
}
```

---

## 12. Recursive Version (Conceptual Clarity)

```cpp
TreeNode* searchBST(TreeNode* root, int key) {
    if (root == nullptr || root->val == key)
        return root;

    if (key < root->val)
        return searchBST(root->left, key);

    return searchBST(root->right, key);
}
```

---

## 13. Time & Space Complexity (Important)

### Time Complexity

* **Average case (balanced BST):** `O(log N)`
* **Worst case (skewed BST):** `O(N)`

---

### Space Complexity

* Iterative → `O(1)`
* Recursive → `O(H)` (recursion stack)

---

## 14. Common Mistakes (Interview Traps)

1. Using DFS traversal instead of BST logic
2. Forgetting BST property (left < node < right)
3. Assuming BST is always balanced
4. Returning `true/false` instead of node pointer
5. Using recursion when iterative is simpler

---

## 15. Interview-Level Q&A Synthesis

### Q1. Why is BST search faster than Binary Tree search?

Because ordering allows discarding half the tree at each step.

---

### Q2. Is BST search always O(log N)?

No — only if the tree is balanced.

---

### Q3. What traversal is used here?

None — direct value-based navigation.

---

### Q4. What if duplicates exist?

Depends on BST definition; usually duplicates are not allowed.

---

### Q5. One-line intuition?

**Compare, decide direction, move — repeat.**

---

## Key Takeaway (LOCK THIS)

> **BST search is binary search applied on tree structure**
> If BST rule is respected, search becomes fast and simple.

