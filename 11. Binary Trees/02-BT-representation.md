# BINARY TREE — REPRESENTATION (C++ & JavaScript)

---

## What We Covered Here

1. How a Binary Tree is represented in memory
2. Why pointers/references are required for tree structures
3. Core building block: **Binary Tree Node**
4. Node structure (data + left + right)
5. Constructor purpose and initialization logic
6. Meaning of `NULL` / `nullptr` in tree nodes
7. How nodes are connected to form a tree
8. Manual construction of a binary tree
9. C++ pointer-based implementation
10. JavaScript reference-based implementation
11. Mental model of tree connections in memory
12. Interview-level understanding and common traps

---

## 1. How a Binary Tree Is Represented (Big Picture)

A **Binary Tree is NOT stored like an array**.

It is represented using:

* **Nodes**
* **Pointers (C++) / References (JavaScript)**

Each node:

* Stores its own data
* Knows **where its children are**

This creates a **hierarchical structure**, not a linear one.

---

## 2. Why Pointers / References Are Mandatory

### Why we cannot use arrays

Arrays:

* Are linear
* Require contiguous memory
* Do not model hierarchy naturally

Binary Trees:

* Are non-linear
* Nodes can live **anywhere in memory**
* Connections are maintained via addresses

> **Tree = nodes + connections (addresses)**

---

## 3. Core Building Block — Node (Most Important)

![](https://static.takeuforward.org/content/-mfv2SVN3)
![](https://static.takeuforward.org/content/-SS_mCP4U)

Every Binary Tree is made of **nodes**.

Each node has **three parts**:

```
[data | left | right]
```

### Meaning of Each Part

* `data` → value stored in the node
* `left` → address/reference of left child
* `right` → address/reference of right child

If a child does not exist → pointer/reference is `null`.

![](https://static.takeuforward.org/content/-LNSBp0lD)
---

## 4. Binary Tree Node Structure (C++)

### Exact Code (Same as Source, Clean + Explained)

```cpp
#include <iostream>
using namespace std;

// Class representing a Node in the Binary Tree
class Node {
public:
    int data;      // Stores the value of the node
    Node* left;    // Pointer to the left child node
    Node* right;   // Pointer to the right child node

    // Constructor to initialize a node
    Node(int key) {
        data = key;        // Assign value to node
        left = nullptr;   // No left child initially
        right = nullptr;  // No right child initially
    }
};
```

---

### Why Each Line Exists (Very Important)

* `int data;`
  Stores actual information of the node

* `Node* left;`
  Holds address of left child

* `Node* right;`
  Holds address of right child

* `left = nullptr; right = nullptr;`
  Means:

  > This node currently has **no children**

This avoids:

* Garbage memory
* Accidental traversal to random locations

---

## 5. Meaning of `nullptr` / `NULL`

`nullptr` means:

* No node exists here
* End of a branch

Similar to:

* `null` in linked list
* `NULL` pointer

> **Leaf node = left == nullptr AND right == nullptr**

---

## 6. How Nodes Are Connected (Mental Model)

Creating nodes alone is useless.

The tree forms only when we **connect nodes**.

Example structure:

```
        1
       / \
      2   3
         /
        5
```

Connections happen like this:

```cpp
root->left = new Node(2);
root->right = new Node(3);
root->right->left = new Node(5);
```

Each assignment stores an **address**.

---

## 7. Binary Tree Creation (C++ — Full Example)

### Code (Exact Logic, Clean, Explained)

```cpp
// Class containing the logic for Binary Tree creation
class Solution {
public:
    Node* createBinaryTree() {

        // Step 1: Create root node
        Node* root = new Node(1);

        // Step 2: Create left child of root
        root->left = new Node(2);

        // Step 3: Create right child of root
        root->right = new Node(3);

        // Step 4: Create left child of node 3
        root->right->left = new Node(5);

        // Return root (entry point of tree)
        return root;
    }
};
```

---

### Driver Code (Complete Program)

```cpp
int main() {
    Solution solution;

    // Root stores the entry point of the tree
    Node* root = solution.createBinaryTree();

    // Tree is now created in memory
    return 0;
}
```

---

## 8. Memory Visualization (Critical for Understanding)

Each node lives separately in heap memory:

```
Node(1) at A100
Node(2) at B240
Node(3) at C560
Node(5) at D890
```

Connections:

```
root -> A100
A100.left  -> B240
A100.right -> C560
C560.left  -> D890
```

> Tree = nodes + pointer wiring

---

## 9. Same Concept in JavaScript (References)

### Node Structure (JavaScript)

```javascript
class Node {
    constructor(data) {
        this.data = data;   // value of node
        this.left = null;   // left child reference
        this.right = null;  // right child reference
    }
}
```

---

### Tree Creation (JavaScript)

```javascript
function createBinaryTree() {

    // Create root
    let root = new Node(1);

    // Create children
    root.left = new Node(2);
    root.right = new Node(3);
    root.right.left = new Node(5);

    return root;
}
```

---

### Key Difference (C++ vs JavaScript)

| Aspect      | C++               | JavaScript         |
| ----------- | ----------------- | ------------------ |
| Connection  | Pointers          | References         |
| Memory free | Manual (`delete`) | Garbage Collected  |
| Syntax      | `Node* left`      | `this.left = null` |
| Concept     | Same              | Same               |

> Conceptually **both work the same**.

---

## 10. Time & Space Complexity

### Creation Time

* Each node creation → O(1)
* Total nodes = `n`

```
Time Complexity = O(n)
```

### Space Complexity

* One node per value

```
Space Complexity = O(n)
```

---

## 11. Common Mistakes (Interview Traps)

1. Forgetting to return `root`
2. Not initializing left/right to null
3. Losing root reference
4. Assuming array-like storage
5. Confusing full vs complete tree

---

## 12. Interview-Level Q&A Synthesis

### Q1. Why do we always return root?

Because root is the **only entry point** to the tree.

---

### Q2. Can a node have only one child?

Yes. Binary tree allows **0, 1, or 2 children**.

---

### Q3. How is tree traversal possible?

Using pointers/references stored in nodes.

---

### Q4. Why not store trees in arrays?

Arrays fail for:

* Dynamic structure
* Non-complete trees
* Sparse hierarchies

---

### Q5. What defines a leaf node?

Both `left` and `right` are `null`.

---

## Key Takeaway (Lock This)

> A Binary Tree is nothing but **nodes connected by pointers**.
> If you understand **node + connection**, everything else becomes traversal.

---