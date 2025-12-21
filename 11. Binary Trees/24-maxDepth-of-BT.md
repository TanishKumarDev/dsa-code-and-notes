# BINARY TREE — MAXIMUM DEPTH (HEIGHT)

---

## What We Covered Here

1. What height / depth of a binary tree means
2. Difference between height and levels (important clarity)
3. Why height problems are naturally recursive
4. Recursive DFS approach (most common)
5. How `max(left, right)` works conceptually
6. Step-by-step dry run (very deep)
7. C++ recursive implementation (clean + deeply commented)
8. JavaScript recursive implementation
9. Time & space complexity (balanced vs skewed tree)
10. Common mistakes and interview traps
11. Interview-level Q&A synthesis

---

## 1. What Is the Height (Maximum Depth) of a Binary Tree?

**Definition (Very Important):**

> The height (or maximum depth) of a binary tree is
> **the number of nodes on the longest path from the root to any leaf node**.

---

### Simple Examples

* Empty tree → height = `0`
* Single node → height = `1`

---

## 2. Visual Understanding (Must Be Clear)

Example tree:

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
1 → 2 → 5 → 6 → 7
```

Number of nodes on this path = **5**

So:

```
Height = 5
```

---

## 3. Height vs Levels (Interview Trap)

Many people get confused here.

* **Height / Depth** → number of nodes in longest root-to-leaf path
* **Levels** → also counted as number of layers from top to bottom

In most DSA problems:

> **Height = number of levels = number of nodes in longest path**

---

## 4. Why Height Is a Recursive Problem (Key Insight)

At any node:

* Height depends on:

  * Height of left subtree
  * Height of right subtree

So naturally:

> Height of tree =
> `1 + max(height(left), height(right))`

This exact relation defines the recursion.

---

## 5. Recursive Algorithm (Clear Thinking)

### Base Case

* If node is `null` → height = `0`

### Recursive Case

1. Compute height of left subtree
2. Compute height of right subtree
3. Take maximum of both
4. Add `1` for current node

---

## 6. Pseudocode (Before Code)

```
MAX_DEPTH(node):
    IF node is NULL:
        return 0

    leftHeight = MAX_DEPTH(node.left)
    rightHeight = MAX_DEPTH(node.right)

    return 1 + max(leftHeight, rightHeight)
```

This pseudocode is **the entire solution**.

---

## 7. Dry Run — Step by Step (Very Deep)

Using this tree:

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

### Bottom-Up Calculation (Important Concept)

| Node | Left Height | Right Height | Height Returned |
| ---- | ----------- | ------------ | --------------- |
| 4    | 0           | 0            | 1               |
| 7    | 0           | 0            | 1               |
| 6    | 0           | 1            | 2               |
| 5    | 0           | 2            | 3               |
| 2    | 1           | 3            | 4               |
| 3    | 0           | 0            | 1               |
| 1    | 4           | 1            | 5               |

Final Answer:

```
Height = 5
```

---

### Call Stack Visualization

```
maxDepth(1)
 ├── maxDepth(2)
 │    ├── maxDepth(4)
 │    │    ├── maxDepth(NULL) → 0
 │    │    └── maxDepth(NULL) → 0
 │    │    → returns 1
 │    ├── maxDepth(5)
 │    │    ├── maxDepth(NULL) → 0
 │    │    └── maxDepth(6)
 │    │         └── ...
 │    │         → returns 3
 │    → returns 4
 ├── maxDepth(3) → returns 1
 → returns 5
```

This explains **why recursion works bottom-up**.

---

## 8. C++ — Maximum Depth (Core Logic)

### Version 1 — Only Required Function

```cpp
int maxDepth(Node* root) {
    if (root == nullptr) return 0;

    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);

    return 1 + max(lh, rh);
}
```

---

## 9. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Node structure for the binary tree
struct Node {
    int data;          // Value of node
    Node* left;        // Left child
    Node* right;       // Right child

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    int maxDepth(Node* root) {

        // Base case:
        // If tree is empty, depth is 0
        if (root == nullptr) {
            return 0;
        }

        // Recursively find height of left subtree
        int leftHeight = maxDepth(root->left);

        // Recursively find height of right subtree
        int rightHeight = maxDepth(root->right);

        // Height of current node =
        // 1 (current node) + max of both subtrees
        return 1 + max(leftHeight, rightHeight);
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
                \
                 6
                  \
                   7
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);

    Solution sol;
    int depth = sol.maxDepth(root);

    cout << "Maximum depth of the binary tree: " << depth << endl;

    return 0;
}
```

---

## 10. JavaScript — Maximum Depth (Recursive)

```javascript
function maxDepth(root) {
    if (root === null) return 0;

    let leftHeight = maxDepth(root.left);
    let rightHeight = maxDepth(root.right);

    return 1 + Math.max(leftHeight, rightHeight);
}
```

---

## 11. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

Why?

* Every node is visited exactly once
* Constant work per node

So:

```
Time = O(N)
```

---

### Space Complexity — **O(H)**

Why?

* Recursion stack stores nodes along one path
* Maximum stack depth = height of tree

Cases:

* Balanced tree → **O(log N)**
* Skewed tree → **O(N)**

Interview-safe answer:

```
Space = O(H)
```

---

## 12. Common Mistakes (Interview Traps)

1. Returning `max(lh, rh)` instead of `1 + max(lh, rh)`
2. Returning `-1` for null node (wrong definition)
3. Confusing height with number of edges
4. Forgetting base case

---

## 13. Interview-Level Q&A Synthesis

### Q1. Why is height computed bottom-up?

Because child heights must be known before parent.

---

### Q2. Can height be calculated using BFS?

Yes — count number of levels (we’ll do later).

---

### Q3. Height of empty tree?

`0`

---

### Q4. Height of single node tree?

`1`

---

### Q5. Is height same as depth?

Yes, in most DSA problems (unless specified otherwise).

---

## Key Takeaway (Lock This)

> **Height of tree = 1 + max(left subtree height, right subtree height)**
> If this formula is clear, **half of tree problems become easy**.
