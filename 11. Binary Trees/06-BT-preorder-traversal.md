# BINARY TREE — PREORDER TRAVERSAL (DFS)

---

## What We Covered Here

1. What traversal means in a Binary Tree
2. Why recursion fits naturally with trees
3. Definition of Preorder Traversal (Root → Left → Right)
4. Recursive algorithm for preorder traversal
5. Base case and recursive case clarity
6. Step-by-step dry run (node by node)
7. C++ implementation (clean + deep commented)
8. JavaScript implementation (clean + deep commented)
9. Role of recursion stack in traversal
10. Time and space complexity (why O(N))
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. What Is Tree Traversal? (Mindset First)

**Traversal** means:

> Visiting **every node exactly once** in a specific order.

Unlike arrays:

* No index
* No linear order

So traversal defines **how we move** through the tree.

---

## 2. Why Traversal Needs a Strategy

In a tree:

* Each node has **two directions**

  * Left
  * Right

So we must decide:

* When to process the current node?
* When to go left?
* When to go right?

This decision gives us **Traversal Types**.

---

## 3. Preorder Traversal — Definition (Lock This)

### Preorder Order

```
ROOT → LEFT → RIGHT
```

Meaning:

1. Visit the current node
2. Traverse left subtree
3. Traverse right subtree

> **Root is processed BEFORE its children**

---

## 4. Why Recursion Is Natural for Trees

A tree is made of **subtrees**.

Each subtree is:

* Again a tree
* With its own root, left, and right

So the same logic repeats.

> Tree + recursion = perfect match

---

## 5. Recursive Algorithm (Clear Thinking)

### At any node `root`:

1. If `root == null`

   * Stop (base case)
2. Process current node
3. Recurse on left child
4. Recurse on right child

---

## 6. Pseudocode (Before Any Code)

```
PREORDER(node):
    IF node is NULL:
        return

    visit(node)
    PREORDER(node.left)
    PREORDER(node.right)
```

This pseudocode alone can solve **90% tree problems**.

---

## 7. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
        / \
       4   5
```

---

## 8. Dry Run — Step by Step (Very Deep)

We start at **root = 1**

### Step-by-Step Table

| Step | Current Node | Action Taken        | Output Array    |
| ---- | ------------ | ------------------- | --------------- |
| 1    | 1            | Visit root          | [1]             |
| 2    | 2            | Go left, visit      | [1, 2]          |
| 3    | 4            | Go left, visit      | [1, 2, 4]       |
| 4    | NULL         | Left of 4 → return  | [1, 2, 4]       |
| 5    | NULL         | Right of 4 → return | [1, 2, 4]       |
| 6    | 5            | Right of 2, visit   | [1, 2, 4, 5]    |
| 7    | NULL         | Left of 5 → return  | [1, 2, 4, 5]    |
| 8    | NULL         | Right of 5 → return | [1, 2, 4, 5]    |
| 9    | 3            | Right of 1, visit   | [1, 2, 4, 5, 3] |

---

### Call Stack Visualization (Very Important)

```
preorder(1)
 ├── preorder(2)
 │    ├── preorder(4)
 │    │    ├── preorder(NULL)
 │    │    └── preorder(NULL)
 │    └── preorder(5)
 │         ├── preorder(NULL)
 │         └── preorder(NULL)
 └── preorder(3)
      ├── preorder(NULL)
      └── preorder(NULL)
```

This explains **why recursion works**.

---

## 9. C++ Code — Core Logic (Clean Version)

### Version 1 — Only Required Functions

```cpp
void preorder(Node* root, vector<int>& arr) {
    if (root == nullptr)
        return;

    arr.push_back(root->data);
    preorder(root->left, arr);
    preorder(root->right, arr);
}

vector<int> preOrder(Node* root) {
    vector<int> arr;
    preorder(root, arr);
    return arr;
}
```

---

## 10. C++ Code — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Node structure for Binary Tree
struct Node {
    int data;        // Value of node
    Node* left;      // Pointer to left child
    Node* right;     // Pointer to right child

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Solution class
class Solution {
public:
    // Recursive preorder traversal
    void preorder(Node* root, vector<int>& arr) {

        // Base case:
        // If node is NULL, stop recursion
        if (root == nullptr) {
            return;
        }

        // Step 1: Visit root
        arr.push_back(root->data);

        // Step 2: Traverse left subtree
        preorder(root->left, arr);

        // Step 3: Traverse right subtree
        preorder(root->right, arr);
    }

    // Function called by user
    vector<int> preOrder(Node* root) {
        vector<int> arr;          // Stores traversal result
        preorder(root, arr);      // Start recursion
        return arr;
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
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    Solution sol;
    vector<int> result = sol.preOrder(root);

    cout << "Preorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
```

---

## 11. JavaScript Code — Clean Version

```javascript
function preorder(root, result) {
    if (root === null) return;

    result.push(root.data);
    preorder(root.left, result);
    preorder(root.right, result);
}

function preOrder(root) {
    let result = [];
    preorder(root, result);
    return result;
}
```

---

## 12. JavaScript Code — Full & Explained

```javascript
class Node {
    constructor(data) {
        this.data = data;     // Node value
        this.left = null;     // Left child
        this.right = null;    // Right child
    }
}

function preorder(root, result) {

    // Base case
    if (root === null) {
        return;
    }

    // Visit root
    result.push(root.data);

    // Traverse left subtree
    preorder(root.left, result);

    // Traverse right subtree
    preorder(root.right, result);
}

function preOrder(root) {
    let result = [];
    preorder(root, result);
    return result;
}

// Tree creation
let root = new Node(1);
root.left = new Node(2);
root.right = new Node(3);
root.left.left = new Node(4);
root.left.right = new Node(5);

console.log(preOrder(root)); // [1, 2, 4, 5, 3]
```

---

## 13. Time & Space Complexity (Deep Why)

### Time Complexity — **O(N)**

Why?

* Every node is visited **exactly once**
* Each visit does constant work

So total work = `N` → **O(N)**

---

### Space Complexity — **O(N)** (Worst Case)

Why?

* Recursive call stack stores nodes
* Worst case (skewed tree): stack size = N

> Balanced tree → O(log N)
> Skewed tree → O(N)

Interview answer: **O(N)**

---

## 14. Common Mistakes (Interview Traps)

1. Forgetting base case → infinite recursion
2. Swapping left and right order
3. Thinking recursion is extra memory (it is stack)
4. Confusing preorder with inorder

---

## 15. Interview-Level Q&A Synthesis

### Q1. Why root is processed first?

Because preorder is **Root-first traversal**.

---

### Q2. Can preorder be done iteratively?

Yes, using a stack.

---

### Q3. When is preorder useful?

* Copying a tree
* Prefix expression evaluation
* Tree serialization

---

### Q4. What happens if tree is skewed?

Space complexity becomes **O(N)**.

---

### Q5. Why recursion fits trees?

Because each subtree follows same structure.

---

## Key Takeaway (Lock This)

> **Preorder = Root before children**
> If recursion + base case is clear, traversal becomes automatic.

---