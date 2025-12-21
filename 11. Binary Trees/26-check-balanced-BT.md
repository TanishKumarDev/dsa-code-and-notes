

# BINARY TREE — CHECK IF BALANCED BINARY TREE

---

## What We Covered Here

1. What a balanced binary tree means (exact definition)
2. Why height difference matters at **every node**
3. Brute force approach (O(N²)) — intuition & problem
4. Why brute force is inefficient
5. Optimal approach using postorder traversal (O(N))
6. Why `-1` is used as a signal
7. Step-by-step dry run (balanced & unbalanced)
8. C++ brute force implementation
9. C++ optimal implementation (deeply commented)
10. JavaScript optimal implementation
11. Time & space complexity comparison
12. Common mistakes and interview traps
13. Interview-level Q&A synthesis

---

## 1. What Is a Balanced Binary Tree?

**Definition (Very Important):**

A binary tree is **balanced** if:

> For **every node** in the tree,
> `| height(left subtree) - height(right subtree) | ≤ 1`

⚠️ This condition must hold **at all nodes**, not just the root.

---

### Balanced Example

```
        3
       / \
      9  20
         / \
        15  7
```

✔ Height difference ≤ 1 everywhere → **Balanced**

---

### Unbalanced Example

```
        1
       /
      2
       \
        3
```

❌ Height difference > 1 at node `1` → **Not Balanced**

---

## 2. Why This Problem Is Tricky

Most beginners check **only the root**.

That is **wrong**.

You must ensure:

* Root is balanced
* Left subtree is balanced
* Right subtree is balanced

So it’s a **recursive structural problem**.

---

# PART A — BRUTE FORCE APPROACH (O(N²))

---

## 3. Brute Force Idea (Clear Thinking)

For **every node**:

1. Compute height of left subtree
2. Compute height of right subtree
3. Check difference ≤ 1
4. Recursively check left & right subtrees

---

## 4. Brute Force Pseudocode

```
isBalanced(node):
    IF node == NULL:
        return true

    leftHeight = height(node.left)
    rightHeight = height(node.right)

    IF |leftHeight - rightHeight| > 1:
        return false

    return isBalanced(node.left) AND isBalanced(node.right)
```

---

## 5. Why Brute Force Is O(N²)

* `height()` itself is **O(N)**
* Called at **every node**
* Worst case (skewed tree):

```
O(N) height × N nodes = O(N²)
```

This **will TLE** for large trees.

---

## 6. Brute Force C++ Code (For Understanding Only)

```cpp
bool isBalanced(Node* root) {
    if (root == nullptr) return true;

    int lh = getHeight(root->left);
    int rh = getHeight(root->right);

    if (abs(lh - rh) > 1) return false;

    return isBalanced(root->left) && isBalanced(root->right);
}

int getHeight(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}
```

---

# PART B — OPTIMAL APPROACH (O(N)) ⭐

---

## 7. Key Insight (MOST IMPORTANT)

Height and balance **should be checked together**, not separately.

> Use **postorder traversal** (Left → Right → Root)

Why?

* Children heights must be known **before** parent.

---

## 8. Smart Trick Used

We return:

* **Height** → if subtree is balanced
* **-1** → if subtree is unbalanced

`-1` acts as a **failure signal**.

---

## 9. Optimal Algorithm (Step-by-Step)

```
dfsHeight(node):
    IF node == NULL:
        return 0

    left = dfsHeight(node.left)
    IF left == -1:
        return -1

    right = dfsHeight(node.right)
    IF right == -1:
        return -1

    IF |left - right| > 1:
        return -1

    return 1 + max(left, right)
```

Final check:

```
Tree is balanced if dfsHeight(root) != -1
```

---

## 10. Dry Run — Unbalanced Tree (Deep)

```
            1
           /
          2
           \
            3
             \
              4
```

Bottom-up:

| Node | Left | Right | Result          |
| ---- | ---- | ----- | --------------- |
| 4    | 0    | 0     | 1               |
| 3    | 0    | 1     | 2               |
| 2    | 0    | 2     | ❌ diff > 1 → -1 |
| 1    | -1   | —     | -1              |

Final result → **Not Balanced**

---

## 11. Dry Run — Balanced Tree

```
        3
       / \
      9  20
         / \
        15  7
```

| Node | Left | Right | Result |
| ---- | ---- | ----- | ------ |
| 9    | 0    | 0     | 1      |
| 15   | 0    | 0     | 1      |
| 7    | 0    | 0     | 1      |
| 20   | 1    | 1     | 2      |
| 3    | 1    | 2     | 3      |

✔ No `-1` → **Balanced**

---

## 12. C++ — Optimal Solution (Clean)

### Version 1 — Core Logic Only

```cpp
bool isBalanced(Node* root) {
    return dfsHeight(root) != -1;
}

int dfsHeight(Node* root) {
    if (root == nullptr) return 0;

    int lh = dfsHeight(root->left);
    if (lh == -1) return -1;

    int rh = dfsHeight(root->right);
    if (rh == -1) return -1;

    if (abs(lh - rh) > 1) return -1;

    return 1 + max(lh, rh);
}
```

---

## 13. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    bool isBalanced(Node* root) {
        return dfsHeight(root) != -1;
    }

    int dfsHeight(Node* root) {

        // Base case
        if (root == nullptr) return 0;

        // Check left subtree
        int leftHeight = dfsHeight(root->left);
        if (leftHeight == -1) return -1;

        // Check right subtree
        int rightHeight = dfsHeight(root->right);
        if (rightHeight == -1) return -1;

        // Check balance condition
        if (abs(leftHeight - rightHeight) > 1)
            return -1;

        // Return height
        return 1 + max(leftHeight, rightHeight);
    }
};

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->left->right = new Node(3);
    root->left->right->right = new Node(4);

    Solution sol;

    cout << (sol.isBalanced(root) ? "Balanced" : "Not Balanced");
    return 0;
}
```

---

## 14. JavaScript — Optimal Solution

```javascript
function isBalanced(root) {
    return dfsHeight(root) !== -1;
}

function dfsHeight(node) {
    if (node === null) return 0;

    let left = dfsHeight(node.left);
    if (left === -1) return -1;

    let right = dfsHeight(node.right);
    if (right === -1) return -1;

    if (Math.abs(left - right) > 1) return -1;

    return 1 + Math.max(left, right);
}
```

---

## 15. Complexity Comparison (Very Important)

| Approach    | Time  | Space |
| ----------- | ----- | ----- |
| Brute Force | O(N²) | O(H)  |
| Optimal     | O(N)  | O(H)  |

⚠️ Always discuss **optimal approach in interviews**.

---

## 16. Common Mistakes (Interview Traps)

1. Checking balance only at root
2. Calling height separately for every node
3. Forgetting `abs()`
4. Returning `false` instead of `-1` in helper
5. Using preorder instead of postorder

---

## 17. Interview-Level Q&A Synthesis

### Q1. Why postorder traversal?

Because height is needed **before** checking balance.

---

### Q2. Why return `-1`?

To propagate unbalanced state early.

---

### Q3. Can BFS be used?

Yes, but DFS is simpler and optimal.

---

### Q4. Height-balanced vs BST?

Different concepts — **do not confuse**.

---

### Q5. Does balanced mean complete?

❌ No. Balanced ≠ Complete.

---

## Key Takeaway (LOCK THIS)

> **Balanced Tree = Height(left) and Height(right) differ by ≤ 1 at EVERY node**
> Best solved using **postorder + height propagation**.
