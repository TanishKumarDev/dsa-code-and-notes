
# BINARY TREE — ITERATIVE POSTORDER TRAVERSAL (USING 2 STACKS)

---

## What We Covered Here

1. Why postorder is hardest to do iteratively
2. Postorder rule recap (Left → Right → Root)
3. Why one stack is not enough (intuition)
4. Core idea of using **two stacks**
5. How 2-stack approach mimics recursion
6. Exact algorithm for postorder using 2 stacks
7. Very deep step-by-step dry run
8. C++ implementation (clean + deeply commented)
9. JavaScript implementation
10. Time & space complexity (balanced vs skewed)
11. Common mistakes and interview traps
12. Interview-level Q&A synthesis

---

## 1. Postorder Rule (Recall First)

```
POSTORDER = LEFT → RIGHT → ROOT
```

Key property:

> **Root is processed last**

This single fact makes postorder tricky.

---

## 2. Why Iterative Postorder Is Hard

In preorder and inorder:

* Root is processed early or in middle

In postorder:

* Root must wait until **both children are fully done**

Recursion handles this automatically.
Iteration does **not**.

So we need help.

---

## 3. Why Two Stacks? (Core Insight)

Think like this:

* Stack 1 → **Traversal control**
* Stack 2 → **Reverse the order**

The 2-stack trick converts:

```
Root → Right → Left   (intermediate order)
```

into:

```
Left → Right → Root   (postorder)
```

That’s the entire magic.

---

## 4. Key Mental Model (Very Important)

> **Postorder = reverse of (Root → Right → Left)**

So we:

1. Generate `Root → Left → Right`-like order
2. Reverse it using second stack

---

## 5. Algorithm (Structured & Clean)

```
IF root is NULL:
    return empty list

Create stack1, stack2

Push root into stack1

WHILE stack1 not empty:
    node = stack1.pop()
    push node into stack2

    IF node.left exists:
        push node.left into stack1
    IF node.right exists:
        push node.right into stack1

WHILE stack2 not empty:
    pop node from stack2
    add node.data to result
```

---

## 6. Why LEFT is pushed before RIGHT? (Interview Trap)

Because stack is **LIFO**.

If we push:

```
left first
right next
```

Then:

* Right is processed before left in stack1
* Stack2 ends up with **Left → Right → Root**

Which is exactly postorder after popping.

---

## 7. Example Tree (We Will Dry Run This)

```
            1
          /   \
         2     3
        / \
       4   5
```

Expected Output:

```
[4, 5, 2, 3, 1]
```

---

## 8. Dry Run — VERY DEEP (Two Stacks)

### Initial State

```
stack1 = [1]
stack2 = []
output = []
```

---

### Iteration 1

* Pop `1` from stack1
* Push `1` to stack2
* Push left `2` to stack1
* Push right `3` to stack1

```
stack1 = [2, 3]
stack2 = [1]
```

---

### Iteration 2

* Pop `3`
* Push `3` to stack2
* No children

```
stack1 = [2]
stack2 = [1, 3]
```

---

### Iteration 3

* Pop `2`
* Push `2` to stack2
* Push left `4`
* Push right `5`

```
stack1 = [4, 5]
stack2 = [1, 3, 2]
```

---

### Iteration 4

* Pop `5`
* Push `5` to stack2

```
stack1 = [4]
stack2 = [1, 3, 2, 5]
```

---

### Iteration 5

* Pop `4`
* Push `4` to stack2

```
stack1 = []
stack2 = [1, 3, 2, 5, 4]
```

---

### Final Phase — Pop stack2

Popping stack2 gives:

```
4 → 5 → 2 → 3 → 1
```

Which is **postorder**.

---

## 9. C++ — Iterative Postorder (Core Logic)

### Version 1 — Only Required Function

```cpp
vector<int> postOrder(Node* root) {

    vector<int> postorder;
    if (root == nullptr) return postorder;

    stack<Node*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        Node* node = st1.top();
        st1.pop();

        st2.push(node);

        if (node->left != nullptr)
            st1.push(node->left);

        if (node->right != nullptr)
            st1.push(node->right);
    }

    while (!st2.empty()) {
        postorder.push_back(st2.top()->data);
        st2.pop();
    }

    return postorder;
}
```

---

## 10. C++ — Full Program (Deep Commented)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Node structure
struct Node {
    int data;           // Value of node
    Node* left;         // Left child
    Node* right;        // Right child

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

vector<int> postOrder(Node* root) {

    vector<int> postorder;

    // Edge case
    if (root == nullptr) {
        return postorder;
    }

    // Two stacks
    stack<Node*> st1, st2;

    // Push root to first stack
    st1.push(root);

    // Process all nodes
    while (!st1.empty()) {

        // Pop from stack1
        Node* node = st1.top();
        st1.pop();

        // Push into stack2
        st2.push(node);

        // Push children into stack1
        if (node->left != nullptr) {
            st1.push(node->left);
        }
        if (node->right != nullptr) {
            st1.push(node->right);
        }
    }

    // stack2 now contains reverse postorder
    while (!st2.empty()) {
        postorder.push_back(st2.top()->data);
        st2.pop();
    }

    return postorder;
}

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

    vector<int> result = postOrder(root);

    cout << "Postorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
```

---

## 11. JavaScript — Iterative Postorder (2 Stacks)

```javascript
function postOrder(root) {
    let result = [];
    if (root === null) return result;

    let st1 = [];
    let st2 = [];

    st1.push(root);

    while (st1.length > 0) {
        let node = st1.pop();
        st2.push(node);

        if (node.left !== null) st1.push(node.left);
        if (node.right !== null) st1.push(node.right);
    }

    while (st2.length > 0) {
        result.push(st2.pop().data);
    }

    return result;
}
```

---

## 12. Time & Space Complexity (Deep Explanation)

### Time Complexity — **O(N)**

* Each node:

  * Pushed once into st1
  * Pushed once into st2
  * Popped once

So:

```
Time = O(N)
```

---

### Space Complexity — **O(N)**

* Two stacks can hold up to N nodes
* Worst case (skewed tree)

Interview-safe answer:

```
Space = O(N)
```

---

## 13. Common Mistakes (Interview Traps)

1. Pushing right before left (order breaks)
2. Forgetting second stack
3. Thinking space is O(H) (it is O(N))
4. Confusing this with single-stack method

---

## 14. Interview-Level Q&A Synthesis

### Q1. Why two stacks?

To reverse traversal order safely.

---

### Q2. Can postorder be done with one stack?

Yes, but logic is much more complex.

---

### Q3. Which is easier — recursive or iterative?

Recursive is simpler, iterative is safer.

---

### Q4. Why not reverse preorder directly?

Because subtree ordering matters.

---

### Q5. When is postorder used?

Tree deletion, expression evaluation, bottom-up DP.

---

## Key Takeaway (Lock This)

> **Iterative Postorder = Two stacks + Reverse thinking**
