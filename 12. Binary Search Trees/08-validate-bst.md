# VALIDATE A BINARY SEARCH TREE (BST)

---

## What We Covered Here

1. What does “valid BST” **actually** mean (strict rules)
2. Why naive checks fail (common interview trap)
3. Correct mental model: **range propagation**
4. Recursive validation using min–max bounds
5. Dry run (step-by-step) on valid and invalid trees
6. C++ solution (clean + deep commented)
7. JavaScript solution
8. Time & space complexity
9. Common mistakes interviewers look for
10. Interview-level Q&A synthesis

---

## 1. What Is a Valid BST? (Precise Definition)

For **every node** in the tree:

```
All nodes in LEFT subtree  <  current node
All nodes in RIGHT subtree >  current node
```

Important points:

* This rule applies **recursively**
* Not just parent–child, but **entire subtree**
* Usually **no duplicates** allowed (strict `<` and `>`)

---

## 2. The BIGGEST Interview Trap ❌

### ❌ Wrong Thinking (Most Candidates)

> “I’ll just check
> left child < node < right child”

Example:

```
        10
       /  \
      5    15
          /
         6
```

Check locally:

* 6 < 15 → OK
* 6 > 10 ❌ (but naive check misses this)

This tree is **NOT a BST**, but local checks will say “valid”.

👉 **This is why many people fail.**

---

## 3. Correct Mental Model (Very Important)

> Every node must lie in a **valid value range**

Instead of checking with parent only, we do:

```
Node must satisfy:
min < node.val < max
```

And we **update this range** as we go down the tree.

---

## 4. Range Propagation Logic

At root:

```
(-∞ , +∞)
```

For left child:

```
(min , current.val)
```

For right child:

```
(current.val , max)
```

This guarantees **global correctness**, not local.

---

## 5. Algorithm (Recursive, Interview-Standard)

```
IS_VALID(node, min, max):

IF node is null:
    return true

IF node.val <= min OR node.val >= max:
    return false

return
    IS_VALID(node.left, min, node.val)
    AND
    IS_VALID(node.right, node.val, max)
```

---

## 6. Dry Run — Valid BST

```
        8
      /   \
     4     12
    / \    / \
   2   6  10 14
```

Start:

```
8 in (-∞, +∞) ✔
```

Left:

```
4 in (-∞, 8) ✔
6 in (4, 8) ✔
```

Right:

```
12 in (8, +∞) ✔
10 in (8, 12) ✔
```

Result → **Valid BST**

---

## 7. Dry Run — Invalid BST (Interview Favorite)

```
        10
       /  \
      5    15
          /
         6
```

Check `6`:

```
Allowed range: (10, 15)
6 < 10 ❌
```

Immediately return **false**.

---

## 8. C++ Solution

### Version 1 — Required Function Only

```cpp
bool validate(TreeNode* root, long minVal, long maxVal) {

    if (root == nullptr) return true;

    if (root->val <= minVal || root->val >= maxVal)
        return false;

    return validate(root->left, minVal, root->val) &&
           validate(root->right, root->val, maxVal);
}

bool isValidBST(TreeNode* root) {
    return validate(root, LONG_MIN, LONG_MAX);
}
```

---

### Version 2 — Full Program (Deep Commented)

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
    bool isValidBST(TreeNode* root) {
        return check(root, LONG_MIN, LONG_MAX);
    }

private:
    bool check(TreeNode* node, long minVal, long maxVal) {

        // Empty tree is valid
        if (node == nullptr) {
            return true;
        }

        // Current node must lie in (min, max)
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }

        // Left subtree: max bound becomes current value
        // Right subtree: min bound becomes current value
        return check(node->left, minVal, node->val) &&
               check(node->right, node->val, maxVal);
    }
};

int main() {

    /*
            10
           /  \
          5    15
              /
             6   -> INVALID BST
    */

    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(6);

    Solution sol;

    if (sol.isValidBST(root))
        cout << "Valid BST" << endl;
    else
        cout << "Invalid BST" << endl;

    return 0;
}
```

---

## 9. JavaScript Solution

```javascript
function isValidBST(root) {

    function validate(node, min, max) {
        if (node === null) return true;

        if (node.data <= min || node.data >= max)
            return false;

        return validate(node.left, min, node.data) &&
               validate(node.right, node.data, max);
    }

    return validate(root, -Infinity, Infinity);
}
```

---

## 10. Time & Space Complexity

### Time Complexity

* **O(N)**
  Every node is visited once.

---

### Space Complexity

* **O(H)** recursion stack
  H = height of tree
  Worst case (skewed): O(N)
  Best case (balanced): O(log N)

---

## 11. Common Mistakes (Very Important)

1. ❌ Checking only immediate children
2. ❌ Using `INT_MIN / INT_MAX` instead of `LONG_MIN / LONG_MAX`
3. ❌ Allowing duplicates accidentally
4. ❌ Forgetting strict inequality
5. ❌ Not passing updated bounds correctly

Interviewers **expect** you to avoid these.

---

## 12. Interview-Level Q&A Synthesis

### Q1. Why not check only left < root < right?

Because violations can exist **deep in subtrees**.

---

### Q2. Why min–max method works?

It enforces **global BST constraints**, not local.

---

### Q3. Can inorder traversal validate BST?

Yes (array must be strictly sorted),
but **range method is preferred** (O(1) extra space).

---

### Q4. What about duplicates?

Depends on definition.
Most problems expect **no duplicates**.

---

### Q5. One-line intuition?

**Every node must respect the range decided by its ancestors.**

---

## Key Takeaway (Lock This)

> **BST validity is about ranges, not neighbors.**

If you say this line in interviews, it’s a green flag.
