# BINARY TREE — INORDER TRAVERSAL (DFS)

---

## What We Covered Here

1. What inorder traversal means in a binary tree
2. Core rule of inorder traversal (Left → Root → Right)
3. Why inorder is extremely important (especially for BST)
4. Recursive inorder traversal — algorithm and intuition
5. Base case vs recursive case clarity
6. Step-by-step dry run (recursive, very detailed)
7. C++ recursive implementation (clean + deeply commented)
8. JavaScript recursive implementation
9. Iterative inorder traversal using stack
10. Why stack replaces recursion
11. Step-by-step dry run (iterative, stack-focused)
12. Time & space complexity (balanced vs skewed tree)
13. Common mistakes and interview traps
14. Interview-level Q&A synthesis

---

## 1. What Is Inorder Traversal? (Mindset First)

**Inorder traversal** means:

> Visit nodes in the order
> **LEFT → ROOT → RIGHT**

So for every node:

1. First go completely to the left
2. Then process the node itself
3. Then go to the right

---

## 2. Why Inorder Traversal Is Special

This is **very important for interviews**.

If the tree is a **Binary Search Tree (BST)**:

> **Inorder traversal gives values in sorted order**

That single statement is asked very frequently.

---

## 3. Inorder Traversal Rule (Lock This)

```
LEFT → ROOT → RIGHT
```

Compare:

* Preorder  → Root first
* Inorder   → Root in the middle
* Postorder → Root last

---

## 4. Recursive Inorder Traversal — Core Idea

At any node `root`:

1. Traverse left subtree
2. Process current node
3. Traverse right subtree

---

## 5. Recursive Algorithm (Clear Thinking)

### Base Case

* If node is `null`, stop recursion

### Recursive Case

* Go left
* Visit node
* Go right

---

## 6. Pseudocode (Before Code)

```
INORDER(node):
    IF node is NULL:
        return

    INORDER(node.left)
    visit(node)
    INORDER(node.right)
```

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

## 8. Dry Run — Recursive (Very Deep, Step-by-Step)

### Expected Output

```
[4, 2, 5, 1, 3]
```

---

### Step-by-Step Execution Table

| Step | Current Node | Action Taken    | Output Array    |
| ---- | ------------ | --------------- | --------------- |
| 1    | 1            | Go left         | []              |
| 2    | 2            | Go left         | []              |
| 3    | 4            | Go left (null)  | []              |
| 4    | 4            | Visit node      | [4]             |
| 5    | 4            | Go right (null) | [4]             |
| 6    | 2            | Visit node      | [4, 2]          |
| 7    | 5            | Go left (null)  | [4, 2]          |
| 8    | 5            | Visit node      | [4, 2, 5]       |
| 9    | 5            | Go right (null) | [4, 2, 5]       |
| 10   | 1            | Visit node      | [4, 2, 5, 1]    |
| 11   | 3            | Go left (null)  | [4, 2, 5, 1]    |
| 12   | 3            | Visit node      | [4, 2, 5, 1, 3] |
| 13   | 3            | Go right (null) | Done            |

---

### Call Stack Visualization

```
inorder(1)
 ├── inorder(2)
 │    ├── inorder(4)
 │    │    ├── inorder(NULL)
 │    │    └── visit 4
 │    └── inorder(5)
 │         ├── inorder(NULL)
 │         └── visit 5
 └── visit 1
     └── inorder(3)
          ├── inorder(NULL)
          └── visit 3
```

---

## 9. C++ — Recursive Inorder (Core Logic)

### Version 1 — Only Required Functions

```cpp
void recursiveInorder(TreeNode* root, vector<int>& arr) {
    if (root == nullptr) return;

    recursiveInorder(root->left, arr);
    arr.push_back(root->data);
    recursiveInorder(root->right, arr);
}

vector<int> inorder(TreeNode* root) {
    vector<int> arr;
    recursiveInorder(root, arr);
    return arr;
}
```

---

