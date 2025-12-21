# BINARY TREE — PREORDER + INORDER + POSTORDER

## (ALL THREE IN **ONE TRAVERSAL**, USING ONE STACK)

---

## What We Covered Here

1. Why doing all 3 traversals separately is inefficient
2. Key idea: **state-based traversal**
3. How recursion actually works internally
4. Mapping recursion → stack + state
5. Meaning of traversal states (1, 2, 3)
6. Exact algorithm (single traversal)
7. Very deep dry run (state-by-state)
8. C++ Version 1 — Core logic only (interview-ready)
9. C++ Version 2 — Full program (learning + interview)
10. JavaScript implementation
11. Time & space complexity (real explanation)
12. Common mistakes
13. Interview-level Q&A synthesis

---

## 1. Why This Problem Exists (Mindset)

Normally, we do:

* Preorder → one traversal
* Inorder → one traversal
* Postorder → one traversal

That is **3 full traversals**.

Interview question:

> “Can you do all three in **one traversal**?”

This checks:

* Stack understanding
* Recursion internals
* State management
* Tree depth clarity

---

## 2. Core Insight (MOST IMPORTANT)

> **Recursion already knows preorder, inorder, postorder.
> We just need to expose its internal state.**

So instead of:

```
call → return → call → return
```

We track **WHERE** a node is in its lifecycle.

---

## 3. Node Lifecycle (THIS IS THE KEY)

Every node is processed **three times** in recursion:

| Moment              | Traversal |
| ------------------- | --------- |
| First time seen     | Preorder  |
| After left subtree  | Inorder   |
| After right subtree | Postorder |

We encode this using **states**.

---

## 4. State Meaning (LOCK THIS)

We store in stack:

```
(node, state)
```

| State | Meaning              | Traversal |
| ----- | -------------------- | --------- |
| 1     | Node seen first time | Preorder  |
| 2     | Left subtree done    | Inorder   |
| 3     | Right subtree done   | Postorder |

---

## 5. Algorithm (Clean & Exact)

```
IF root is NULL:
    return empty

Create stack of (node, state)

Push (root, 1)

WHILE stack not empty:
    (node, state) = stack.pop()

    IF state == 1:
        add node to preorder
        push (node, 2)
        push (node.left, 1) if exists

    ELSE IF state == 2:
        add node to inorder
        push (node, 3)
        push (node.right, 1) if exists

    ELSE:
        add node to postorder
```

**This exactly mimics recursion.**

---

## 6. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
        / \
       4   5
