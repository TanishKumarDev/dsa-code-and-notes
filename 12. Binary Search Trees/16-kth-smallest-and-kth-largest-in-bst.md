# Kth Smallest & Kth Largest Element in a BST

---

## What We Covered Here

1. Problem breakdown (what exactly is asked)
2. Core BST property used in this problem
3. Why **inorder traversal** gives sorted order
4. Brute force approach (store all values)
5. Optimal approach (no extra storage)
6. Kth smallest using inorder
7. Kth largest using reverse inorder
8. Step-by-step dry run (both)
9. C++ code (clean + deep commented)
10. JavaScript code
11. Time & space complexity
12. Common mistakes
13. Interview-level Q&A synthesis

---

## 1. Problem Restatement (Very Clear)

Given:

* Root of a **Binary Search Tree**
* An integer `k` (1-indexed)

You need to return:

* **kth smallest element**
* **kth largest element**

As an array:

```
[kthSmallest, kthLargest]
```

---

## 2. Core BST Property Used

The **single most important property**:

> **Inorder traversal of a BST gives values in sorted (ascending) order**

```
Inorder → Left → Root → Right
```

Example BST:

```
        5
       / \
      3   7
     / \   \
    2   4   8
```

Inorder traversal:

```
[2, 3, 4, 5, 7, 8]
```

---

## 3. Why This Problem Is Easy *Because* It Is a BST

If this were a **normal Binary Tree**:

* No order
* You must sort manually

But BST gives:

* Sorted order naturally via traversal

That’s the shortcut.

---

## 4. Brute Force Approach (Baseline Thinking)

### Idea

1. Do **inorder traversal**
2. Store all node values in a vector
3. Since inorder is sorted:

   * kth smallest → `arr[k-1]`
   * kth largest → `arr[n-k]`

---

### Pseudocode (Brute Force)

```
values = []

INORDER(root):
    if root is null: return
    INORDER(root.left)
    values.push(root.data)
    INORDER(root.right)

kthSmallest = values[k-1]
kthLargest  = values[values.size - k]
```

---

### Brute Force C++ Code

```cpp
void inorderTraversal(TreeNode* root, vector<int>& values) {
    if (!root) return;

    inorderTraversal(root->left, values);
    values.push_back(root->data);
    inorderTraversal(root->right, values);
}

vector<int> kLargesSmall(TreeNode* root, int k) {
    vector<int> values;
    inorderTraversal(root, values);

    return { values[k - 1], values[values.size() - k] };
}
```

---

### Complexity (Brute Force)

* **Time:** `O(N)`
* **Space:** `O(N)` (extra array)

⚠️ Interviewers usually ask:

> “Can you do it without storing all elements?”

---

## 5. Optimal Approach (Interview Expected)

We **do not store all values**.

Instead:

* Use a **counter**
* Stop traversal when `k` is reached

---

## 6. Kth Smallest (Inorder Traversal)

### Why Inorder?

Because inorder = sorted ascending.

---

### Logic

1. Traverse Left
2. Visit Node → decrement `k`
3. If `k == 0` → this node is answer
4. Traverse Right

---

### Dry Run (Kth Smallest)

BST:

```
        5
       / \
      3   7
     / \
    2   4
```

k = 3

Inorder sequence:

```
2 → 3 → 4 → 5 → 7
```

| Visit | Node | k after decrement |
| ----- | ---- | ----------------- |
| 1     | 2    | 2                 |
| 2     | 3    | 1                 |
| 3     | 4    | 0 ← answer        |

✔ Kth smallest = **4**

---

### C++ — Kth Smallest (Optimal)

```cpp
int k;
int ans;

void inorder(TreeNode* root) {
    if (!root || k == 0) return;

    inorder(root->left);

    k--;
    if (k == 0) {
        ans = root->data;
        return;
    }

    inorder(root->right);
}

int kthSmallest(TreeNode* root, int K) {
    k = K;
    ans = -1;
    inorder(root);
    return ans;
}
```

---

## 7. Kth Largest (Reverse Inorder Traversal)

### Why Reverse Inorder?

Reverse inorder:

```
Right → Root → Left
```

This gives **descending order**.

---

### Dry Run (Kth Largest)

Same BST:

```
Inorder:        2 3 4 5 7
Reverse inorder 7 5 4 3 2
```

k = 2

| Visit | Node | k          |
| ----- | ---- | ---------- |
| 1     | 7    | 1          |
| 2     | 5    | 0 ← answer |

✔ Kth largest = **5**

---

### C++ — Kth Largest

```cpp
void reverseInorder(TreeNode* root) {
    if (!root || k == 0) return;

    reverseInorder(root->right);

    k--;
    if (k == 0) {
        ans = root->data;
        return;
    }

    reverseInorder(root->left);
}

int kthLargest(TreeNode* root, int K) {
    k = K;
    ans = -1;
    reverseInorder(root);
    return ans;
}
```

---

## 8. Combined Function (Final Answer)

```cpp
vector<int> kLargesSmall(TreeNode* root, int k) {
    int smallest = kthSmallest(root, k);
    int largest  = kthLargest(root, k);
    return {smallest, largest};
}
```

---

## 9. JavaScript Version (Optimal)

```javascript
function kthSmallest(root, k) {
    let count = 0;
    let result = null;

    function inorder(node) {
        if (!node || result !== null) return;

        inorder(node.left);
        count++;

        if (count === k) {
            result = node.data;
            return;
        }

        inorder(node.right);
    }

    inorder(root);
    return result;
}
```

---

## 10. Time & Space Complexity (Optimal)

### Time

* Worst case: `O(N)`
* Best case (early stop): `< O(N)`

### Space

* `O(H)` recursion stack
* No extra array

---

## 11. Common Mistakes (Very Important)

1. Forgetting BST inorder property
2. Using array when not required
3. Off-by-one error (`k-1`)
4. Not stopping recursion early
5. Mixing inorder and reverse inorder

---

## 12. Interview-Level Q&A Synthesis

### Q1. Why inorder gives sorted order?

Because BST enforces left < root < right.

---

### Q2. Can we do it iteratively?

Yes, using stack (same logic).

---

### Q3. Why space is O(H)?

Due to recursion stack, not extra storage.

---

### Q4. Can this work in normal Binary Tree?

No. Ordering is required.

---

### Q5. One-line intuition?

> **BST inorder = sorted array without sorting**

---

## Final Key Takeaway

> If a problem asks **kth smallest/largest**
> and the structure is **BST**
> → Think **inorder / reverse inorder immediately**