## 10. C++ — Recursive Inorder (Full Program, Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Tree node structure
struct TreeNode {
    int data;               // Value stored in node
    TreeNode* left;         // Left child
    TreeNode* right;        // Right child

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
private:
    void recursiveInorder(TreeNode* root, vector<int>& arr) {

        // Base case: if node is NULL, stop
        if (root == nullptr) {
            return;
        }

        // Step 1: Traverse left subtree
        recursiveInorder(root->left, arr);

        // Step 2: Visit current node
        arr.push_back(root->data);

        // Step 3: Traverse right subtree
        recursiveInorder(root->right, arr);
    }

public:
    vector<int> inorder(TreeNode* root) {
        vector<int> arr;            // Stores result
        recursiveInorder(root, arr);
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

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<int> result = sol.inorder(root);

    cout << "Inorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
```

---

## 11. JavaScript — Recursive Inorder

```javascript
function inorderTraversal(root, result) {
    if (root === null) return;

    inorderTraversal(root.left, result);
    result.push(root.data);
    inorderTraversal(root.right, result);
}

function inorder(root) {
    let result = [];
    inorderTraversal(root, result);
    return result;
}
```

---

## 12. Iterative Inorder Traversal (Why We Need This)

### Why Iterative?

* Recursion uses system stack
* Iterative version gives **explicit control**
* Often asked in interviews

> Stack simulates recursion.

---

## 13. Iterative Algorithm (Mental Model)

1. Go as left as possible, pushing nodes onto stack
2. When left ends:

   * Pop from stack
   * Visit node
   * Move to right
3. Repeat until stack empty AND node is null

---

## 14. Iterative Dry Run (Stack-Based)

Initial state:

```
node = 1
stack = []
output = []
```

### Key Steps

| Action     | Stack   | Node | Output      |
| ---------- | ------- | ---- | ----------- |
| Push 1     | [1]     | 2    | []          |
| Push 2     | [1,2]   | 4    | []          |
| Push 4     | [1,2,4] | null | []          |
| Pop 4      | [1,2]   | null | [4]         |
| Move right | [1,2]   | null | [4]         |
| Pop 2      | [1]     | 5    | [4,2]       |
| Push 5     | [1,5]   | null | [4,2]       |
| Pop 5      | [1]     | null | [4,2,5]     |
| Pop 1      | []      | 3    | [4,2,5,1]   |
| Push 3     | [3]     | null | [4,2,5,1]   |
| Pop 3      | []      | null | [4,2,5,1,3] |

---

## 15. C++ — Iterative Inorder (Exact Code)

```cpp
vector<int> inorder(TreeNode* root) {

    stack<TreeNode*> st;
    TreeNode* node = root;
    vector<int> inorder;

    while (true) {

        if (node != nullptr) {
            st.push(node);
            node = node->left;
        }
        else {
            if (st.empty()) break;

            node = st.top();
            st.pop();

            inorder.push_back(node->data);
            node = node->right;
        }
    }

    return inorder;
}
```

---

## 16. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

* Each node visited once

### Space Complexity

* Recursive: **O(N)** worst case
* Iterative: **O(H)** (H = height of tree)

  * Balanced tree → O(log N)
  * Skewed tree → O(N)

---

## 17. Common Mistakes (Interview Traps)

1. Visiting root before left (that becomes preorder)
2. Forgetting base case
3. Misunderstanding stack behavior
4. Assuming space is always O(log N)

---

## 18. Interview-Level Q&A Synthesis

### Q1. Why inorder is important?

Because inorder of BST is sorted.

---

### Q2. Recursive or iterative — which is better?

Depends on stack constraints.

---

### Q3. Can inorder be done without stack or recursion?

Yes — **Morris Traversal** (advanced).

---

### Q4. Worst-case space complexity?

O(N) for skewed tree.

---

### Q5. Where is inorder used in real life?

* BST validation
* Sorted data extraction
* Expression trees

---

## Key Takeaway (Lock This)

> **Inorder = Left first, Root in middle, Right last**
> If you understand stack + left descent, iterative inorder becomes easy.

---