```

Expected:

```
Pre  = [1, 2, 4, 5, 3]
In   = [4, 2, 5, 1, 3]
Post = [4, 5, 2, 3, 1]
```

---

## 7. Dry Run — VERY DEEP (State by State)

### Initial

```
stack = [(1,1)]
pre = []
in  = []
post= []
```

---

### Step-by-step Execution

| Stack Pop | Action    | Stack After       | Pre         | In          | Post        |
| --------- | --------- | ----------------- | ----------- | ----------- | ----------- |
| (1,1)     | pre += 1  | (1,2),(2,1)       | [1]         | []          | []          |
| (2,1)     | pre += 2  | (1,2),(2,2),(4,1) | [1,2]       | []          | []          |
| (4,1)     | pre += 4  | (1,2),(2,2),(4,2) | [1,2,4]     | []          | []          |
| (4,2)     | in += 4   | (1,2),(2,2),(4,3) | [1,2,4]     | [4]         | []          |
| (4,3)     | post += 4 | (1,2),(2,2)       | [1,2,4]     | [4]         | [4]         |
| (2,2)     | in += 2   | (1,2),(2,3),(5,1) | [1,2,4]     | [4,2]       | [4]         |
| (5,1)     | pre += 5  | (1,2),(2,3),(5,2) | [1,2,4,5]   | [4,2]       | [4]         |
| (5,2)     | in += 5   | (1,2),(2,3),(5,3) | [1,2,4,5]   | [4,2,5]     | [4]         |
| (5,3)     | post += 5 | (1,2),(2,3)       | [1,2,4,5]   | [4,2,5]     | [4,5]       |
| (2,3)     | post += 2 | (1,2)             | [1,2,4,5]   | [4,2,5]     | [4,5,2]     |
| (1,2)     | in += 1   | (1,3),(3,1)       | [1,2,4,5]   | [4,2,5,1]   | [4,5,2]     |
| (3,1)     | pre += 3  | (1,3),(3,2)       | [1,2,4,5,3] | [4,2,5,1]   | [4,5,2]     |
| (3,2)     | in += 3   | (1,3),(3,3)       | [1,2,4,5,3] | [4,2,5,1,3] | [4,5,2]     |
| (3,3)     | post += 3 | (1,3)             | …           | …           | [4,5,2,3]   |
| (1,3)     | post += 1 | empty             | …           | …           | [4,5,2,3,1] |

Traversal complete.

---

## 8. C++ — Version 1 (CORE LOGIC ONLY)

```cpp
vector<vector<int>> preInPostTraversal(Node* root) {

    vector<int> pre, in, post;
    if (root == nullptr) return {};

    stack<pair<Node*, int>> st;
    st.push({root, 1});

    while (!st.empty()) {
        auto it = st.top();
        st.pop();

        if (it.second == 1) {
            pre.push_back(it.first->data);
            it.second = 2;
            st.push(it);
            if (it.first->left)
                st.push({it.first->left, 1});
        }
        else if (it.second == 2) {
            in.push_back(it.first->data);
            it.second = 3;
            st.push(it);
            if (it.first->right)
                st.push({it.first->right, 1});
        }
        else {
            post.push_back(it.first->data);
        }
    }

    return {pre, in, post};
}
```

---

## 9. C++ — Version 2 (FULL PROGRAM, DEEP COMMENTED)

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
    vector<vector<int>> preInPostTraversal(Node* root) {

        vector<int> pre, in, post;

        if (root == nullptr) return {};

        stack<pair<Node*, int>> st;
        st.push({root, 1});

        while (!st.empty()) {

            auto it = st.top();
            st.pop();

            // Preorder
            if (it.second == 1) {
                pre.push_back(it.first->data);
                it.second = 2;
                st.push(it);

                if (it.first->left != nullptr) {
                    st.push({it.first->left, 1});
                }
            }

            // Inorder
            else if (it.second == 2) {
                in.push_back(it.first->data);
                it.second = 3;
                st.push(it);

                if (it.first->right != nullptr) {
                    st.push({it.first->right, 1});
                }
            }

            // Postorder
            else {
                post.push_back(it.first->data);
            }
        }

        return {pre, in, post};
    }
};

int main() {

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    Solution sol;
    auto res = sol.preInPostTraversal(root);

    cout << "Preorder: ";
    for (int x : res[0]) cout << x << " ";
    cout << endl;

    cout << "Inorder: ";
    for (int x : res[1]) cout << x << " ";
    cout << endl;

    cout << "Postorder: ";
    for (int x : res[2]) cout << x << " ";
    cout << endl;

    return 0;
}
```

---

## 10. JavaScript Implementation

```javascript
function preInPostTraversal(root) {
    if (root === null) return [];

    let pre = [], inorder = [], post = [];
    let stack = [];
    stack.push([root, 1]);

    while (stack.length > 0) {
        let [node, state] = stack.pop();

        if (state === 1) {
            pre.push(node.data);
            stack.push([node, 2]);
            if (node.left) stack.push([node.left, 1]);
        }
        else if (state === 2) {
            inorder.push(node.data);
            stack.push([node, 3]);
            if (node.right) stack.push([node.right, 1]);
        }
        else {
            post.push(node.data);
        }
    }

    return [pre, inorder, post];
}
```

---

## 11. Complexity Analysis (REAL TALK)

### Time Complexity

```
O(3N) → O(N)
```

Each node processed exactly **3 times**.

---

### Space Complexity

```
O(N)
```

* Stack
* Pre, In, Post arrays

---

## 12. Common Mistakes (VERY IMPORTANT)

1. Forgetting to push node back with updated state
2. Wrong child push order
3. Mixing state numbers
4. Thinking recursion is simpler than this (this is recursion exposed)

---

## 13. Interview-Level Q&A Synthesis

**Q1. Why states are needed?**
To simulate recursion manually.

**Q2. Is this better than 3 traversals?**
Yes — single DFS pass.

**Q3. Will interviewer expect this?**
Yes, for strong candidates.

**Q4. Can this be done recursively?**
No — recursion separates traversals.

**Q5. Most important insight?**
Node lifecycle has **three distinct moments**.

---

## FINAL TAKEAWAY (LOCK THIS 🔒)

> **One traversal = stack + node state**
>
> If you understand **state 1 → 2 → 3**,
> you understand **recursion itself**.
