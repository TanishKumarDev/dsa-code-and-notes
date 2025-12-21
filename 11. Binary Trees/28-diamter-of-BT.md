# BINARY TREE — DIAMETER OF A BINARY TREE

---

## What We Covered Here

1. What diameter of a binary tree really means
2. Common confusion: diameter vs height
3. Why diameter may or may not pass through root
4. Brute force approach (O(N²)) — intuition & flaw
5. Why brute force recalculates height again and again
6. Optimal postorder approach (O(N))
7. Why diameter is computed using heights
8. Step-by-step dry run (very deep)
9. C++ brute force implementation
10. C++ optimal implementation (clean + deeply commented)
11. JavaScript optimal implementation
12. Time & space complexity comparison
13. Common mistakes and interview traps
14. Interview-level Q&A synthesis

---

## 1. What Is Diameter of a Binary Tree?

**Definition (Very Important):**

> The **diameter** of a binary tree is the
> **longest distance between any two nodes** in the tree.

⚠️ The path:

* **does NOT need to pass through the root**
* can be anywhere in the tree

---

### Distance Means What?

In most DSA problems (including TakeUForward):

> **Distance = number of edges between two nodes**

So if path has:

* 5 nodes → diameter = 4

---

## 2. Visual Understanding

Example:

```
            1
          /   \
         2     3
        / \
       4   5
            \
             6
              \
               7
```

Longest path:

```
4 → 2 → 5 → 6 → 7
```

Number of edges = **4**

So:

```
Diameter = 4
```

---

## 3. Diameter vs Height (Interview Trap)

| Concept  | Meaning                            |
| -------- | ---------------------------------- |
| Height   | Longest path from root to leaf     |
| Diameter | Longest path between ANY two nodes |

They are **related but NOT the same**.

---

## 4. Key Observation (Foundation)

At **any node**:

> The longest path **passing through that node** is:

```
height(left subtree) + height(right subtree)
```

This node acts as a **turning point**.

---

# PART A — BRUTE FORCE APPROACH (O(N²))

---

## 5. Brute Force Idea

For **every node**:

1. Treat it as a turning point
2. Compute height of left subtree
3. Compute height of right subtree
4. Diameter at that node = `leftHeight + rightHeight`
5. Keep maximum

---

## 6. Brute Force Pseudocode

```
FOR each node:
    leftHeight = height(left)
    rightHeight = height(right)
    diameter = max(diameter, leftHeight + rightHeight)
```

---

## 7. Why Brute Force Is O(N²)

* `height()` takes **O(N)** in worst case
* Called at **every node**

So:

```
O(N) × N = O(N²)
```

This **will TLE** for large trees.

---

## 8. Brute Force C++ Code (For Understanding)

```cpp
int diameter = 0;

int height(Node* node) {
    if (node == nullptr) return 0;

    int lh = height(node->left);
    int rh = height(node->right);

    diameter = max(diameter, lh + rh);

    return 1 + max(lh, rh);
}
```

---

# PART B — OPTIMAL APPROACH (O(N)) ⭐⭐⭐

---

## 9. Key Insight (MOST IMPORTANT)

We already learned:

* Height is computed using **postorder**
* Diameter depends on **height**

So:

> **Compute height and diameter together in one traversal**

---

## 10. Optimal Strategy (Postorder)

We do **postorder traversal**:

```
Left → Right → Root
```

At each node:

1. Get left height
2. Get right height
3. Update diameter
4. Return height to parent

Each node is processed **once**.

---

## 11. Optimal Algorithm (Clean)

```
height(node):
    IF node == NULL:
        return 0

    lh = height(node.left)
    rh = height(node.right)

    diameter = max(diameter, lh + rh)

    return 1 + max(lh, rh)
```

---

## 12. Deep Dry Run (Step-by-Step)

Tree:

```
            1
          /   \
         2     3
        / \
       4   5
            \
             6
              \
               7
```

---

### Bottom-Up Table

| Node | Left Height | Right Height | Diameter Update | Height Returned |
| ---- | ----------- | ------------ | --------------- | --------------- |
| 4    | 0           | 0            | 0               | 1               |
| 7    | 0           | 0            | 0               | 1               |
| 6    | 0           | 1            | 1               | 2               |
| 5    | 0           | 2            | 2               | 3               |
| 2    | 1           | 3            | 4 ⭐             | 4               |
| 3    | 0           | 0            | 4               | 1               |
| 1    | 4           | 1            | 5 (ignored)     | 5               |

Final diameter = **4**

---

### Why Diameter Did NOT Update at Root?

Because:

```
max(4, 1) = 4
```

So the longest path **does not pass through root**.

---

## 13. C++ — Optimal Solution (Core Logic)

### Version 1 — Required Functions Only

```cpp
int diameterOfBinaryTree(Node* root) {
    int diameter = 0;
    height(root, diameter);
    return diameter;
}

int height(Node* node, int& diameter) {
    if (node == nullptr) return 0;

    int lh = height(node->left, diameter);
    int rh = height(node->right, diameter);

    diameter = max(diameter, lh + rh);

    return 1 + max(lh, rh);
}
```

---

## 14. C++ — Full Program (Deep Commented)

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
    int diameterOfBinaryTree(Node* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }

private:
    int height(Node* node, int& diameter) {

        // Base case
        if (node == nullptr) {
            return 0;
        }

        // Height of left subtree
        int leftHeight = height(node->left, diameter);

        // Height of right subtree
        int rightHeight = height(node->right, diameter);

        // Update diameter at this node
        diameter = max(diameter, leftHeight + rightHeight);

        // Return height to parent
        return 1 + max(leftHeight, rightHeight);
    }
};

int main() {

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);

    Solution sol;
    cout << "Diameter: " << sol.diameterOfBinaryTree(root);

    return 0;
}
```

---

## 15. JavaScript — Optimal Solution

```javascript
function diameterOfBinaryTree(root) {
    let diameter = 0;

    function height(node) {
        if (node === null) return 0;

        let lh = height(node.left);
        let rh = height(node.right);

        diameter = Math.max(diameter, lh + rh);

        return 1 + Math.max(lh, rh);
    }

    height(root);
    return diameter;
}
```

---

## 16. Complexity Comparison

| Approach    | Time  | Space |
| ----------- | ----- | ----- |
| Brute Force | O(N²) | O(H)  |
| Optimal     | O(N)  | O(H)  |

⚠️ Always explain **optimal approach** in interviews.

---

## 17. Common Mistakes (Interview Traps)

1. Returning `lh + rh + 1` as diameter (wrong)
2. Confusing nodes count vs edges count
3. Thinking diameter always passes through root
4. Using preorder instead of postorder
5. Recalculating height separately

---

## 18. Interview-Level Q&A Synthesis

### Q1. Why postorder traversal?

Because height of children must be known first.

---

### Q2. Can diameter be computed using BFS?

Yes, but DFS is simpler and optimal.

---

### Q3. Diameter in terms of nodes?

Then answer = `edges + 1`

---

### Q4. Is diameter related to balanced tree?

Yes, both depend on height, but they solve different problems.

---

### Q5. One-liner intuition?

**At every node, longest path = left height + right height**

---

## Key Takeaway (LOCK THIS)

> **Diameter is not about root — it’s about the widest turning point anywhere in the tree**
> Best solved using **postorder + height reuse**.

