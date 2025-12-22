# FIND MINIMUM & MAXIMUM IN A BST

---

## What We Covered Here

1. Why finding Min/Max is **easy in BST**
2. Core observation (leftmost / rightmost)
3. Finding Minimum in BST
4. Finding Maximum in BST
5. Step-by-step dry run
6. Iterative approach (preferred)
7. Recursive approach (conceptual)
8. C++ implementation (clean + deep commented)
9. JavaScript implementation
10. Time & space complexity
11. Common mistakes
12. Interview-level Q&A synthesis

---

## 1. Key Observation (MOST IMPORTANT)

Because of BST property:

```
Left Subtree < Node < Right Subtree
```

👉 **Minimum value** is found by:

* Going **as left as possible**

👉 **Maximum value** is found by:

* Going **as right as possible**

No full traversal needed.

---

## 2. Visual Intuition

Example BST:

```
            8
          /   \
         5     12
        / \    / \
       2   7  10  14
      /
     1
```

* **Minimum = 1** (leftmost)
* **Maximum = 14** (rightmost)

---

## 3. Find Minimum in BST (Thinking)

### Step-by-step logic

1. Start from root
2. Keep moving to `left`
3. Stop when `left == null`
4. Current node is the **minimum**

---

### Pseudocode (Minimum)

```
FIND_MIN(root):
    IF root is null:
        return null

    current = root
    WHILE current.left is not null:
        current = current.left

    return current
```

---

## 4. Find Maximum in BST (Thinking)

### Step-by-step logic

1. Start from root
2. Keep moving to `right`
3. Stop when `right == null`
4. Current node is the **maximum**

---

### Pseudocode (Maximum)

```
FIND_MAX(root):
    IF root is null:
        return null

    current = root
    WHILE current.right is not null:
        current = current.right

    return current
```

---

## 5. Dry Run (Important)

Using this BST:

```
            8
          /   \
         5     12
        / \    / \
       2   7  10  14
```

### Find Minimum

| Step  | Node         |
| ----- | ------------ |
| Start | 8            |
| Left  | 5            |
| Left  | 2            |
| Stop  | left is null |

✅ Min = **2**

---

### Find Maximum

| Step  | Node          |
| ----- | ------------- |
| Start | 8             |
| Right | 12            |
| Right | 14            |
| Stop  | right is null |

✅ Max = **14**

---

## 6. C++ Code (Iterative – Preferred)

### Version 1 — Only Required Functions

```cpp
TreeNode* findMin(TreeNode* root) {
    if (root == nullptr) return nullptr;

    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

TreeNode* findMax(TreeNode* root) {
    if (root == nullptr) return nullptr;

    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}
```

---

## 7. C++ Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// BST Node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data) {
        val = data;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    // Find minimum value node
    TreeNode* findMin(TreeNode* root) {

        // Edge case: empty tree
        if (root == nullptr) return nullptr;

        // Move to leftmost node
        while (root->left != nullptr) {
            root = root->left;
        }

        return root;
    }

    // Find maximum value node
    TreeNode* findMax(TreeNode* root) {

        // Edge case: empty tree
        if (root == nullptr) return nullptr;

        // Move to rightmost node
        while (root->right != nullptr) {
            root = root->right;
        }

        return root;
    }
};

int main() {

    /*
            8
          /   \
         5     12
        / \    / \
       2   7  10  14
    */

    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(14);

    Solution sol;

    TreeNode* minNode = sol.findMin(root);
    TreeNode* maxNode = sol.findMax(root);

    cout << "Minimum value: " << minNode->val << endl;
    cout << "Maximum value: " << maxNode->val << endl;

    return 0;
}
```

---

## 8. JavaScript Implementation

```javascript
function findMin(root) {
    if (root === null) return null;

    while (root.left !== null) {
        root = root.left;
    }
    return root;
}

function findMax(root) {
    if (root === null) return null;

    while (root.right !== null) {
        root = root.right;
    }
    return root;
}
```

---

## 9. Recursive Approach (For Understanding)

```cpp
TreeNode* findMin(TreeNode* root) {
    if (root == nullptr || root->left == nullptr)
        return root;
    return findMin(root->left);
}

TreeNode* findMax(TreeNode* root) {
    if (root == nullptr || root->right == nullptr)
        return root;
    return findMax(root->right);
}
```

---

## 10. Time & Space Complexity

### Time Complexity

* **O(H)** where H = height of BST
* Balanced BST → **O(log N)**
* Skewed BST → **O(N)**

---

### Space Complexity

* Iterative → **O(1)**
* Recursive → **O(H)** (call stack)

---

## 11. Common Mistakes

1. Traversing entire tree unnecessarily
2. Forgetting null check
3. Mixing up left/right direction
4. Returning value instead of node (when node is asked)

---

## 12. Interview-Level Q&A Synthesis

### Q1. Why is min always leftmost?

Because all smaller values lie on the left.

---

### Q2. Can we do better than O(H)?

No — we must at least go down one side.

---

### Q3. Is inorder traversal needed?

No — that would be **O(N)** (wasteful).

---

### Q4. What if tree is empty?

Return `null`.

---

### Q5. One-line intuition?

**Leftmost = Min, Rightmost = Max.**

---

## Key Takeaway

> BST ordering makes min/max a straight path problem, not a traversal problem.
