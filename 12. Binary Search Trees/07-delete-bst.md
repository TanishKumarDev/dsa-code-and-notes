# DELETE A NODE IN A BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. Why deletion is harder than search & insert
2. The **three deletion cases** (must remember)
3. Core idea: preserve BST property
4. Case-by-case intuition with diagrams
5. Inorder successor concept (key idea)
6. Recursive deletion approach (interview standard)
7. Step-by-step dry runs for all cases
8. C++ implementation (clean + deep commented)
9. JavaScript implementation
10. Time & space complexity
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. Why BST Deletion Is Tricky

Search and insert are **path-based**.
Delete is **structure-changing**.

When deleting a node:

* You **must not break** BST ordering
* You must **reconnect children correctly**
* Different node shapes need different handling

That’s why deletion has **cases**.

---

## 2. The 3 Deletion Cases (ABSOLUTELY IMPORTANT)

When you find the node to delete, check:

### Case 1: Node is a **Leaf Node**

```
   5
```

Just delete it → return `null`

---

### Case 2: Node has **One Child**

```
   5
    \
     7
```

Delete `5` → return `7` (child replaces parent)

---

### Case 3: Node has **Two Children**

```
        8
      /   \
     5     12
```

This is the **real problem case**.

---

## 3. Case 3 Core Idea (Interview Gold)

> Replace the node with a value that keeps BST valid

Two options:

* **Inorder Successor** → smallest in right subtree
* **Inorder Predecessor** → largest in left subtree

👉 We usually use **Inorder Successor**.

---

## 4. What Is Inorder Successor?

> The **smallest value** in the right subtree

How to find it:

* Go to `right`
* Then keep going `left` until `null`

---

### Example

```
        8
      /   \
     5     12
          /
        10
```

Inorder successor of `8` = **10**

---

## 5. High-Level Delete Algorithm

```
DELETE(root, key):

IF root is null:
    return null

IF key < root.val:
    root.left = DELETE(root.left, key)

ELSE IF key > root.val:
    root.right = DELETE(root.right, key)

ELSE:
    // Node found

    IF no left child:
        return root.right

    IF no right child:
        return root.left

    successor = minValue(root.right)
    root.val = successor
    root.right = DELETE(root.right, successor)

RETURN root
```

---

## 6. Dry Run — Case 1 (Leaf Node)

Delete `4`

```
        8
       /
      5
     /
    4
```

* Found node `4`
* No children
* Return `null`

---

## 7. Dry Run — Case 2 (One Child)

Delete `5`

```
    8
   /
  5
   \
    6
```

* Node has one child (`6`)
* Return child
* `6` replaces `5`

---

## 8. Dry Run — Case 3 (Two Children)

Delete `8`

```
        8
      /   \
     5     12
          /
        10
```

Steps:

1. Find inorder successor → `10`
2. Replace `8` with `10`
3. Delete `10` from right subtree

Final tree:

```
        10
      /    \
     5      12
```

---

## 9. C++ — Core Delete Function (Recursive)

### Version 1 — Required Function Only

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {

    if (root == nullptr) return nullptr;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // Node found

        // Case 1 & 2: One or zero child
        if (root->left == nullptr) return root->right;
        if (root->right == nullptr) return root->left;

        // Case 3: Two children
        TreeNode* succ = root->right;
        while (succ->left != nullptr) {
            succ = succ->left;
        }

        root->val = succ->val;
        root->right = deleteNode(root->right, succ->val);
    }

    return root;
}
```

---

## 10. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

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
    TreeNode* deleteNode(TreeNode* root, int key) {

        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // Node to delete found

            // Case 1: No left child
            if (root->left == nullptr) {
                return root->right;
            }

            // Case 2: No right child
            if (root->right == nullptr) {
                return root->left;
            }

            // Case 3: Two children
            TreeNode* successor = root->right;

            // Find inorder successor
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            // Replace value
            root->val = successor->val;

            // Delete successor node
            root->right = deleteNode(root->right, successor->val);
        }

        return root;
    }
};

int main() {

    /*
            8
          /   \
         5     12
        / \    /
       4   7  10
    */

    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(10);

    Solution sol;
    root = sol.deleteNode(root, 8);

    cout << "Deleted node 8 from BST" << endl;

    return 0;
}
```

---

## 11. JavaScript — Delete in BST

```javascript
function deleteNode(root, key) {

    if (root === null) return null;

    if (key < root.data) {
        root.left = deleteNode(root.left, key);
    }
    else if (key > root.data) {
        root.right = deleteNode(root.right, key);
    }
    else {
        // Node found

        if (root.left === null) return root.right;
        if (root.right === null) return root.left;

        let succ = root.right;
        while (succ.left !== null) {
            succ = succ.left;
        }

        root.data = succ.data;
        root.right = deleteNode(root.right, succ.data);
    }

    return root;
}
```

---

## 12. Time & Space Complexity

### Time Complexity

* **Average (balanced BST):** `O(log N)`
* **Worst (skewed):** `O(N)`

---

### Space Complexity

* Recursive stack → `O(H)`
* Iterative version possible but complex

---

## 13. Common Mistakes (DO NOT DO THESE)

1. Forgetting to delete successor
2. Replacing node pointer instead of value
3. Breaking BST order
4. Not returning updated root
5. Confusing successor & predecessor

---

## 14. Interview-Level Q&A Synthesis

### Q1. Why use inorder successor?

Because it preserves BST ordering naturally.

---

### Q2. Can we use predecessor?

Yes, largest value in left subtree.

---

### Q3. Why recursive preferred?

Clean handling of all cases.

---

### Q4. Hardest case?

Node with **two children**.

---

### Q5. One-line intuition?

**Search → Handle cases → Reconnect tree**

---

## Key Takeaway (LOCK THIS)

> **Delete = Search + Case handling + Structure repair**

If you master the **3 cases**, BST deletion becomes mechanical.
