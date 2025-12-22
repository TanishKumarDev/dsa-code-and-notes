# FLOOR IN A BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. What “Floor” means in BST (exact definition)
2. Why BST ordering makes floor efficient
3. Core intuition (thinking before coding)
4. Step-by-step algorithm
5. Detailed dry run (pointer movement)
6. Iterative approach (interview preferred)
7. Recursive alternative (conceptual)
8. C++ code (clean + deeply commented)
9. JavaScript code (same logic)
10. Time & space complexity
11. Common mistakes
12. Interview-level Q&A synthesis

---

## 1. What Is Floor in a BST?

**Floor of a key `X`** =
👉 **Largest value in the BST such that value ≤ X**

If **no such value exists**, return **-1 / nullptr**.

---

### Simple Example (Inorder of BST)

```
2 3 4 5 6 9 10 11 13 14
```

| Key | Floor |
| --- | ----- |
| 8   | 6     |
| 5   | 5     |
| 1   | -1    |
| 15  | 14    |

---

## 2. Why BST Makes Floor Easy

BST property:

```
Left subtree  <  Node  <  Right subtree
```

So:

* If key is **greater** than node → node is a **possible floor**
* If key is **smaller** → floor must be on the **left**

No need to scan all nodes.

---

## 3. Core Intuition (MOST IMPORTANT)

> **While searching for the key, keep remembering the best smaller value.**

This is the **mirror logic of Ceil**.

---

## 4. Step-by-Step Thinking

At every node:

1. If `node.val == key`

   * Exact match → **floor found**
   * Return immediately

2. If `key > node.val`

   * Current node is a **candidate floor**
   * Store it
   * Move **right** (to find bigger valid floor)

3. If `key < node.val`

   * Floor must be **smaller**
   * Move **left**

---

## 5. Pseudocode (Mindset First)

```
floor = -1
current = root

WHILE current != null:
    IF current.value == key:
        floor = current.value
        BREAK
    ELSE IF key > current.value:
        floor = current.value
        current = current.right
    ELSE:
        current = current.left

RETURN floor
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

| Step | Node | Comparison | Floor | Move  |
| ---- | ---- | ---------- | ----- | ----- |
| 1    | 10   | 8 < 10     | -1    | Left  |
| 2    | 5    | 8 > 5      | 5     | Right |
| 3    | 6    | 8 > 6      | 6     | Right |
| 4    | 9    | 8 < 9      | 6     | Left  |
| 5    | null | stop       | 6     | —     |

**Answer: 6**

---

## 7. C++ Code — Required Function (Clean)

```cpp
int findFloor(TreeNode* root, int key) {
    int floor = -1;

    while (root != nullptr) {

        // Exact match
        if (root->val == key) {
            return root->val;
        }

        // Possible floor found
        if (key > root->val) {
            floor = root->val;
            root = root->right;
        }
        // Move left to find smaller values
        else {
            root = root->left;
        }
    }

    return floor;
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
    int findFloor(TreeNode* root, int key) {

        int floor = -1; // stores best answer so far

        while (root != nullptr) {

            // Case 1: exact match
            if (root->val == key) {
                return root->val;
            }

            // Case 2: key is greater → possible floor
            if (key > root->val) {
                floor = root->val;
                root = root->right;
            }
            // Case 3: key is smaller → move left
            else {
                root = root->left;
            }
        }

        return floor;
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

    cout << "Floor of " << key << " is: "
         << sol.findFloor(root, key) << endl;

    return 0;
}
```

---

## 9. JavaScript Code (Same Logic)

```javascript
function findFloor(root, key) {
    let floor = -1;

    while (root !== null) {

        if (root.data === key) {
            return root.data;
        }

        if (key > root.data) {
            floor = root.data;
            root = root.right;
        } else {
            root = root.left;
        }
    }

    return floor;
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

1. Updating floor when moving left ❌
2. Mixing ceil and floor logic ❌
3. Full inorder traversal ❌
4. Forgetting exact match case ❌

---

## 12. Interview-Level Q&A Synthesis

### Q1. Difference between Floor and Ceil?

* Floor → nearest **smaller or equal**
* Ceil → nearest **greater or equal**

---

### Q2. Why update floor only when moving right?

Because only then `node.val ≤ key`.

---

### Q3. Can recursion be used?

Yes, but iterative is simpler and O(1) space.

---

### Q4. One-line intuition?

> **Search like BST, remember the last smaller value.**

---

## Final Lock-in Insight

> **Floor and Ceil are mirror problems.
> Understand one → the other becomes trivial.**

